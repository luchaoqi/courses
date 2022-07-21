#!/usr/bin/env bash

cnt=0
while [[ "$?" -eq 0 ]]
do
	cnt=$((cnt+1))
	./random.sh &>> output.txt
done
echo "error after $cnt runs"
