#!/bin/bash

output=$(ls lib/) 
gcc_command="gcc -o main.out main.c"

for item in $output; do
	if [[ $item == *.h ]]; then
		gcc_command="$gcc_command lib/$item"

	fi
done

$gcc_command
echo

