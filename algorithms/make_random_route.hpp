#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <limits>
#include "../structs/limitations.hpp"
#include "../structs/cost.hpp"

using namespace std;

vector<int> make_random_route(vector<vector<Cost>>& adjacency_matrix, float epsilon, Limitations limits) {
    random_device rd;
    mt19937 g(rd());
    vector<int> route;
    int num_nodes = adjacency_matrix.size();

    // Inicializa a rota no nó 0 e as restrições de custo
    route.push_back(0);
    vector<bool> visited(num_nodes, false);
    visited[0] = true;

    Cost current_cost = {0, 0, 0};

    for (int i = 1; i < num_nodes; i++) {
        int last_node = route.back();

        int next_node = -1;
        if (static_cast<float>(rand()) / RAND_MAX < epsilon) {
            // Escolha aleatória, mas respeitando limitações
            vector<int> candidates;
            for (int j = 0; j < num_nodes; j++) {
                if (!visited[j]) {
                    Cost new_cost = current_cost;
                    new_cost += adjacency_matrix[last_node][j];
                    if (new_cost.dendeInMililiters <= limits.maxDendeInMililiters &&
                        new_cost.durationSeconds <= limits.maxCollectionTimeInSeconds) {
                        candidates.push_back(j);
                    }
                }
            }
            if (!candidates.empty()) {
                next_node = candidates[g() % candidates.size()];
            }
        } else {
            // Escolhe o próximo nó com menor custo, respeitando limitações
            Cost min_cost = {numeric_limits<int>::max(), numeric_limits<int>::max(), numeric_limits<int>::max()};
            for (int j = 0; j < num_nodes; j++) {
                if (!visited[j]) {
                    Cost new_cost = current_cost;
                    new_cost += adjacency_matrix[last_node][j];
                    if (new_cost.dendeInMililiters <= limits.maxDendeInMililiters &&
                        new_cost.durationSeconds <= limits.maxCollectionTimeInSeconds &&
                        adjacency_matrix[last_node][j] < min_cost) {
                        min_cost = adjacency_matrix[last_node][j];
                        next_node = j;
                    }
                }
            }
        }

        // Se não encontrou próximo nó válido, encerra a geração da rota
        if (next_node == -1) break;

        // Adiciona o próximo nó à rota
        route.push_back(next_node);
        visited[next_node] = true;
        current_cost += adjacency_matrix[last_node][next_node];
    }

    // Fecha o ciclo retornando ao nó inicial
    route.push_back(0);
    return route;
}
