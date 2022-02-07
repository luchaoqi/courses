#!/usr/bin/env bash

# read from command line
pid=$1
while kill -0 $pid 2>/dev/null; do
    sleep 1 # check every second to save cpu
done
ls
