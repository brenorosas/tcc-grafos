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

    // Order by distance, then by duration, then by reverse dendeInMililiters
    bool operator<(const Cost& other) const {
        return distanceMeters < other.distanceMeters ||
               (distanceMeters == other.distanceMeters && durationSeconds < other.durationSeconds) ||
               (distanceMeters == other.distanceMeters && durationSeconds == other.durationSeconds &&
                dendeInMililiters > other.dendeInMililiters);
    }

    // Order by duration, then by distance, then by reverse dendeInMililiters
    // bool operator<(const Cost& other) const {
    //     return durationSeconds < other.durationSeconds ||
    //            (durationSeconds == other.durationSeconds && distanceMeters < other.distanceMeters) ||
    //            (durationSeconds == other.durationSeconds && distanceMeters == other.distanceMeters &&
    //             dendeInMililiters > other.dendeInMililiters);
    // }

    // Order by reverse dendeInMililiters, then by distance, then by duration
    // bool operator<(const Cost& other) const {
    //     return dendeInMililiters < other.dendeInMililiters ||
    //            (dendeInMililiters == other.dendeInMililiters && distanceMeters < other.distanceMeters) ||
    //            (dendeInMililiters == other.dendeInMililiters && distanceMeters == other.distanceMeters &&
    //             durationSeconds < other.durationSeconds);
    // }


    // Collected dendeInMililiters per distanceMeters
    // bool operator<(const Cost& other) const {
    //     return distance_per_dende() < other.distance_per_dende();
    // }

    double distance_per_dende() const {
        return static_cast<double>(distanceMeters) / dendeInMililiters;
    }

    double fitness() const {
        return -0.6 * distanceMeters + -0.3 * durationSeconds + 0.1 * dendeInMililiters;
    }

    bool is_inside_limits(Limitations limits) const {
        return dendeInMililiters <= limits.maxDendeInMililiters &&
               durationSeconds <= limits.maxCollectionTimeInSeconds &&
               dendeInMililiters >= limits.minDendeInMililiters;
    }
};

// distancia, duração, tempo de carga, limitante total de tempo, quantidade de carga.