#include <iostream>
#include <fstream>
#include "structs/input.hpp"
#include "nlohmann/json.hpp"
#include "structs/cost.hpp"
#include "algorithms/construct_adjacency_matrix.hpp"
#include "algorithms/make_random_route.hpp"
#include "algorithms/calculate_total_cost.hpp"
#include "algorithms/grasp.hpp"
#include "algorithms/genetic.hpp"

using json = nlohmann::json;
using namespace std;

int main() {
    double epsilon;
    int population_size, generations;

    cin >> epsilon >> population_size >> generations;
    ifstream file("input.json");
    json j;
    file >> j;

    Input input = j.get<Input>();


    vector<vector<Cost>> adjacency_matrix = construct_adjacency_matrix(input);

    vector<int> genetic_route = genetic_algorithm(adjacency_matrix, input.limitations, epsilon, population_size, generations);
    Cost genetic_route_total_cost = calculate_total_cost(adjacency_matrix, genetic_route);

    // cout << "Genetic route: ";
    // for (const auto& location : genetic_route) {
    //     cout << location << " ";
    // }
    // cout << endl;

    // cout << "Genetic route total cost: " << genetic_route_total_cost.distanceMeters << " meters, " << genetic_route_total_cost.durationSeconds << " seconds, " << genetic_route_total_cost.dendeInMililiters << " mililiters" << endl;

    cout << genetic_route_total_cost.fitness() << endl;
    return 0;
}