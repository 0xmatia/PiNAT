from sys import path
import sqlite3
import os
import subprocess

path.append("src/python")
from src.python import Network_Status as ns
from src.python.evil_twin import evil_twin
from flask_restful import Resource, Api
from flask import Flask
from Plugin_Observer import plugin_system
plugins_dictionary = {}

app = Flask(__name__)
api = Api(app)
adapter = ""

"""
This function loads the plugins so we can access the databases
"""


def load_plugins():
    plugin_observer_instance = plugin_system("Plugins")
    plugins = list(plugin_observer_instance.reload().values())
    # put the plugins in a dictionary
    # so we can access them by name
    for plugin in plugins:
        plugins_dictionary[plugin.name] = plugin
        plugin.setup()

#########################################################################


"""
This is the root - return:
Pinat is online, list of available plugins
"""


class Root(Resource):
    def get(self):
        available_plugins = list(plugins_dictionary.keys())
        actions = ['get_evil_twin_log']
        devices = ns.get_connected_devices(adapter)
        return {"status": "online",
                "connected entities": devices,
                "actions": actions,
                "plugins": available_plugins}


"""
This will return all available actions for a specified plugin
"""


class ListPluginActions(Resource):
    def get(self, plugin: str):
        try:
            action_list = plugins_dictionary[plugin].get_actions()
            return {"actions": action_list}
        except KeyError:
            return {"status": "Plugin was not found"}, 500

    def delete(self, plugin: str):
        try:
            plugins_dictionary[plugin].delete_database()
            return {"status": "success"}
        except KeyError:
            return {"status": "Plugin was not found"}, 500


"""
This will return the result of a specifed action
"""


class PluginAction(Resource):
    def get(self, plugin: str, action: str):
        try:
            requested_plugin = plugins_dictionary[plugin]
            # result should be in json format
            result = getattr(requested_plugin, action)()
            return result
        except KeyError:
            return {"status": "Plugin was not found"}, 500
        except AttributeError:
            return {"status": "invalid action"}, 500


class EvilTwinLog(Resource):
    def get(self):
        return {"status": "success", "log": evil_twin.get_log()}

    def delete(self):
        evil_twin.delete_log()
        return {"status": "success"}


# add resources to API
api.add_resource(Root, "/")
api.add_resource(EvilTwinLog, "/get_evil_twin_log")
api.add_resource(ListPluginActions, "/<string:plugin>")
api.add_resource(PluginAction, "/<string:plugin>/<string:action>")


if __name__ == "__main__":
    current_path = os.getcwd()  # save curred pwd
    load_plugins()
    os.chdir(current_path)  # restore path

    data = ""
    with open("config.txt", 'r') as f:
        data = f.read()

    data = data.split("\n")
    for line in data:
        if line.split("=")[0] == "wireless_adapter":
            adapter = line.split("=")[1]
    print(adapter)
    app.run(debug=True, host='0.0.0.0')
