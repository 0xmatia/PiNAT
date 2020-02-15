import subprocess
from time import sleep

def check_interface(interface):
    """
    Returns a valid interface name
    """
    proc = subprocess.Popen(["nmcli", "-f", "DEVICE", "device"], stdout=subprocess.PIPE)
    (available_adapters, _) = proc.communicate()

    # # Does the adapter exist?
    return interface + " "  in available_adapters.decode()


def check_password(passphrase):
    """
    Returns a valid WPA2 password
    """
    return 8 <= len(passphrase) <= 63


def check_ssid(ssid):
    """
    Returns a valid SSID
    """
    return 1 < len(ssid) < 32 and '|' not in ssid


def _turn_on(wifi_adapter, etherent_adapter, ssid, password, router_mac):
    """
    Turns hotspot on
    """
    
    subprocess.Popen(["create_ap", "-m", "bridge", wifi_adapter, etherent_adapter, \
         ssid, password, "--daemon", "--no-virt"])

    subprocess.Popen(["ebtables", "-A", "FORWARD", "--logical-in", "br0", "-d", router_mac, "-j", "DROP"]).wait()

    subprocess.Popen(["ethtool", "-K", wifi_adapter, "gso", "off"]).wait()
    subprocess.Popen(["ethtool", "-K", wifi_adapter, "gro", "off"]).wait()

    sleep(6)
    print("Hotspot has been activated")


def cleanup(wifi_interface, eth_interface, router_mac):
    """ 
    Turns off the hotspot if neccessry
    """
    subprocess.Popen(["create_ap", "--stop", wifi_interface]).wait()
    subprocess.Popen(["ebtables", "-D", "FORWARD", "--logical-in", "br0", "-d", router_mac, "-j", "DROP"]).wait()
    subprocess.Popen(["ethtool", "-K", wifi_interface, "gso", "on"]).wait()
    subprocess.Popen(["ethtool", "-K", wifi_interface, "gro", "on"]).wait()

    print("Hotspot deactivated")


def read_config():
    try:
        f = open("config.txt", "r")
    except OSError:
        return None, None, None, None

    wifi_adapter = None
    secondry_wifi = None
    eth_adapter = None
    ssid = None
    password = None
    for line in f.read().split("\n"):
        try:
            key, value = line.split("=")
        except:
            continue
        if key == "wireless_adapter":
            wifi_adapter = value
        elif key == "secondry_adapter":
            secondry_wifi = value
        elif key == "regular_adapter":
            eth_adapter = value
        elif key == "ssid":
            ssid = value
        elif key == "pass":
            password = value
    f.close()

    return wifi_adapter, secondry_wifi, eth_adapter, ssid, password


def init_hotspot(router_mac):
    wifi_adapter, secondry_wifi, eth_adapter, ssid, password = read_config()

    if wifi_adapter == None:
        wifi_adapter = input("Wifi interface name: ")
    else:
        print("wifi_adapter = " + wifi_adapter)
    if not check_interface(wifi_adapter):
        raise Exception("interface {} does not exist".format(wifi_adapter))

    if secondry_wifi == None:
        secondry_wifi = input("Secondry wifi interface name: ")
    else:
        print("secondry_adapter = " + secondry_wifi)
    if not check_interface(secondry_wifi):
        raise Exception("interface {} does not exist".format(secondry_wifi))


    if eth_adapter == None:
        eth_adapter = input("Ethernet interface name: ")
    else:
        print("regular_adapter = " + eth_adapter)
    if not check_interface(eth_adapter):
        raise Exception("interface {} does not exist".format(eth_adapter))


    if ssid == None:
        ssid = input("Wifi name: ")
    else:
        print("ssid = " + ssid)
    if not check_ssid(ssid):
        raise Exception("Invalid ssid: " + ssid)
    

    if password == None:
        password = input("Wifi password: ")
    else:
        print("password = {}".format(password))
    if not check_password(password):
        raise Exception("Invalid WPA2 password: {}\nPassword must be 8-63 chars long".format(password))
    

    # Start hotspot:
    _turn_on(wifi_adapter, eth_adapter, ssid, password, router_mac)
    return wifi_adapter, eth_adapter, secondry_wifi
