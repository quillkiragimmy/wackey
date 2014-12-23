#!/usr/bin/bash

orgDir="$(pwd)"
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
 
export DISPLAY=:0.0
export XAUTHORITY=/home/patricius/.Xauthority

button () {
	while read line; do
		echo $line| grep Set
	done
}

cd "$DIR"
while true; do
	./a.out neo_happy
	sleep 4
done


trap "cd $orgDir" SIGHUP SIGINT SIGTERM

