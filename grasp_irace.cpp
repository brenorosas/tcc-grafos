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
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <epsilon>" << endl;
        return 1;
    }

    // Read epsilon from command line argument
    double epsilon = stod(argv[1]);
    int max_iterations = 10000;  // Fixed parameter for GRASP
    
    // ifstream file("input.json");
    // json j;
    // file >> j;

    // Input input = j.get<Input>();
    int n;
    cin >> n;
    Input input;
    for (int i = 0; i < n; i++) {
        Location location;
        cin >> location.collectionTimeInSeconds >> location.dendeInDeciliters;
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
    input.limitations.maxDendeInDeciliters = 100 * 10;
    input.limitations.minDendeInDeciliters = 20 * 10;

    // ifstream file("input.json");
    // json j;
    // file >> j;

    // Input input = j.get<Input>();

    vector<vector<Cost>> adjacency_matrix = construct_adjacency_matrix(input);
    auto start_time = chrono::steady_clock::now();
    vector<int> grasp_route = grasp(adjacency_matrix, input.limitations, epsilon, max_iterations);
    auto current_time = chrono::steady_clock::now();
    auto elapsed_milliseconds = chrono::duration_cast<chrono::milliseconds>(current_time - start_time).count();
    Cost grasp_route_total_cost = calculate_total_cost(adjacency_matrix, grasp_route);

    // cout << "GRASP route: ";
    // for (const auto& location : grasp_route) {
    //     cout << location << " ";
    // }
    // cout << endl;

    // cout << "GRASP route total cost: " << grasp_route_total_cost.distanceMeters << " meters, " << grasp_route_total_cost.durationSeconds << " seconds, " << grasp_route_total_cost.dendeInDeciliters << " mililiters" << endl;

    // cout << grasp_route_total_cost.fitness() << " " << elapsed_milliseconds << " " << grasp_route_total_cost.distanceMeters << " " << grasp_route_total_cost.durationSeconds << " " << grasp_route_total_cost.dendeInDeciliters << endl;
    cout << grasp_route_total_cost.fitness() << endl;
    return 0;
}