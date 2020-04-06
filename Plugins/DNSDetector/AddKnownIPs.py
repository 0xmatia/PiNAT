from ipaddress import IPv4Network, AddressValueError
import sqlite3
import pathlib

PATH = str(pathlib.Path(__file__).parent.absolute()) + "/DNSDetector.db"
def main():
    init()
    range = input("Enter IP range (With CIDR notation): ")
    conn = sqlite3.connect(PATH)
    c = conn.cursor()
    try:
        for ip in IPv4Network(range, strict=False):
            print(str(ip))
            c.execute("INSERT INTO KNOWN_IPS (IP) VALUES(?)", (str(ip), ))
        conn.commit()
        conn.close()
    except AddressValueError:
        print("Please enter valid IP range")


def init():
    conn = sqlite3.connect(PATH)
    c = conn.cursor()

    c.execute("CREATE TABLE IF NOT EXISTS KNOWN_IPS (id INTEGER PRIMARY KEY AUTOINCREMENT,\
         IP INTEGER NOT NULL);")
    
    conn.commit()
    conn.close()

if __name__ == "__main__":
    main()