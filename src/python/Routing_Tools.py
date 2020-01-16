import subprocess
from time import sleep

def _get_interface():
    """
    Returns a valid interface name
    """
    proc = subprocess.Popen(["nmcli", "-f", "DEVICE", "device"], stdout=subprocess.PIPE)
    (available_adapters, _) = proc.communicate()

    wifi_adapter = input("Wifi interface name: ")
    etherent_adapter = input("Ethernet interface name: ")

    # # Does the adapter exists?
    if wifi_adapter + " " not in available_adapters.decode() or \
        etherent_adapter + " " not in available_adapters.decode():
            raise Exception("One of the specified adapters doesn't exist")
    
    return wifi_adapter, etherent_adapter


def _get_password():
    """
    Returns a valid WPA2 password
    """
    passphrase = input("Wifi password: ")
    if len(passphrase) > 63 or len(passphrase) < 8:
        raise Exception("Invalid WPA2 password. Password must be 8-63 chars long.")
  
    return passphrase



def _get_ssid():
    """
    Returns a valid SSID
    """
    ssid = input("Wifi Name: ")
    if len(ssid) > 32 or len(ssid) < 1 or '|' in ssid:
        raise Exception("Invalid SSID.")

    return ssid


def _turn_on(wifi_adapter, etherent_adapter, ssid, password, router_mac):
    """
    Turns hotspot on
    """
    
    subprocess.Popen(["create_ap", "-m", "bridge", wifi_adapter, etherent_adapter, \
         ssid, password, "--daemon", "--no-virt"])

    #subprocess.Popen(["ebtables", "-A", "FORWARD", "--logical-in", "br0", "-d", router_mac, "-j", "DROP"]).wait()

    sleep(6) #how to get rid of it

    print("Hotspot has been activated")

def cleanup(wifi_interface, eth_interface, router_mac):
    """ 
    Turns off the hotspot if neccessry
    """
    subprocess.Popen(["create_ap", "--stop", wifi_interface]).wait()
    subprocess.Popen(["ebtables", "-D", "FORWARD", "--logical-in", "br0", "-d", router_mac, "-j", "DROP"]).wait()

    print("Hotspot deactivated")


def init_hotspot(router_mac):
    wifi_adapter, eth_adapter = _get_interface()
    ssid = _get_ssid()
    password = _get_password()
    # Start hotspot:
    _turn_on(wifi_adapter, eth_adapter, ssid, password, router_mac)
    return wifi_adapter, eth_adapter
