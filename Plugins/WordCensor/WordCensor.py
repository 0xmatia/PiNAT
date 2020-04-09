from Plugin_Observer import plugin
from bin import pynat
import sqlite3
import os
import json

class WordCensor(plugin):

    def __init__(self):
        self.name = "WordCensor"
        self.type = "censor"
        self.version = 1.0
        self.description = "censors any given words"
        self.author = "Elad Matia"
        self.priority = 1000
        self.actions = ["get_log"]
        
        self.db = ""


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
