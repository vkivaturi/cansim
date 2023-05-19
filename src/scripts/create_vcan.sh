#!/bin/bash
if [[ $# -eq 0 ]]; then
    echo "Error : Provide one argument (prefereably a number) which will be used as suffix for the new vcan interface"
    exit 1
fi
# Make sure the script runs with super user privileges.
[ "$UID" -eq 0 ] || exec sudo bash "$0" "$@"
# List current interfaces before creating a vcan
echo "--> Interfaces prior to adding the vcan"
ip link
# Load the kernel module.
modprobe vcan
# Create the virtual CAN interface.
ip link add dev vcan$1 type vcan
# Bring the virtual CAN interface online.
ip link set up vcan$1
echo "-->"
echo "--> Interfaces after adding the vcan"
ip link
