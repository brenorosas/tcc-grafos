#!/bin/bash
set -e

#../compile-statement.sh statement.md
# g++ -std=c++11 gen.cpp -O2

# Instance 93, 94, and 95 tests from 1 to 30
for i in $(seq 93 95); do
    echo "Generating results for instance $i..."
    mkdir -p "results/grasp/instance$i"
    for j in $(seq 1 30); do
        echo "Generating result $j for instance $i..."
        ./grasp < "instances/instance_$i.txt" > "results/grasp/instance$i/result$j.out"
    done
done
