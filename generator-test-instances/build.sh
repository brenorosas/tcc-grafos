#!/bin/bash
set -e

# Make the script executable
chmod +x "$0"

#../compile-statement.sh statement.md
rm -rf instances
mkdir -p instances

# Compile the generator
g++ -std=c++11 gen.cpp -o gen

# Create separate directories for test and Irace instances
mkdir -p output/test_instances
mkdir -p output/irace_instances

echo "Generating instances..."

# Generate test instances (1-105)
for i in {1..105}
do
    echo "Generating test instance $i..."
    ./gen 1 $i > output/test_instances/instance_$i.txt
done

# Generate Irace instances (106-119)
for i in {106..119}
do
    echo "Generating Irace instance $i..."
    ./gen 1 $i > output/irace_instances/instance_$i.txt
done

echo "All instances generated successfully!"
echo "Test instances (1-105) are in output/test_instances/"
echo "Irace instances (106-119) are in output/irace_instances/"

