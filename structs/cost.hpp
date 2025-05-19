#pragma once

#include <iostream>

using namespace std;

struct Cost {
    int distanceMeters = 0;
    int durationSeconds = 0;
    int dendeInDeciliters = 0;

    void operator+=(const Cost& other) {
        distanceMeters += other.distanceMeters;
        durationSeconds += other.durationSeconds;
        dendeInDeciliters += other.dendeInDeciliters;
    }

    // Order by distance, then by duration, then by dendeInDeciliters
    bool operator<(const Cost& other) const {
        if (distanceMeters != other.distanceMeters)
            return distanceMeters < other.distanceMeters;
        if (durationSeconds != other.durationSeconds)
            return durationSeconds < other.durationSeconds;
        return dendeInDeciliters > other.dendeInDeciliters;
    }

    // Order by duration, then by distance, then by dendeInDeciliters
    // bool operator<(const Cost& other) const {
    //     return durationSeconds < other.durationSeconds ||
    //            (durationSeconds == other.durationSeconds && distanceMeters < other.distanceMeters) ||
    //            (durationSeconds == other.durationSeconds && distanceMeters == other.distanceMeters &&
    //             dendeInDeciliters < other.dendeInDeciliters);
    // }

    // Order by dendeInDeciliters, then by distance, then by duration
    // bool operator<(const Cost& other) const {
    //     return dendeInDeciliters < other.dendeInDeciliters ||
    //            (dendeInDeciliters == other.dendeInDeciliters && distanceMeters < other.distanceMeters) ||
    //            (dendeInDeciliters == other.dendeInDeciliters && distanceMeters == other.distanceMeters &&
    //             durationSeconds < other.durationSeconds);
    // }

    // Collected dendeInDeciliters per distanceMeters
    // bool operator<(const Cost& other) const {
    //     return distance_per_dende() < other.distance_per_dende();
    // }

    double fitness() const {
        // α · X + β · Y - γ · Z
        // where X = distanceMeters, Y = durationSeconds, Z = dendeInDeciliters
        const double alpha = 0.6;  // weight for distance
        const double beta = 0.3;   // weight for duration
        const double gamma = 0.1;  // weight for dende
        return alpha * distanceMeters + beta * durationSeconds - gamma * dendeInDeciliters;
    }

    bool is_inside_limits(Limitations limits) const {
        return dendeInDeciliters <= limits.maxDendeInDeciliters &&
               durationSeconds <= limits.maxCollectionTimeInSeconds &&
               dendeInDeciliters >= limits.minDendeInDeciliters;
    }
};

// distancia, duração, tempo de carga, limitante total de tempo, quantidade de carga.