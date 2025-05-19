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
        return numeric_limits<double>::max();
    }

    return cost.fitness();
}

vector<int> crossover(vector<int> parent1, vector<int> parent2, vector<vector<Cost>>& adjacency_matrix, Limitations& limits) {
    random_device rd;
    mt19937 g(rd());
    
    // Basic validation - if either parent is invalid, return the valid one
    if (parent1.size() <= 2) return parent2;
    if (parent2.size() <= 2) return parent1;
    
    // Create child route starting with depot
    vector<int> child = {0};
    Cost current_cost = {0, 0, 0};
    
    // Get the middle segments of both parents (excluding depots)
    vector<int> middle1(parent1.begin() + 1, parent1.end() - 1);
    vector<int> middle2(parent2.begin() + 1, parent2.end() - 1);
    
    // If either parent has no middle segment, return the other parent
    if (middle1.empty()) return parent2;
    if (middle2.empty()) return parent1;
    
    // Choose a random crossover point
    int min_size = min(middle1.size(), middle2.size());
    if (min_size == 0) return parent1; // Safety check
    
    uniform_int_distribution<int> cross_dist(0, min_size - 1);
    int crossover_point = cross_dist(g);
    
    // Try to add customers from parent1 up to crossover point
    for (int i = 0; i < crossover_point; i++) {
        int customer = middle1[i];
        if (find(child.begin() + 1, child.end(), customer) != child.end()) {
            continue; // Skip if customer is already in the child
        }
        
        Cost new_cost = current_cost;
        new_cost += adjacency_matrix[child.back()][customer];
        
        // Check if we can add this customer and return to depot
        Cost check_cost = new_cost;
        check_cost += adjacency_matrix[customer][0];
        
        if (check_cost.is_inside_limits(limits)) {
            child.push_back(customer);
            current_cost = new_cost;
        }
    }
    
    // Add remaining customers from parent2 that are not already in the child
    for (int customer : middle2) {
        if (find(child.begin() + 1, child.end(), customer) != child.end()) {
            continue; // Skip if customer is already in the child
        }
        
        Cost new_cost = current_cost;
        new_cost += adjacency_matrix[child.back()][customer];
        
        // Check if we can add this customer and return to depot
        Cost check_cost = new_cost;
        check_cost += adjacency_matrix[customer][0];
        
        if (check_cost.is_inside_limits(limits)) {
            child.push_back(customer);
            current_cost = new_cost;
        }
    }

    // If child is invalid (only contains depot), return one of the parents
    if (child.size() <= 1) {
        return parent1;
    }

    // Add depot at the end
    child.push_back(0);
    
    // Final validation - ensure the route is valid
    Cost final_cost = calculate_total_cost(adjacency_matrix, child);
    if (!final_cost.is_inside_limits(limits)) {
        return parent1; // Return parent1 if the child is invalid
    }
    
    return child;
}

void mutation(vector<int>& route) {
    random_device rd;
    mt19937 g(rd());
    
    // Don't mutate if route is too short (just depot or depot + one customer)
    if (route.size() <= 3) return;
    
    // Choose two random positions excluding the depot at start and end
    uniform_int_distribution<int> pos_dist(1, route.size() - 2);
    int pos1 = pos_dist(g);
    int pos2 = pos_dist(g);
    
    // Swap the customers at these positions
    swap(route[pos1], route[pos2]);
}

vector<int> genetic_algorithm(vector<vector<Cost>>& adjacency_matrix, Limitations& limits, bool is_memetic = false, double epsilon = 0.5, int population_size = 100, int generations = 1000, int best_cota = 10, int selection_size = 50) {
    random_device rd;
    mt19937 g(rd());

    // Ensure population_size and selection_size are valid
    population_size = max(2, population_size);
    selection_size = max(2, min(selection_size, population_size));
    best_cota = max(1, min(best_cota, selection_size));

    vector<vector<int>> population;
    int attempts = 0;
    const int MAX_ATTEMPTS = population_size * 10; // Limit attempts to avoid infinite loop

    while (population.size() < population_size && attempts < MAX_ATTEMPTS) {
        vector<int> route = make_random_route(adjacency_matrix, epsilon, limits);
        Cost cost = calculate_total_cost(adjacency_matrix, route);
        if (cost.is_inside_limits(limits))
            population.push_back(route);
        attempts++;
    }

    // If we couldn't generate enough valid routes, return the best one we have
    if (population.empty()) {
        return {0, 0}; // Return a minimal valid route
    }

    for (int gen = 0; gen < generations; gen++) {
        vector<pair<double, vector<int>>> evaluated_population;
        double best_fitness = numeric_limits<double>::max();
        vector<int> best_route;

        for (auto& individual : population) {
            double fitness = calculate_fitness(individual, adjacency_matrix, limits);
            evaluated_population.push_back({-fitness, individual});
            
            if (fitness < best_fitness) {
                best_fitness = fitness;
                best_route = individual;
            }
        }

        // Sort by fitness in ascending order (lower fitness is better)
        sort(evaluated_population.begin(), evaluated_population.end());

        // Keep the best individuals (lowest fitness values)
        vector<vector<int>> new_population;
        for (int i = 0; i < best_cota && i < evaluated_population.size(); i++) {
            new_population.push_back(evaluated_population[i].second);
        }

        // Add random individuals, not in the best ones
        uniform_int_distribution<int> idx_dist(0, evaluated_population.size() - 1);
        while (new_population.size() < selection_size) {
            int random_idx = idx_dist(g);
            if (find(new_population.begin(), new_population.end(), evaluated_population[random_idx].second) == new_population.end()) {
                new_population.push_back(evaluated_population[random_idx].second);
            }
        }

        // Generate new individuals through crossover
        uniform_int_distribution<int> parent_dist(0, selection_size - 1);
        while (new_population.size() < population_size) {
            int parent1_idx = parent_dist(g);
            int parent2_idx = parent_dist(g);
            vector<int> child = crossover(new_population[parent1_idx], new_population[parent2_idx], adjacency_matrix, limits);

            mutation(child);

            if (is_memetic)
                local_search(adjacency_matrix, child, limits);
            
            // Always add the child to the population since crossover now guarantees validity
            new_population.push_back(child);
        }

        population = new_population;
    }

    // Return the best route found
    double best_fitness = numeric_limits<double>::max();
    vector<int> best_route;
    for (auto& individual : population) {
        double fitness = calculate_fitness(individual, adjacency_matrix, limits);
        if (fitness < best_fitness) {
            best_fitness = fitness;
            best_route = individual;
        }
    }
    return best_route;
}

// adici