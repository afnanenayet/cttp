#!/bin/bash

# Compile script for cttp. Checks for dependencies (cmake and make), then if 
# they are present, compiles the project
#
# Afnan Enayet

echo "Checking for build dependencies..."

# Ensure that all dependencies are present for compilation

# make/gmake
if ! command -v make > /dev/null or ! command -v gmake > /dev/null; then
    echo "error: need make utility"
    exit 1
fi

# cmake
if ! command -v cmake > /dev/null; then
    echo "error: need cmake"
    exit 1
fi

echo "All dependencies present"

echo "Building project..."

cmake . && make;

