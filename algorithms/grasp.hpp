#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "../structs/cost.hpp"
#include "make_random_route.hpp"
#include "calculate_total_cost.hpp"
#include "local_search.hpp"

using namespace std;


vector<int> grasp(vector<vector<Cost>>& adjacency_matrix, Limitations limits, double epsilon = 0.5, int max_iterations = 100000) {
    vector<int> best_route = make_random_route(adjacency_matrix, epsilon, limits);
    Cost best_cost = {numeric_limits<int>::max(), numeric_limits<int>::max(), numeric_limits<int>::max()};
    vector<int> best_random_route = best_route;

    for (int i = 0; i < max_iterations; i++) {
        vector<int> random_route = make_random_route(adjacency_matrix, epsilon, limits);
        vector<int> route = random_route;
        local_search(adjacency_matrix, route, limits);

        Cost cost = calculate_total_cost(adjacency_matrix, route);

        if (cost.is_inside_limits(limits) && cost.fitness() > best_cost.fitness()) {
            best_cost = cost;
            best_route = route;
            best_random_route = random_route;
        }
    }

    // cout << "Best random route: ";
    // for (int node : best_random_route) {
    //     cout << node << " ";
    // }
    // cout << endl;

    return best_route;
}