# PiNAT

Raspberry **Pi** **N**etwork **A**nalayzer **T**ool

![pinat](peanut.png?raw=true)

## What is PiNAT?

PiNAT is an open source, modular network monitoring tool, built for small to 
medium sized private networks. It connects to the router with an ethernet cable 
from one adapter, and opens an access point from another adapter for other devices
to connect. 

![struct](structure.png?raw=true)

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



## Getting Started

(Add instruction how to setup, features, restapi and how to develop plugins etc)

Clone the repo and follow the instruction on the [Installing] section.
run the program by executring ./run.sh as root. 
You may also create a file in the root of the project called config.txt and 
add the parameters in the following format:
x
y
z
zz

### Prerequisites

* Two interfaces, one of them has to be ethernet! (another interface is recommended)
* Libtins [add link to repo]
* Python3 + libraries specified in requirements.txt
* ethtool
* create_ap [add link to repo]
* (optional) virtual python enivronment
...

### Installing

Follow these instruction to get PiNAT setup and ready to go

Firstly, clone the repo:

```
git clone https://gitlab.com/magsh-2019/14/1402-pinat-
```

Install all requirments (libtins, python3, ethtool, create_ap)

```
sudo apt install ethtool
```

You may create virtual python environment and install all the python requirements
Note: You may have to install venv:

```
sudo apt install python3-venv
```

To create virtual environment:
Note: You may choose the environment name my specifing different value other
than 'env'
```
python3 -m venv env 
```
To activate the virtual environment, run:
```
source env/bin/activate
deactivate - will disable the virtual environemt
```

Now that you have virtual environment set up, you can install the required libraries:
```
pip install -r requirements.txt
```

You should be all setup now. Run ./run to start to program


## Built With

* [Flask](url) - The web framework used
* [Libtins](url) - Dependency Management
* [create_ap](url) - Used to generate RSS Feeds


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
