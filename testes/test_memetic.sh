#!/bin/bash
set -e

#../compile-statement.sh statement.md
# g++ -std=c++11 gen.cpp -O2

echo "Generating results for instances..."
for i in $(seq 101 105); do
    echo "Generating results for instance $i..."
    mkdir -p "results/memetic/instance$i"
    for j in $(seq 1 30); do
        echo "Generating result $j for instance $i..."
        ./memetic < "instances/instance_$i.txt" > "results/memetic/instance$i/result$j.out"
    done
done
