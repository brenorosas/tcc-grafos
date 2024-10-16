#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "../structs/cost.hpp"

using namespace std;

vector<int> make_random_route(vector<vector<Cost>>& adjacency_matrix) {
    random_device rd;
    mt19937 g(rd());

    vector<int> route(adjacency_matrix.size());

    for (int i = 0; i < route.size(); i++) {
        route[i] = i;
    }

    shuffle(route.begin() + 1, route.end(), g);

    route.push_back(route[0]);
    return route;
}