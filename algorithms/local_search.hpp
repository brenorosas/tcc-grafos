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
        bool improved_at = false;
        vector<int> best_route_at_moment = route;
        Cost best_cost_at_moment = cost;

        // 1 - Swap two adjacent nodes
        for (int i = 1; i < best_route_at_moment.size() - 2; i++) {
            swap(best_route_at_moment[i], best_route_at_moment[i + 1]);
            Cost current_cost = calculate_total_cost(adjacency_matrix, best_route_at_moment);
            if (current_cost.fitness() > best_cost_at_moment.fitness()) {
                best_cost_at_moment = current_cost;
                best_route_at_moment = best_route_at_moment;
                improved_at = true;
            }
            swap(best_route_at_moment[i], best_route_at_moment[i + 1]);
        }

        if (improved_at) {
            route = best_route_at_moment;
            cost = best_cost_at_moment;
            improved_at = false;
            improved = true;
        }

        // 2 - Remove a node and insert other that is not in the route
        unordered_set<int> current_nodes_1(route.begin(), route.end());
        for (int i = 1; i < route.size() - 1; i++) {
            for (int j = 0; j < adjacency_matrix.size(); j++) {
                if (current_nodes_1.count(j) == 0) {
                    vector<int> new_route = route;
                    new_route.erase(new_route.begin() + i);
                    new_route.insert(new_route.begin() + i, j);
                    Cost current_cost = calculate_total_cost(adjacency_matrix, new_route);
                    if (current_cost.is_inside_limits(limits) && current_cost.fitness() > best_cost_at_moment.fitness()) {
                        best_cost_at_moment = current_cost;
                        best_route_at_moment = new_route;
                        improved_at = true;
                    }
                }
            }
        }

       if (improved_at) {
            route = best_route_at_moment;
            cost = best_cost_at_moment;
            improved_at = false;
            improved = true;
        }

        unordered_set<int> current_nodes_2(route.begin(), route.end());
        // 3 - Add a new node to the route
        for (int j = 0; j < adjacency_matrix.size(); j++) {
            if (current_nodes_2.count(j) == 0) {
                for (int i = 1; i < route.size(); i++) {
                    vector<int> new_route = route;
                    new_route.insert(new_route.begin() + i, j);
                    Cost current_cost = calculate_total_cost(adjacency_matrix, new_route);
                    if (current_cost.is_inside_limits(limits) && current_cost.fitness() > best_cost_at_moment.fitness()) {
                        best_cost_at_moment = current_cost;
                        best_route_at_moment = new_route;
                        improved_at = true;
                    }
                }
            }
        }

        improved |= improved_at;

        if (!improved) {
            break;
        }

        route = best_route_at_moment;
        cost = best_cost_at_moment;
    }
}