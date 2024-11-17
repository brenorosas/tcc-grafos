#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "../structs/cost.hpp"
#include "make_random_route.hpp"
#include "calculate_total_cost.hpp"

using namespace std;

void local_search(vector<vector<Cost>>& adjacency_matrix, vector<int>& route, Limitations limits) {
    Cost cost = calculate_total_cost(adjacency_matrix, route);

    while (true) {
        bool improved = false;
        vector<int> best_route_at_moment = route;
        Cost best_cost_at_moment = cost;

        // 1 - Swap two adjacent nodes
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

        // 2 - Remove a node and insert other that is not in the route
        unordered_set<int> current_nodes(route.begin(), route.end());
        for (int i = 1; i < route.size() - 1; i++) {
            for (int j = 0; j < adjacency_matrix.size(); j++) {
                if (current_nodes.count(j) == 0) {
                    vector<int> new_route = route;
                    new_route.erase(new_route.begin() + i);
                    new_route.insert(new_route.begin() + i, j);
                    Cost current_cost = calculate_total_cost(adjacency_matrix, new_route);
                    if (current_cost.is_inside_limits(limits) && current_cost < best_cost_at_moment) {
                        best_cost_at_moment = current_cost;
                        best_route_at_moment = new_route;
                        improved = true;
                    }
                }
            }
        }

        // 3 - Add a new node to the route
        for (int j = 0; j < adjacency_matrix.size(); j++) {
            if (current_nodes.count(j) == 0) {
                for (int i = 1; i < route.size(); i++) {
                    vector<int> new_route = route;
                    new_route.insert(new_route.begin() + i, j);
                    Cost current_cost = calculate_total_cost(adjacency_matrix, new_route);
                    if (current_cost.is_inside_limits(limits) && current_cost < best_cost_at_moment) {
                        best_cost_at_moment = current_cost;
                        best_route_at_moment = new_route;
                        improved = true;
                    }
                }
            }
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
        local_search(adjacency_matrix, route, limits);

        Cost cost = calculate_total_cost(adjacency_matrix, route);

        if (cost.is_inside_limits(limits) && cost < best_cost) {
            best_cost = cost;
            best_route = route;
        }
    }

    return best_route;
}