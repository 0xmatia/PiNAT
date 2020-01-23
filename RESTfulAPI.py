from sys import path
import sqlite3
import os, subprocess
path.append("src/python")
from Plugin_Observer import plugin_system
from flask import Flask
from flask_restful import Resource, Api

plugins_directory = {}

app = Flask(__name__)
api = Api(app)

"""
This function loads the plugins so we can access the databases
"""
def load_plugins():
    plugin_observer_instance = plugin_system("Plugins")
    plugins = list(plugin_observer_instance.reload().values())
    # put the plugins in directory
    # so we can access them by name
    for plugin in plugins:
        plugins_directory[plugin.name] = plugin
        plugin.setup()

#########################################################################
"""
This is the root - return:
Pinat is online, list of available plugins
"""

class Root(Resource):
    def get(self):
        return {"status": "online", "plugins": ["IPBlocker", "DNSDetector"]}

api.add_resource(Root, "/")

if __name__ == "__main__":
    current_path = os.getcwd() # save curred pwd
    load_plugins()
    os.chdir(current_path) #restore path
    app.run(debug=True)
    subprocess.Popen(['./clean_pyc.sh']).wait() # clean pyc
