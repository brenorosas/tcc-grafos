#include <iostream>
#include <fstream>
#include "structs/input.hpp"
#include "nlohmann/json.hpp"
#include "structs/cost.hpp"
#include "algorithms/construct_adjacency_matrix.hpp"
#include "algorithms/make_random_route.hpp"
#include "algorithms/calculate_total_cost.hpp"
#include "algorithms/grasp.hpp"

using json = nlohmann::json;
using namespace std;

int main() {
    ifstream file("input.json");
    json j;
    file >> j;

    Input input = j.get<Input>();

    vector<vector<Cost>> adjacency_matrix = construct_adjacency_matrix(input);

    // for (const auto& row : adjacency_matrix) {
    //     for (const auto& cost : row) {
    //         cout << cost.distanceMeters << " ";
    //     }
    //     cout << endl;
    // }

    vector<int> random_route = make_random_route(adjacency_matrix, 1, input.limitations);
    Cost random_route_total_cost = calculate_total_cost(adjacency_matrix, random_route);

    cout << "Random route: ";
    for (const auto& location : random_route) {
        cout << location << " ";
    }
    cout << endl;

    cout << "Random route total cost: " << random_route_total_cost.distanceMeters << " meters, " << random_route_total_cost.durationSeconds << " seconds, " << random_route_total_cost.dendeInMililiters << " mililiters" << endl;

    vector<int> grasp_route = grasp(adjacency_matrix, input.limitations);
    Cost grasp_route_total_cost = calculate_total_cost(adjacency_matrix, grasp_route);

    cout << "GRASP route: ";
    for (const auto& location : grasp_route) {
        cout << location << " ";
    }
    cout << endl;

    cout << "GRASP route total cost: " << grasp_route_total_cost.distanceMeters << " meters, " << grasp_route_total_cost.durationSeconds << " seconds, " << grasp_route_total_cost.dendeInMililiters << " mililiters" << endl;

    return 0;
}