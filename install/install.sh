#!/bin/bash

# Author: John Carter
# Created: 2021/12/15 18:47:43
# Last modified: 2022/01/20 08:30:31
# Install jtrace on a Linux machine


RED=$'\e[1;31m'
GRN=$'\e[1;32m'
END=$'\e[0m'

help() {
   echo "[${RED}ERROR${END}] USAGE: $0 <username>"
   exit 1
}

exit_process() {
    echo "[${RED}EXIT${END}] Script terminated"
    exit 1
}

trap exit_process INT TERM

if (( EUID != 0 )); then
   echo "[${RED}ERROR${END}] This script must be run as root" 
   exit 1
fi

if [[ $# -ne 1 ]]; then
    help
fi

echo "[${GRN}INFO${END}] Entering directory '/home/$1/jtrace'"
cd /home/$1/jtrace

echo "[${GRN}INFO${END}] Compiling jtrace executable"
make

echo "[${GRN}INFO${END}] Installing jtrace as an executable script in /usr/bin"
cat > /usr/bin/jtrace <<EOF
#!/bin/bash

/home/${1}/jtrace/jtrace \$1
EOF

chmod +x /usr/bin/jtrace

if [[ $? -ne 0 ]]; then
    echo "[${RED}SUCCESS${END}] jtrace installation failed"
else 
    echo "[${GRN}SUCCESS${END}] jtrace installation successful!"
fi