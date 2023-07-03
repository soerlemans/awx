#!/usr/bin/env bash


# We want to CD into the root of the awx directory
cd "$(dirname "$0")"/..
pwd -P

# Record the AWX command
sudo perf record -F 99  -- ./debug/awx $@

# Create a flamegraph
sudo perf script report flamegraph --template "$(realpath flamegraph/flamegraph.html)"
