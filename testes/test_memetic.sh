#!/bin/bash
set -e

#../compile-statement.sh statement.md
# g++ -std=c++11 gen.cpp -O2

echo "Generating results for instances..."
for i in $(seq -f "%03g" 1 100); do
    echo "Generating results for instance $i..."
    mkdir -p "results/memetic/instance$i"
    for j in $(seq -f "%03g" 1 30); do
        echo "Generating result $j for instance $i..."
        ./memetic.exe < "instances/instance$i.in" > "results/memetic/instance$i/result$j.out"
    done
done
