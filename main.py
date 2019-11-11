from PluginSystem import plugin_system


def main():
    plugin_system_instance = plugin_system('Plugins')
    plugins = plugin_system_instance.reload()
    # Use the first plugin - adblocker
    adblocker = plugins[0]()
    adblocker.action1()



if __name__ == "__main__":
     main()
