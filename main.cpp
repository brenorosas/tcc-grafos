#include <iostream>
#include <fstream>
#include "structs/input.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

int main() {
    ifstream file("input.json");
    json j;
    file >> j;

    Input input = j.get<Input>();

    cout << "Locations: ";
    for (const auto& origin : input.locations) {
        cout << origin << " ";
    }
    cout << endl;

    cout << "Routes: " << endl;
    for (const auto& route : input.routes) {
        cout << "Origin index: " << route.originIndex << endl;
        cout << "Destination index: " << route.destinationIndex << endl;
        cout << "Distance meters: " << route.distanceMeters << endl;
        cout << "Duration seconds: " << route.durationSeconds << endl;
        cout << endl;
    }

    return 0;
}