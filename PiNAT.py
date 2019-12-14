#!/usr/bin/python3

# Imports: We need PyNAT in order to connect the program to the CPP interface
import Routing_Tools
from Plugin_Observer import plugin_system
from bin import pynat


def main():
    plugins = {}

    # Start hotspot and routing
    try:
        adapter = Routing_Tools.init_hotspot()
    except Exception as e:
        print (e)
        print("PiNAT is terminating")
        exit(1)
    
    # Load the plugins
    plugin_system_instance = plugin_system('Plugins')
    plugins = plugin_system_instance.reload()

    try:
        sniffer = pynat.Sniffer(adapter, "")
        while True:
            packet = sniffer.get_packet()
            print(packet)
            for plugin in plugins.values():
                plugin.proccess(packet)
            
    except KeyboardInterrupt:
        print("Interrupt detected, terminating now")
    except Exception:
        pass
    
    Routing_Tools.cleanup()


if __name__ == "__main__":
    main()


