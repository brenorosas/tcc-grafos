#include <iostream>
#include <fstream>
#include "structs/input.hpp"
#include "nlohmann/json.hpp"
#include "structs/cost.hpp"
#include "algorithms/construct_adjacency_matrix.hpp"
#include "algorithms/make_random_route.hpp"

using json = nlohmann::json;
using namespace std;

int main() {
    ifstream file("input.json");
    json j;
    file >> j;

    Input input = j.get<Input>();

    vector<vector<Cost>> adjacency_matrix = construct_adjacency_matrix(input);

    for (const auto& row : adjacency_matrix) {
        for (const auto& cost : row) {
            cout << cost.distanceMeters << " ";
        }
        cout << endl;
    }

    vector<int> random_route = make_random_route(adjacency_matrix);

    return 0;
}