#!/bin/bash

if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

#MAC=$(ip neigh | grep $(ip route show match 0/0 | awk '{print $3}') -w | awk '{print $5}')

python3 -B PiNAT.py 08:6a:0a:22:12:1a