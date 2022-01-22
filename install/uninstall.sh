#!/bin/bash

# Author: John Carter
# Created: 2021/12/15 18:47:43
# Last modified: 2022/01/21 20:02:55
# Uninstall jtrace on a Linux machine


RED=$'\e[1;31m'
GRN=$'\e[1;32m'
END=$'\e[0m'

exit_process() {
    echo "[${RED}EXIT${END}] Script terminated"
    exit 1
}

trap exit_process INT TERM

if (( EUID != 0 )); then
   echo "[${RED}ERROR${END}] This script must be run as root" 
   exit 1
fi

echo "[${GRN}INFO${END}] Removing jtrace executable"
make clean

echo "[${GRN}INFO${END}] Removing script in /usr/bin"
rm /usr/bin/jtrace 

if [[ $? -ne 0 ]]; then
    echo "[${RED}SUCCESS${END}] jtrace removal failed"
else 
    echo "[${GRN}SUCCESS${END}] jtrace removal successful"
fi