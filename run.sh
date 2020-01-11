#!/bin/bash

if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

MAC=$(ip neigh | grep $(ip route show match 0/0 | awk 'NR==1{print $3}') -w | awk 'NR==1{print $5}')

python3 -B PiNAT.py $MAC