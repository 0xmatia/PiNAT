import sqlite3
from sys import path
import os
path.append("Plugins/IPBlocker")
path.append("src/python")


from IPBlocker import IPBlocker

def main():
    pwd = os.getcwd()
    blocker = IPBlocker()
    blocker.setup()
    # change working directory
    os.chdir(pwd)
    conn = sqlite3.connect("Plugins/IPBlocker/database.db")
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM ACTIONS")
    print(cursor.fetchone()[0])
    print(cursor.fetchone()[0])
    conn.commit()
    conn.close()


if __name__ == "__main__":
    main()
