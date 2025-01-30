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
    double epsilon = 0.9817;
    int population_size = 100, generations = 1000, best_cota = 27, selection_size = 10;

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


    vector<vector<Cost>> adjacency_matrix = construct_adjacency_matrix(input);
    auto start_time = chrono::steady_clock::now();
    vector<int> genetic_route = genetic_algorithm(adjacency_matrix, input.limitations, false, epsilon, population_size, generations, best_cota, selection_size);
    auto current_time = chrono::steady_clock::now();
    auto elapsed_milliseconds = chrono::duration_cast<chrono::milliseconds>(current_time - start_time).count();
    Cost genetic_route_total_cost = calculate_total_cost(adjacency_matrix, genetic_route);


    // cout << "Genetic route: ";
    // for (const auto& location : genetic_route) {
    //     cout << location << " ";
    // }
    // cout << endl;

    // cout << "Genetic route total cost: " << genetic_route_total_cost.distanceMeters << " meters, " << genetic_route_total_cost.durationSeconds << " seconds, " << genetic_route_total_cost.dendeInMililiters << " mililiters" << endl;
    cout << genetic_route_total_cost.fitness() << " " << elapsed_milliseconds << " " << genetic_route_total_cost.distanceMeters << " " << genetic_route_total_cost.durationSeconds << " " << genetic_route_total_cost.dendeInMililiters << endl;
    return 0;
}