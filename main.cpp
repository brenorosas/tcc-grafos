#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include "structs/input.hpp"

using json = nlohmann::json;
using namespace std;

int main() {
    ifstream file("input.json");
    json j;
    file >> j;

    Input input = j.get<Input>();

    cout << "Origins: ";
    for (const auto& origin : input.origins) {
        cout << origin << " ";
    }
    cout << endl;

    cout << "Destinations: ";
    for (const auto& destination : input.destinations) {
        cout << destination << " ";
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