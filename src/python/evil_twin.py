from wifi import Cell
from time import sleep
from sys import argv
import sqlite3

def scan_for_evil_twin(time, adapter):
    try:
        while True:
            duplicates = []
            ssids = [cell.ssid for cell in Cell.all(adapter)]
            for ssid in ssids:
                if ssids.count(ssid) > 1 and ssid not in duplicates:
                    duplicates.append(ssid)

            for duplicate in duplicates:
                print("[Evil-Twin Detector]: Warning - Found multiple wifi networks with the same SSID: {}".format(duplicate))
            sleep(time)
    except KeyboardInterrupt:
        print("[Evil-Twin Detector]: Terminating")


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