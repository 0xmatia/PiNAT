# Inspiration: https://github.com/gdiepen/python_plugin_example
import pkgutil, inspect

class plugin:
    """All plugins will have to inherit this class and implement 
    its methods"""

    def __init__(self, name, author, version, description, plugin_type):
        """In order to load a plugin, we need to have the following information:
        - name of the plugin
        - author/s of the plugin
        - the current version of the plugin 
        - the description of the plugin - what does it do?
        - the plugin type (maybe in the future this will come in handy)
        It is possible and even recommended to have a config file and load the information from there
        """
        self.name = name
        self.author = author
        self.version = version
        self.description = description
        self.type = plugin_type

    # Now here we can add all the methods the plugin has to have:
    
    def action1(self):
       raise NotImplementedError


class plugin_system:
    """This class will load every plugin (File which inherits from plugin class)"""

    def __init__(self, plugins_location):
        self.plugins_location = plugins_location
        self.reload()


    def reload(self):
        """Reset the list of all plugins and initiate the walk over the main
        provided plugin package to load all available plugins
        """
        self.plugins = []
        self.seen_paths = []
        print()
        print(f'Looking for plugins under package {self.plugins_location}')
        self.walk_package(self.plugins_location)


    def walk_package(self, plugins_location):
        """Recursively walk the supplied package to retrieve all plugins
        """
        imported_package = __import__(plugins_location)

        for _, pluginname, ispkg in pkgutil.iter_modules(imported_package.__path__, imported_package.__name__ + '.'):
            if not ispkg:
                plugin_module = __import__(pluginname, inspect.isclass)
                clsmembers = inspect.getmembers(plugin_module)
                for (_, c) in clsmembers:
                    # Only add classes that are a sub class of Plugin, but NOT Plugin itself
                    if issubclass(c, plugin) & (c is not plugin):
                        print('Found plugin class: {c.__module__}.{c.__name__}')
                        self.plugins.append(c())

        