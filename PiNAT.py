#!/usr/bin/python3

# Imports: We need PyNAT in order to connect the program to the CPP interface
import Routing_Tools
from Plugin_Observer import plugin_system
# import PyNAT


def main():
    plugins = {}

    # Start hotspot and routing
    try:
        Routing_Tools.init_hotspot()
    except Exception as e:
        print (e)
        print("PiNAT is terminating")
        exit(1)
    
    # Load the plugins
    plugin_system_instance = plugin_system('Plugins')
    plugins = plugin_system_instance.reload()

    try: # this part will loop
        packet = "Blue"
        for plugin in plugins.values():
                plugin.proccess(packet)
        """
        Psuedo code:
        sniffer = PyNAT.sniffer()
        While True:
            packet = sniffer.getNextPacket()
            for plugin in plugins.values():
                plugin.proccess(packet)
        """
    except KeyboardInterrupt:
        print("Interrupt detected, terminating now")

    input()
    Routing_Tools.cleanup()


if __name__ == "__main__":
    main()


