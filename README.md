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
the program to his specific needs, or add functionality to the default analasys 
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

### installation Instructions

To make things easier, there are two installation scripts that should make the installation process much simpler. There is one for Ubuntu based systems and one for Arch based systems.
To run them, go to the installer_scripts folder and run the correct one:

```bash
cd installer_scripts/
./installer_<arch/debian>.sh
```

Now you should have PiNAT installed!

## Using PiNAT

There are two main scripts used to operate the program: ```./run.sh``` and ```./run_api.sh```.

### Running PiNAT

> Note: Running PiNAT requires superuser privileges.

First, make sure your machine is connected to the internet via etherent cable, and that you have you wireless adapter turned on.
PiNAT requires four parameters to run:
* Ethernet adapter name
* Wireless adapter name
* SSID
* Network passphrase

> Note: You can find your adapters' names with the IP command.

Once you run the program with ```./run.sh``` you'll be asked to enter those parameters. After that, it should take a few seconds for the program to initialize itself.
Now you can connect to the new WiFi network you just created and start using PiNAT!

#### Using a config file

Entering these four parameters eveytime you want to run PiNAT is annoying. Luckily, PiNAT can read these settings from a config file so you don't have to supply the them manually every run!
To use the config file, create a file named ```config.txt``` in the root folder of PiNAT and supply the parameters in the following format:

```
hotspot_interface=<your wifi adapter name>
internet_interface=<Ethernet adapter name>
ssid=<wifi name>
pass=<wifi password>
```

After you save the file and run PiNAT again, PiNAT should read the parameters from the config file and run automatically. Neat!

> Note: You can stop the program at any time with ```Ctrl+C```. If for some reason the program crashes and you can't access the interent, run the following command: ```create_ap --stop <wifi_adapter_name>```

### Using the RESTFul API

PiNAT provides an easy way to access plugin logs and program information using a very simple API. Running is as easy as running ```./run_api.sh```.
You can query the server using GET and POST methods to get reponses, it is very intuitive. Because it is an API, anyone could build a beautiful GUI interface that makes interacting with the program much more fun!
We provide a user interface as an android application that simply connects to the server and displays the information nicely. Nothing special.
You can build the apk from source, located in the Client directory.

## Built With

* [Flask](url) - The web framework used
* [Libtins](url) - The library for sniffing and packet-crafting
* [create_ap](url) - Used to turn on AP as bridge


## Develop plugins
Developing plugins is pretty straightforward. 

## Internals
The [sniffer](##What is PiNAT?) component sniffs packets on the wifi interface, and passes them to the plugins. Plugins located inside the Plugins folder will be loaded at runtime, and any packets sniffed will go through them. Each plugin can decide whether to forward or drop each packet. The plugins have access to the packets through a library we coded in C++ and compiled to python. We sniff, craft and extract information from packets using the libtins library.
Routing and general network maniuplation is done through ebtables.

## Authors

* **Elad Matia** - [JavaMatia](https://gitlab.com/JavaMatia)
* **Ofri Marx** - [ofri_marx](https://gitlab.com/ofri_marx)


## License

This project is licensed under the Apache 2.0 License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

This project was written during our third year in the [Magshimim](https://www.magshimim.cyber.org.il/) 
program with the help of several people from and out of Magshimim.

Special thanks to *Saar Yakolav* and *Yaron Mor*
