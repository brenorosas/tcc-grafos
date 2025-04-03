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
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <epsilon> <best_cota> <selection_size>" << endl;
        return 1;
    }

    // Read parameters from command line arguments
    double epsilon = stod(argv[1]);
    int best_cota = stoi(argv[2]);
    int selection_size = stoi(argv[3]);
    
    // Fixed parameters
    int population_size = 100;
    int generations = 1000;
    
    best_cota = min(best_cota, population_size);
    selection_size = min(selection_size, population_size);

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

    vector<int> memetic_route = genetic_algorithm(adjacency_matrix, input.limitations, true, epsilon, population_size, generations, best_cota, selection_size);
    Cost memetic_route_total_cost = calculate_total_cost(adjacency_matrix, memetic_route);

    // Output only the fitness value for irace
    cout << memetic_route_total_cost.fitness() << endl;

    return 0;
} 