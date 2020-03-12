#!/usr/bin/python3

from sys import path
from sys import argv
import signal
import subprocess
from traceback import print_exc
path.append("src/python")

import Routing_Tools
from Plugin_Observer import plugin_system
from bin import pynat


def main():
    plugins = {}
    evil_twin_location = "src/python/evil_twin/evil_twin.py"

    # Start hotspot and routing
    try:
        wifi_adapter, eth_adapter = Routing_Tools.init_hotspot(argv[1])
    except Exception:
        print_exc()
        print("PiNAT is terminating")
        exit(1)


    # Load the plugins
    plugin_system_instance = plugin_system('Plugins')
    plugins = list(plugin_system_instance.reload().values())
    plugins.sort(key=lambda x: x.priority)

    try:
        sniffer = pynat.Sniffer("br0", "", "ap0", eth_adapter, argv[1])
        pynat.init_core(sniffer.get_pool())
    except Exception:
        print_exc()
        print("terminating now")
        Routing_Tools.cleanup(wifi_adapter, eth_adapter, argv[1])
        exit(1)

    for plugin in plugins:
            plugin.setup()

    # Start features that are not considered 'plugins'
    # 1. Evil twin detector
    evil_twin_proccess = subprocess.Popen(["python", evil_twin_location, "30", wifi_adapter])
    
    try:
        while True:
            packet = sniffer.get_packet()
            for plugin in plugins:
                packet = plugin.process(packet)
                if packet == None:
                    break
            if packet != None:
                sniffer.forward_packet(packet)
    except KeyboardInterrupt:
        print("Interrupt detected, terminating now")
    except Exception:
        print_exc()
        print("terminating now")
    
    for plugin in plugins:
        plugin.teardown()

    # temrminate evil-twin detector
    evil_twin_proccess.send_signal(signal.SIGINT)

    Routing_Tools.cleanup(wifi_adapter, eth_adapter, argv[1])


if __name__ == "__main__":
    main()


