#!/bin/bash
# PiNAT installer for debian-based distros, initially writted for Kali

# Run as root
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

# Install dependencies
apt update -y
apt install cmake libpcap-dev libssl-dev ebtables ethtool python3-venv hostapd -y

#create_ap
git clone https://github.com/oblique/create_ap
cd create_ap
make install
cd ../
rm -rf create_ap

# Install libtins

git clone https://github.com/mfontanini/libtins.git
cd libtins
mkdir build
cd build
cmake ../
make
make install

#add the library to the shared object path
echo "/usr/local/lib" > /etc/ld.so.conf.d/libtins.conf
ldconfig

#remove the repo
cd ../../
rm -rf libtins/

cd ../
#compile pinat
make # build pinat library
touch bin/__init__.py # for auto completetion

#create python virtual environment and install depecdencies
python3 -m venv venv
source venv/bin/activate
pip install wheel
pip install -r requirements.txt
deactivate
