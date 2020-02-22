#!/bin/bash

if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

source venv/bin/activate
python RESTfulAPI.py
deactivate