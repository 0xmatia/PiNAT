from ipaddress import IPv4Network, AddressValueError
import sqlite3
import pathlib

def main():
    init()
    range = input("Enter IP range (With CIDR notation): ")
    path = pathlib.Path(__file__).parent.absolute()
    conn = sqlite3.connect(path/'example.db')
    c = conn.cursor()
    try:
        for ip in IPv4Network(range, strict=False):
            c.execute("INSERT INTO KNOWN_IPS (IP) VALUES(?)", str(ip))
            print(ip)
        conn.commit()
        conn.close()
    except AddressValueError:
        print("Please enter valid IP range")


def init():
    path = pathlib.Path(__file__).parent.absolute()
    conn = sqlite3.connect(path/'example.db')
    c = conn.cursor()

    c.execute("CREATE TABLE IF NOT EXISTS KNOWN_IPS (id INTEGER PRIMARY KEY AUTOINCREMENT,\
         IP INTEGER NOT NULL);")
    
    conn.commit()
    conn.close()

if __name__ == "__main__":
    main()