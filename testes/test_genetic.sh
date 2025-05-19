#!/bin/bash
set -e

#../compile-statement.sh statement.md
# g++ -std=c++11 gen.cpp -O2

echo "Generating results for instances..."
for i in $(seq 1 105); do
    echo "Generating results for instance $i..."
    mkdir -p "results/genetic/instance$i"
    for j in $(seq 1 30); do
        echo "Generating result $j for instance $i..."
        ./genetic < "instances/instance_$i.txt" > "results/genetic/instance$i/result$j.out"
    done
done
