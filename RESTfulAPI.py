from sys import path
import sqlite3
import os
path.append("Plugins/IPBlocker")
path.append("src/python")
from Plugin_Observer import plugin_system

plugins_directory = {}

def main():
    plugin_observer_instance = plugin_system("Plugins")
    plugins = list(plugin_observer_instance.reload().values())
    # put the plugins in directory
    # so we can access them by name
    for plugin in plugins:
        plugins_directory[plugin.name] = plugin
        plugin.setup()

    # call for example to get_blocked_ips of the IPBlocker plugin
    # print(getattr(plugins_directory["IPBlocker"], "get_blocked_ips")())
    print(plugins_directory["IPBlocker"].get_actions())


if __name__ == "__main__":
    main()
