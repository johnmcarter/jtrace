#!/bin/bash

# Created: 2021/12/15 
# Last modified: 2024/07/01 
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

source_dir="$1"

echo "[${GRN}INFO${END}] Entering directory '$source_dir'"
cd "$source_dir" || { echo "[${RED}ERROR${END}] Failed to enter directory '$source_dir'"; exit 1; }

echo "[${GRN}INFO${END}] Compiling jtrace executable"
make || { echo "[${RED}ERROR${END}] Compilation failed"; exit 1; }

echo "[${GRN}INFO${END}] Installing jtrace as an executable script in /usr/bin"
cat > /usr/bin/jtrace <<EOF
#!/bin/bash

"${source_dir}/jtrace" "\$@"
EOF

chmod +x /usr/bin/jtrace || { echo "[${RED}ERROR${END}] Failed to make /usr/bin/jtrace executable"; exit 1; }

echo "[${GRN}SUCCESS${END}] jtrace installation successful!"
