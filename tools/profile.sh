#!/usr/bin/env bash


# Cd into project root directory
cd "$(dirname "$0")"/..
pwd -P

readonly EXECUTABLE="./benchmark/awx"
if [[ ! -e "$EXECUTABLE" ]]; then
		echo "ERROR: $EXECUTABLE does not exit" 1>&2
		exit 1
fi

valgrind --tool=callgrind \
				 --callgrind-out-file=callgrind.out.awx \
				 "$EXECUTABLE" $@
