#!/bin/bash

# Author: John Carter
# Created: 2021/12/15 18:47:43
# Last modified: 2022/01/21 20:05:36
# Install jtrace on a Linux machine


RED=$'\e[1;31m'
GRN=$'\e[1;32m'
END=$'\e[0m'

help() {
   echo "[${RED}ERROR${END}] USAGE: $0 <qualified jtrace source code location>"
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

echo "[${GRN}INFO${END}] Entering directory '$1'"
cd $1

echo "[${GRN}INFO${END}] Compiling jtrace executable"
make

echo "[${GRN}INFO${END}] Installing jtrace as an executable script in /usr/bin"
cat > /usr/bin/jtrace <<EOF
#!/bin/bash

${1}/jtrace \$1
EOF

chmod +x /usr/bin/jtrace

if [[ $? -ne 0 ]]; then
    echo "[${RED}SUCCESS${END}] jtrace installation failed"
else 
    echo "[${GRN}SUCCESS${END}] jtrace installation successful!"
fi
