from os import system



def turn_on():
    shared_adapter = input("Please enter the adapter name: ")
    ssid = input("Wifi Name: ")
    passphrase = input("Wifi password: ")

    system(f"nmcli dev wifi hotspot ifname {shared_adapter} ssid {ssid} password {passphrase}")

def turn_off():
    # first, turn the connection off
    system("nmcli con down Hotspot") # Hotspot - the connection name locally, should be the same every time
    system("nmcli con delete Hotspot")

def main():
    choice = int(input("Choose: \n1 - Turn on\n2 - Turn off\n"))
    if choice == 1:
        turn_on()
    else:
        turn_off()

if __name__ == "__main__":
    main()