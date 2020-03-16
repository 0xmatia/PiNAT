# PiNAT installer for arch-based distros, initially writted for Manjaro

# Run as root
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

# Install dependencies from arch repo
pacman -Syy cmake libpcap openssl create_ap ebtables ethtool wireless_tools --noconfirm

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
pip install -r requirments.txt
deactivate
