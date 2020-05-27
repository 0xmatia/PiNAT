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
                        ["delete_database", "get_log"])
        self.words_to_consor = ["Email"]
        self.censor_with = "Pinat"


    def process(self, packet):
        pynat.censor_words(packet, self.censor_with, self.words_to_consor)
        pynat.exec_db(self.db, "INSERT OR IGNORE INTO LOG VALUES \
                    ('{}', '{}', strftime('%Y-%m-%d %H:%M', 'now', 'localtime'))"
                                .format(','.join(self.words_to_consor), self.censor_with))
        return packet


    def setup(self):
        file_location = os.path.dirname(__file__)
        self.db = pynat.open_db(file_location + "/{}.db".format(self.name))
        pynat.exec_db(self.db, "CREATE TABLE IF NOT EXISTS LOG\
             (REPLACED_WORD TEXT NOT NULL, REPLACED_WITH TEXT NOT NULL,\
                  TIME TEXT NOT NULL, UNIQUE(REPLACED_WORD, REPLACED_WITH, TIME))")


    def teardown(self):
        pynat.close_db(self.db)


    def get_log(self):
        answer_array = []
        db_res = pynat.select_db(self.db, "SELECT * FROM LOG")

        for entry in db_res:
            answer_array.append(
                {"Replaced Words:": entry[0].split(","), "Replaced With": entry[1],\
                    "time": entry[2]})

        return {"result": answer_array}

    
    def delete_database(self):
        pynat.exec_db(self.db, "DELETE FROM LOG")
        return {"status": "success"}


    # return a list of available actions!
    def get_actions(self):
        return self.actions
