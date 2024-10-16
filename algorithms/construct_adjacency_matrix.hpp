#pragma once

#include <iostream>
#include "../structs/cost.hpp"
#include "../structs/input.hpp"

using namespace std;

vector<vector<Cost>> construct_adjacency_matrix(Input& input) {
    vector<vector<Cost>> adjacency_matrix(input.locations.size(), vector<Cost>(input.locations.size(), Cost()));

    for (const auto& route : input.routes) {
        adjacency_matrix[route.originIndex][route.destinationIndex].distanceMeters = route.distanceMeters;
        adjacency_matrix[route.originIndex][route.destinationIndex].durationSeconds = route.durationSeconds;
    }

    return adjacency_matrix;
}