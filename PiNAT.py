#!/usr/bin/python3

from sys import path
path.append("src/python")

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
            for plugin in plugins.values():
                plugin.proccess(packet)
            sniffer.forward_packet(0)
            
    except KeyboardInterrupt:
        print("Interrupt detected, terminating now")
    except Exception:
        print("Exception happened, terminating now")
    
    Routing_Tools.cleanup()


if __name__ == "__main__":
    main()


