#pragma once

#include <iostream>

using namespace std;

struct Cost {
    int distanceMeters = 0;
    int durationSeconds = 0;

    void operator+=(const Cost& other) {
        distanceMeters += other.distanceMeters;
        durationSeconds += other.durationSeconds;
    }
};