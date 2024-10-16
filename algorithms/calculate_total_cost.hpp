#pragma once

#include <iostream>
#include <vector>
#include "../structs/cost.hpp"

using namespace std;

Cost calculate_total_cost(vector<vector<Cost>>& adjacency_matrix, vector<int>& route) {
    Cost total_cost;

    for (int i = 0; i < route.size() - 1; i++) {
        total_cost += adjacency_matrix[route[i]][route[i + 1]];
    }

    return total_cost;
}