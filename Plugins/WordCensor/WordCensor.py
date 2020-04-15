from Plugin_Observer import plugin
from bin import pynat
import sqlite3
import os
import json

class WordCensor(plugin):

    def __init__(self):
        plugin.__init__(self,
        "WordCensor",
        "Elad Matia",
        0.1,
        "Censors any given words",
        "Censor",
        1000,
        None,
        [])


    def process(self, packet):
        pynat.censor_words(packet, "Pinat", ["Email"])
        return packet


    def setup(self):
        pass


    def teardown(self):
        pass

    
    # return a list of available actions!
    def get_actions(self):
        return self.actions
