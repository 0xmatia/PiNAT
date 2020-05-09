# PiNAT

Open source, Modular Network Analyzing Tool

![pinat](peanut.png?raw=true)

## What is PiNAT?

PiNAT is an open source, modular network monitoring tool, built for small to 
medium sized private networks. It connects to the router with an ethernet cable 
from one adapter, and opens an access point from another adapter for other devices
to connect. 

![struct](TopLevel.png?raw=true)

PiNAT serves as a transparent bridge between connected devices and the router, 
with the options of sniffing network activity, blocking it and even modifying it
live. Network analysis is done by user written plugins and a few plugins which 
are supplied by us. The plugins are written in python, and are given access to 
network activity through a python library which we developed. With the special 
plugin system we constructed, every user is able to change the functionality of 
the program to his specific needs, or add functionality to the defualt analasys 
done by our plugins.

Some of the included plugins are:
*  ARP spoofing detector - analyzes arp requests and alerts when there is a
duplicate address
*  DSN spoofing detector - analyzes dns responses and compares with trusted dns
servers
*  IP blocker - blocks certain external ip addresses
*  Word Censor - Replaces text in raw tcp packets (such as non-compressed http responses and more)
*  AdBlocker - Blocks dns queries to known ad websites

## Getting Started

### Prerequisites

* A linux machine (Tested on Ubuntu and Arch)
* Two network adapters - wired and wireless. The wireless adapter has to support Virtual AP mode, so the host machine would have internet connection as well, as it is required by some plugins.

### installation Instruction

To make things easier, there are two installation scripts that should make the installation process much simpler. There is one for Ubuntu based systems and one for Arch based systems.
To run them, go to the installer_scripts folder and run the correct one:

```bash
cd installer_scripts/
./installer_<arch/debian>.sh
```

You should have now PiNAT installed!

### Using PiNAT

There are two main scripts that 

## Built With

* [Flask](url) - The web framework used
* [Libtins](url) - The library for sniffing and packet-crafting
* [create_ap](url) - Used to turn on AP as bridge


## Develop plugins


## Internals
a few words about how our project works


## Authors

* **Elad Matia** - [JavaMatia](https://gitlab.com/JavaMatia)
* **Ofri Marx** - [ofri_marx](https://gitlab.com/ofri_marx)


## License

This project is licensed under the <> License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

This project was written during our third year in the [Magshimim](https://www.magshimim.cyber.org.il/) 
program with the help of several people from and out of Magshimim.

Special thanks to [] and []
