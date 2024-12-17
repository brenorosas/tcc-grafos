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
    int max_iterations;

    cin >> epsilon >> max_iterations;
    ifstream file("input.json");
    json j;
    file >> j;

    Input input = j.get<Input>();

    vector<vector<Cost>> adjacency_matrix = construct_adjacency_matrix(input);

    vector<int> grasp_route = grasp(adjacency_matrix, input.limitations, epsilon, max_iterations);
    Cost grasp_route_total_cost = calculate_total_cost(adjacency_matrix, grasp_route);

    // cout << "GRASP route: ";
    // for (const auto& location : grasp_route) {
    //     cout << location << " ";
    // }
    // cout << endl;

    // cout << "GRASP route total cost: " << grasp_route_total_cost.distanceMeters << " meters, " << grasp_route_total_cost.durationSeconds << " seconds, " << grasp_route_total_cost.dendeInMililiters << " mililiters" << endl;

    cout << grasp_route_total_cost.fitness() << endl;
    return 0;
}