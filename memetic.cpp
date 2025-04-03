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

int main(int argc, char* argv[]) {
    double epsilon = 0.9858;
    int population_size = 100, generations = 1000, best_cota = 27, selection_size = 24;

    
    best_cota = min(best_cota, population_size);
    selection_size = min(selection_size, population_size);
    // ifstream file("input.json");
    // json j;
    // file >> j;

    // Input input = j.get<Input>();
    int n;
    cin >> n;
    Input input;
    for (int i = 0; i < n; i++) {
        Location location;
        cin >> location.collectionTimeInSeconds >> location.dendeInMililiters;
        input.locations.push_back(location);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            RouteInfo route_info;
            cin >> route_info.originIndex >> route_info.destinationIndex >> route_info.distanceMeters >> route_info.durationSeconds;
            input.routes.push_back(route_info);
        }
    }

    input.limitations.maxCollectionTimeInSeconds = 3600 * 8;
    input.limitations.maxDendeInMililiters = 100 * 1000;
    input.limitations.minDendeInMililiters = 20 * 1000;

    // ifstream file("input.json");
    // json j;
    // file >> j;

    // Input input = j.get<Input>();

    vector<vector<Cost>> adjacency_matrix = construct_adjacency_matrix(input);

    auto start_time = chrono::steady_clock::now();
    vector<int> memetic_route = genetic_algorithm(adjacency_matrix, input.limitations, true, epsilon, population_size, generations, best_cota, selection_size);
    auto current_time = chrono::steady_clock::now();
    auto elapsed_milliseconds = chrono::duration_cast<chrono::milliseconds>(current_time - start_time).count();
    Cost memetic_route_total_cost = calculate_total_cost(adjacency_matrix, memetic_route);

    // cout << "memetic route: ";
    // for (const auto& location : memetic_route) {
    //     cout << location << " ";
    // }
    // cout << endl;

    // cout << "memetic route total cost: " << memetic_route_total_cost.distanceMeters << " meters, " << genetic_route_total_cost.durationSeconds << " seconds, " << genetic_route_total_cost.dendeInMililiters << " mililiters" << endl;

    cout << memetic_route_total_cost.fitness() << " " << elapsed_milliseconds << " " << memetic_route_total_cost.distanceMeters << " " << memetic_route_total_cost.durationSeconds << " " << memetic_route_total_cost.dendeInMililiters << endl;

    return 0;
}