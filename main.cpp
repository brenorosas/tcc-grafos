#include <iostream>
#include <fstream>
#include "structs/input.hpp"
#include "nlohmann/json.hpp"
#include "structs/cost.hpp"
#include "utils/construct_adjacency_matrix.hpp"

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
    
    return 0;
}