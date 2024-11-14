#pragma once

#include <iostream>

using namespace std;

struct Cost {
    int distanceMeters = 0;
    int durationSeconds = 0;
    int dendeInMililiters = 0;

    void operator+=(const Cost& other) {
        distanceMeters += other.distanceMeters;
        durationSeconds += other.durationSeconds;
        dendeInMililiters += other.dendeInMililiters;
    }

    bool operator<(const Cost& other) const {
        return distanceMeters < other.distanceMeters;
    }

    bool operator>(const Cost& other) const {
        return distanceMeters > other.distanceMeters;
    }

    bool operator==(const Cost& other) const {
        return distanceMeters == other.distanceMeters && durationSeconds == other.durationSeconds;
    }
};

// distancia, duração, tempo de carga, limitante total de tempo, quantidade de carga.