#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "../structs/cost.hpp"
#include "make_random_route.hpp"
#include "calculate_total_cost.hpp"
#include "local_search.hpp"

using namespace std;

double calculate_fitness(vector<int>& route, vector<vector<Cost>>& adjacency_matrix, Limitations& limits) {
    Cost cost = calculate_total_cost(adjacency_matrix, route);

    if (!cost.is_inside_limits(limits)) {
        return numeric_limits<double>::min();
    }

    return cost.fitness();
}

vector<int> crossover(vector<int> parent1, vector<int> parent2) {
    random_device rd;
    mt19937 g(rd());

    int n = parent1.size();
    int k = g() % int(n * 0.2) + int(n * 0.2);
    vector<int> result = {0};
    unordered_set<int> used_indices = {0};

    while (!parent1.empty()) {
        int n11 = min(k, (int)parent1.size());
        for (int i = 0; i < n11; i++) {
            if (!used_indices.count(parent1[i])) {
                result.push_back(parent1[i]);
                used_indices.insert(parent1[i]);
            }
        }

        vector<int> new_parent1;
        vector<int> new_parent2;

        for (int i = 0; i < parent1.size(); i++) {
            if (!used_indices.count(parent1[i])) {
                new_parent1.push_back(parent1[i]);
            }
        }

        for (int i = 0; i < parent2.size(); i++) {
            if (!used_indices.count(parent2[i])) {
                new_parent2.push_back(parent2[i]);
            }
        }

        // exchange parent1 and parent2
        parent2 = new_parent1;
        parent1 = new_parent2;
    }

    result.push_back(0);

    return result;
}

void mutation(vector<int>& route) {
    random_device rd;
    mt19937 g(rd());
    int n = route.size();
    int k = g() % n;
    swap(route[k], route[g() % n]);
}

vector<int> genetic_algorithm(vector<vector<Cost>>& adjacency_matrix, Limitations& limits, bool is_memetic = false, double epsilon = 0.5, int population_size = 100, int generations = 1000) {
    random_device rd;
    mt19937 g(rd());

    vector<vector<int>> population;
    while (population.size() < population_size) {
        vector<int> route = make_random_route(adjacency_matrix, epsilon, limits);
        Cost cost = calculate_total_cost(adjacency_matrix, route);
        if (cost.is_inside_limits(limits))
            population.push_back(route);
    }

    for (int gen = 0; gen < generations; gen++) {
        vector<pair<double, vector<int>>> evaluated_population;
        for (auto& individual : population) {
            double fitness = calculate_fitness(individual, adjacency_matrix, limits);
            evaluated_population.push_back({fitness, individual});
        }

        sort(evaluated_population.rbegin(), evaluated_population.rend());

        // 10 best individuals
        vector<vector<int>> new_population;
        for (int i = 0; i < 10; i++) {
            new_population.push_back(evaluated_population[i].second);
        }

        // 15 random individuals, not in the best 10
        while (new_population.size() < population_size / 2) {
            int random_idx = g() % evaluated_population.size();
            if (find(new_population.begin(), new_population.end(), evaluated_population[random_idx].second) == new_population.end()) {
                new_population.push_back(evaluated_population[random_idx].second);
            }
        }

        while (new_population.size() < population_size) {
            int parent1_idx = g() % (population_size / 2);
            int parent2_idx = g() % (population_size / 2);
            vector<int> child = crossover(new_population[parent1_idx], new_population[parent2_idx]);
            mutation(child);
            if (is_memetic)
                local_search(adjacency_matrix, child, limits);
            Cost cost = calculate_total_cost(adjacency_matrix, child);
            if (cost.is_inside_limits(limits))
                new_population.push_back(child);
        }

        population = new_population;
    }

    return population[0];
}

// adici