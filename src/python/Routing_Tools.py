import subprocess
from time import sleep

def _get_interface():
    """
    Returns a valid interface name
    """
    proc = subprocess.Popen(["nmcli", "-f", "DEVICE", "device"], stdout=subprocess.PIPE)
    (available_adapters, _) = proc.communicate()

    shared_adapter = input("Please enter the adapter's name: ")

    # # Does the adapter exists?
    if shared_adapter not in available_adapters.decode():
         raise Exception("The specified network device does not exist!")
    
    return shared_adapter


def _get_password():
#     """
#     Returns a valid WPA2 password
#     """
    passphrase = input("Wifi password: ")
    if len(passphrase) > 63 or len(passphrase) < 8:
        raise Exception("Invalid WPA2 password. Password must be 8-63 chars long.")
  
    return passphrase



def _get_ssid():
#     """
#     Returns a valid SSID
#     """
    ssid = input("Wifi Name: ")
    if len(ssid) > 32 or len(ssid) < 1 or '|' in ssid:
        raise Exception("Invalid SSID.")

    return ssid


def _turn_on(shared_adapter, ssid, password):
#     """
#     Turns hotspot on
#     """
    subprocess.Popen(["nmcli", "dev", "wifi", "hotspot", "ifname", \
        shared_adapter, "ssid", ssid, "password", password], stdout=subprocess.DEVNULL).wait()
    print("Hotspot has been activated")
    

def cleanup():
    """ 
    Turns off the hotspot if neccessry
    """
    # Check if the hotspot is on:
    cmd = ["nmcli", "-f", "CONNECTION", "device"]
    close_hotspot = "nmcli con down Hotspot"
    delete_hotspot = "nmcli con delete Hotspot"

    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE)
    (adapter_status, _) = proc.communicate()
    
    # I probably need to find a better way to close the hotspot
    # other than relying on the fact that the local name is Hotspot everytime
    if "Hotspot" in adapter_status.decode(): #only now close the hotspot
        subprocess.Popen(close_hotspot.split(), stdout=subprocess.DEVNULL).wait()
        subprocess.Popen(delete_hotspot.split(), stdout=subprocess.DEVNULL).wait()
        print("Hotspot closed.")


def init_hotspot():
    shared_adapter = _get_interface()
    ssid = _get_ssid()
    password = _get_password()
    # Start hotspot:
    _turn_on(shared_adapter, ssid, password)
    return shared_adapter
