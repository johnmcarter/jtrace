#!/bin/bash 

# Author: John Carter
# Last modified: 12 July 2022

# cd to tracing directory
cd /sys/kernel/tracing

# mount the tracefs virtual filesystem
mount -t tracefs tracefs /sys/kernel/tracing

# enable the function tracer by adding it to current_tracer
echo function > current_tracer
