#!/usr/bin/python3

from sys import path
from sys import argv
path.append("src/python")

import Routing_Tools
from Plugin_Observer import plugin_system
from bin import pynat


def main():
    plugins = {}

    # Start hotspot and routing
    try:
        wifi_adapter, eth_adapter = Routing_Tools.init_hotspot(argv[1])
    except Exception as e:
        print (e)
        print("PiNAT is terminating")
        exit(1)

    # Load the plugins
    plugin_system_instance = plugin_system('Plugins')
    plugins = list(plugin_system_instance.reload().values())
    plugins.sort(key=lambda x: x.priority)

    try:
        sniffer = pynat.Sniffer(wifi_adapter, "", eth_adapter, argv[1])
        pynat.init_core(sniffer.get_pool())
    except Exception as e:
        print("Exception: ", end="")
        print(e)
        print("terminating now")
        Routing_Tools.cleanup(wifi_adapter, eth_adapter, argv[1])
        exit(1)

    for plugin in plugins:
            plugin.setup()

    try:
        while True:
            packet = sniffer.get_packet()
<<<<<<< HEAD
            for plugin in plugins.values():
                plugin.process(packet)
            #sniffer.forward_packet(packet)
=======
            for plugin in plugins:
                packet = plugin.process(packet)
                if packet == None:
                    break
            if packet != None:
                sniffer.forward_packet(packet)
>>>>>>> 255f494e280fbf8bc1995be19ece7a63c89cb45b
    except KeyboardInterrupt:
        print("Interrupt detected, terminating now")
    except Exception as e:
        print("Exception: ", end="")
        print(e)
        print("terminating now")
    
    for plugin in plugins:
        plugin.teardown()

    Routing_Tools.cleanup(wifi_adapter, eth_adapter, argv[1])


if __name__ == "__main__":
    main()


