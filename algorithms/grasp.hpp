#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "../structs/cost.hpp"
#include "make_random_route.hpp"
#include "calculate_total_cost.hpp"

using namespace std;

void local_search(vector<vector<Cost>>& adjacency_matrix, vector<int>& route) {
    Cost cost = calculate_total_cost(adjacency_matrix, route);

    while (true) {
        bool improved = false;
        vector<int> best_route_at_moment = route;
        Cost best_cost_at_moment = cost;
        for (int i = 1; i < best_route_at_moment.size() - 2; i++) {
            swap(best_route_at_moment[i], best_route_at_moment[i + 1]);
            Cost current_cost = calculate_total_cost(adjacency_matrix, best_route_at_moment);
            if (current_cost < best_cost_at_moment) {
                best_cost_at_moment = current_cost;
                best_route_at_moment = best_route_at_moment;
                improved = true;
            }
            swap(best_route_at_moment[i], best_route_at_moment[i + 1]);
        }

        if (!improved) {
            break;
        }

        route = best_route_at_moment;
        cost = best_cost_at_moment;
    }
}


vector<int> grasp(vector<vector<Cost>>& adjacency_matrix, Limitations limits) {
    int max_iterations = 100000;

    vector<int> best_route = make_random_route(adjacency_matrix, 0, limits);
    Cost best_cost = {numeric_limits<int>::max(), numeric_limits<int>::max(), numeric_limits<int>::max()};

    for (int i = 0; i < max_iterations; i++) {
        vector<int> route = make_random_route(adjacency_matrix, 0.5, limits);
        local_search(adjacency_matrix, route);

        Cost cost = calculate_total_cost(adjacency_matrix, route);

        // Verifica se o custo está dentro dos limites
        if (cost.dendeInMililiters <= limits.maxDendeInMililiters &&
            cost.dendeInMililiters >= limits.minDendeInMililiters &&
            cost.durationSeconds <= limits.maxCollectionTimeInSeconds &&
            cost < best_cost) {

            best_cost = cost;
            best_route = route;
        }
    }

    return best_route;
}