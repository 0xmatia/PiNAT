from wifi import Cell
from time import sleep
from sys import argv
import sqlite3
import os


EVIL_TWIN_DB = "src/python/evil_twin/evil_twin.db"

def scan_for_evil_twin(time, adapter):    
    conn = sqlite3.connect(EVIL_TWIN_DB)
    cursor = conn.cursor()
    cursor.execute("CREATE TABLE IF NOT EXISTS LOG (DUPLICATE TEXT NOT NULL, TIME TEXT NOT NULL)")
    conn.commit()
    conn.close()

    try:
        while True:
            duplicates = []
            ssids = [cell.ssid for cell in Cell.all(adapter)]
            for ssid in ssids:
                if ssids.count(ssid) > 1 and ssid not in duplicates and ssid != "":
                    duplicates.append(ssid)

            for duplicate in duplicates:
                print("[Evil-Twin Detector]: Warning - Found multiple wifi networks with the same SSID: {}".format(duplicate))
                conn = sqlite3.connect(EVIL_TWIN_DB)
                cursor = conn.cursor()
                cursor.execute("INSERT OR IGNORE INTO LOG VALUES (?, strftime('%Y-%m-%d %H:%M', 'now', 'localtime'))", (duplicate, ))
                conn.commit()
                conn.close()

            sleep(time)
    except KeyboardInterrupt:
        print("[Evil-Twin Detector]: Terminating")


def get_log():
    log = []
    conn = sqlite3.connect(EVIL_TWIN_DB)
    cursor = conn.cursor()
    cursor.execute("SELECT * from LOG")
    result = cursor.fetchall()
    conn.close()

    for entry in result:
        log.append({"SSID": entry[0], "Time": entry[1]})
    return log


def delete_log():
    print(os.geteuid())
    conn = sqlite3.connect(EVIL_TWIN_DB)
    cursor = conn.cursor()
    cursor.execute("DELETE FROM LOG")
    conn.commit()
    conn.close() 


def main():
    try:
        time = int(argv[1])
        adapter = argv[2]
    except IndexError:
        print("""
        Usage: evil_detector.py [time] [adapter]
        """)
    scan_for_evil_twin(time, adapter)


if __name__ == "__main__":
    main()