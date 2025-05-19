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
    ifstream file("input.json");
    json j;
    file >> j;

    Input input = j.get<Input>();

    vector<vector<Cost>> adjacency_matrix = construct_adjacency_matrix(input);

    vector<int> random_route = make_random_route(adjacency_matrix, 1, input.limitations);
    Cost random_route_total_cost = calculate_total_cost(adjacency_matrix, random_route);

    cout << "Random route: ";
    for (const auto& location : random_route) {
        cout << location << " ";
    }
    cout << endl;

    cout << "Random Route: " << random_route_total_cost.distanceMeters << " meters, "
         << random_route_total_cost.durationSeconds << " seconds, "
         << random_route_total_cost.dendeInDeciliters << " deciliters" << endl;

    vector<int> grasp_route = grasp(adjacency_matrix, input.limitations);
    Cost grasp_route_total_cost = calculate_total_cost(adjacency_matrix, grasp_route);

    cout << "GRASP route: ";
    for (const auto& location : grasp_route) {
        cout << location << " ";
    }
    cout << endl;

    cout << "GRASP Route: " << grasp_route_total_cost.distanceMeters << " meters, "
         << grasp_route_total_cost.durationSeconds << " seconds, "
         << grasp_route_total_cost.dendeInDeciliters << " deciliters" << endl;

    vector<int> genetic_route = genetic_algorithm(adjacency_matrix, input.limitations);
    Cost genetic_route_total_cost = calculate_total_cost(adjacency_matrix, genetic_route);

    cout << "Genetic route: ";
    for (const auto& location : genetic_route) {
        cout << location << " ";
    }
    cout << endl;

    cout << "Genetic Route: " << genetic_route_total_cost.distanceMeters << " meters, "
         << genetic_route_total_cost.durationSeconds << " seconds, "
         << genetic_route_total_cost.dendeInDeciliters << " deciliters" << endl;

     vector<int> memetic_route = genetic_algorithm(adjacency_matrix, input.limitations, true);
    Cost memetic_route_total_cost = calculate_total_cost(adjacency_matrix, memetic_route);

    cout << "Memetic route: ";
    for (const auto& location : memetic_route) {
        cout << location << " ";
    }
    cout << endl;

    cout << "Memetic Route: " << memetic_route_total_cost.distanceMeters << " meters, "
         << memetic_route_total_cost.durationSeconds << " seconds, "
         << memetic_route_total_cost.dendeInDeciliters << " deciliters" << endl;



    return 0;
}