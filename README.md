# PiNAT

Open source, modular network monitoring tool

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

* Three interfaces, one of them has to be ethernet!

* Libtins
* Python3 + libraries specified in requirements.txt
* ethtool
* create_ap
* (optional) virtual python enivronment
...

### Installing

Follow these instruction to get PiNAT setup and ready to go

Firstly, clone the repo:

```
git clone https://gitlab.com/magsh-2019/14/1402-pinat-
```

Install all requirments (git, apt, pacman)

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
## Running the tests

## Built With

* [Flask](url) - The web framework used
* [Libtins](url) - Dependency Management
* [create_ap](url) - Used to generate RSS Feeds


## Authors

* **Elad Matia** - [JavaMatia](https://gitlab.com/JavaMatia)
* **Ofri Marx** - [ofri_marx](https://gitlab.com/ofri_marx)


## License

This project is licensed under the <> License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

More stuff