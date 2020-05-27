from sys import path
import os

path.append("src/python")
from src.python import Network_Status as ns
from src.python.evil_twin import evil_twin
from flask_restful import Resource, Api, reqparse
from flask import Flask
from Plugin_Observer import plugin_system


"""
This function loads the plugins so we can access the databases
"""

def load_plugins():
    plugin_observer_instance = plugin_system("Plugins")
    plugins = list(plugin_observer_instance.reload().values())
    plugin_dict = {}
    # put the plugins in a dictionary
    # so we can access them by name
    for plugin in plugins:
        plugin_dict[plugin.name] = plugin
        plugin.setup()

    return plugin_dict


def unload_plugins(plugins):
    for plugin in plugins:
        plugin.teardown()

#########################################################################


class Root(Resource):
    def __init__(self, **kwargs):
        self.actions = kwargs['actions']
        self.plugins = kwargs['plugins']


    def get(self):
        available_plugins = list(self.plugins.keys())
        return {"status": "success",
                "online": True,
                "actions": self.actions,
                "plugins": available_plugins}


class Action(Resource):
    def __init__(self, **kwargs):
        self.actions = kwargs['actions']
        self.parser = reqparse.RequestParser()
        self.parser.add_argument("args", required=True, action="append", help="arguments are required")


    def get(self, action):
        if action in self.actions:
            func = self.actions[action].__code__
            return {"status": "success", "args": func.co_varnames[:func.co_argcount]}
        else:
            return {"status": "Action is not available"}, 404


    def post(self, action):
        if action in self.actions:
            argcount = self.actions[action].__code__.co_argcount
            args = []
            if argcount > 0:
                args = self.parser.parse_args()["args"]
                if len(args) != argcount:
                    return {"status": "Wrong number of arguments"}, 400
            
            return self.actions[action](*args)
        else:
            return {"status": "Action is not available"}, 404
               

class Plugin(Resource):
    def __init__(self, **kwargs):
        self.plugins = kwargs["plugins"]


    def get(self, plugin):
        if plugin in self.plugins:
            return {"status": "success", "actions": self.plugins[plugin].actions}
        else:
            return {"status": "Plugin is not available"}, 404


class PluginAction(Resource):
    def __init__(self, **kwargs):
        self.plugins = kwargs["plugins"]
        self.parser = reqparse.RequestParser()
        self.parser.add_argument("args", required=True, action="append", help="arguments are required")

    
    def get(self, plugin, action):
        if plugin in self.plugins:
            try:
                func = getattr(self.plugins[plugin], action).__code__
                return {"status": "success", "args": func.co_varnames[1:func.co_argcount]}
            except AttributeError:
                return {"status": "Action not available"}
        else:
            return {"status": "Plugin is not available"}, 404
    

    def post(self, plugin, action):
        if plugin in self.plugins:
            try:
                func = getattr(self.plugins[plugin], action)
            except AttributeError:
                return {"status": "Action not available"}

            argcount = func.__code__.co_argcount - 1
            args = []
            if argcount > 0:
                args = self.parser.parse_args()["args"]
                if len(args) != argcount:
                    return {"status": "Wrong number of arguments"}, 400
            
            return func(*args)
        else:
            return {"status": "Plugin is not available"}, 404


def print_config():
    with open("config.txt", 'r') as f:
        data = f.read()

    data = data.split("\n")
    config_data = []
    for line in data:
        info = line.split("=")
        if len(info) == 2:
            config_data.append({info[0]: info[1]})
    
    return {"status":"success", "result": config_data}


def get_connected_devices():
    return {"status": "success", "result": ns.get_connected_devices("ap0")}


def run_api(plugin_dictionary):
    root_actions = {
        'config': print_config,
        'network_status': get_connected_devices,
        'get_evil_twin': evil_twin.get_log,
        'delete_evil_twin': evil_twin.delete_log}

    app = Flask(__name__)
    api = Api(app)
    api.add_resource(Root, "/", resource_class_kwargs={'actions': list(root_actions.keys()), 'plugins': plugin_dictionary})
    api.add_resource(Action, "/action/<string:action>", resource_class_kwargs={'actions': root_actions})
    api.add_resource(Plugin, "/plugin/<string:plugin>", resource_class_kwargs={'plugins': plugin_dictionary})
    api.add_resource(PluginAction, "/plugin/<string:plugin>/<string:action>", resource_class_kwargs={'plugins': plugin_dictionary})

    app.run(debug=False, host='0.0.0.0')


if __name__ == "__main__":
    current_path = os.getcwd()  # save curred pwd
    plugin_dict = load_plugins()
    os.chdir(current_path)  # restore path

    run_api(plugin_dict)
    unload_plugins(plugin_dict.values())
