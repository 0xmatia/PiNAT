#!/usr/bin/python3

# Imports: We need PyNAT in order to connect the program to the CPP interface
import Routing_Tools


def main():
    # Start hotspot and routing
    try:
        Routing_Tools.init_hotspot()
    except Exception as e:
        print (e)
        print("PiNAT is terminating")
        exit(1)
    
    input()
    Routing_Tools.cleanup()
    # Start the plugin observer and register plugins in the plugin's folder



if __name__ == "__main__":
    main()


