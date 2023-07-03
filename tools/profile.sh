#!/usr/bin/env bash

# This script is used for profiling of the interpreter
# Uses valgrind and assumes kcachegrind


# Cd into project root directory
cd "$(dirname "$0")"/..
pwd -P

readonly EXECUTABLE="./benchmark/awx"
readonly OUT_FILE="callgrind.out.awx "

# Check if benchmark build exists
if [[ ! -e "$EXECUTABLE" ]]; then
	echo "ERROR: $EXECUTABLE does not exit" 1>&2
	exit 1
fi

# Generate execution data using callgrind
valgrind --tool=callgrind \
	--callgrind-out-file="$OUT_FILE" \
	"$EXECUTABLE" $@

# Assume kcachegrind for profiling analysis
"${TOOL:-kcachegrind}" "$OUT_FILE"
