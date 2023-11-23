#!/bin/bash

# compile the test script
gcc -o run_test test/test.c

# Run the Docker container
./run_test

# clean up
rm -r run_test