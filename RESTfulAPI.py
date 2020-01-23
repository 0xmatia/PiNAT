from sys import path
import sqlite3
import os, subprocess
path.append("src/python")
from Plugin_Observer import plugin_system
from flask import Flask
from flask_restful import Resource, Api

plugins_dictionary = {}

app = Flask(__name__)
api = Api(app)

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
        return {"status": "online", "plugins": available_plugins}

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
    

"""
This will return the result of a specifed action
"""
class PluginAction(Resource):
     def get(self, plugin: str, action: str):
        try:
            requested_plugin = plugins_dictionary[plugin]
            result = getattr(requested_plugin, action)() # result should be in json format
            return result
        except KeyError:
            return {"status": "Plugin was not found"}, 500
        except AttributeError:
            return {"status": "invalid action"}, 500


# add resources to API
api.add_resource(Root, "/")
api.add_resource(ListPluginActions, "/<string:plugin>")
api.add_resource(PluginAction, "/<string:plugin>/<string:action>")


if __name__ == "__main__":
    current_path = os.getcwd() # save curred pwd
    load_plugins()
    os.chdir(current_path) #restore path
    app.run(debug=True)
    subprocess.Popen(['./clean_pyc.sh']).wait() # clean pyc
