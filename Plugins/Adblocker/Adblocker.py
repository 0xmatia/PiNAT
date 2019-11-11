from PluginSystem import plugin

class Adblocker(plugin):

    def __init__(self):
        self.name = "Adblocker"
        self.type = "Analyzer"
        self.version = 0.1
        self.description = "Blocking ads & stuff"
        self.author = "Elad Matia"

    def action1(self):
        print(f"This is {self.name}, and I am {self.description}")