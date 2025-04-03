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
    // Remove depot from parents for crossover
    parent1.erase(parent1.begin());
    parent1.pop_back();
    parent2.erase(parent2.begin());
    parent2.pop_back();
    
    // Create two random crossover points
    int start = g() % (n - 2);
    int end = g() % (n - 2);
    if (start > end) swap(start, end);
    
    // Initialize child with -1 to mark empty positions
    vector<int> child(n - 2, -1);
    
    // Copy segment from parent1
    for (int i = start; i <= end; i++) {
        child[i] = parent1[i];
    }
    
    // Fill remaining positions with elements from parent2
    int j = 0;
    for (int i = 0; i < n - 2; i++) {
        if (child[i] == -1) {
            // Find next unused element from parent2
            while (j < n - 2) {
                if (find(child.begin(), child.end(), parent2[j]) == child.end()) {
                    child[i] = parent2[j];
                    break;
                }
                j++;
            }
        }
    }
    
    // Add depot at start and end
    child.insert(child.begin(), 0);
    child.push_back(0);
    
    return child;
}

void mutation(vector<int>& route) {
    random_device rd;
    mt19937 g(rd());
    int n = route.size();
    int k = g() % n;
    swap(route[k], route[g() % n]);
}

vector<int> genetic_algorithm(vector<vector<Cost>>& adjacency_matrix, Limitations& limits, bool is_memetic = false, double epsilon = 0.5, int population_size = 100, int generations = 1000, int best_cota = 10, int selection_size = 50) {
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
        for (int i = 0; i < best_cota; i++) {
            new_population.push_back(evaluated_population[i].second);
        }

        // 15 random individuals, not in the best 10
        while (new_population.size() < selection_size) {
            int random_idx = g() % evaluated_population.size();
            if (find(new_population.begin(), new_population.end(), evaluated_population[random_idx].second) == new_population.end()) {
                new_population.push_back(evaluated_population[random_idx].second);
            }
        }

        while (new_population.size() < population_size) {
            int parent1_idx = g() % selection_size;
            int parent2_idx = g() % selection_size;
            vector<int> child = crossover(new_population[parent1_idx], new_population[parent2_idx]);

            mutation(child);
            Cost cost_before = calculate_total_cost(adjacency_matrix, child);

            if (!cost_before.is_inside_limits(limits)) {
                continue;
            }

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