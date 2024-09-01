#pragma once

#include <iostream>
#include <fstream>
#include "../nlohmann/json.hpp"
#include "route_info.hpp"

using json = nlohmann::json;
using namespace std;

struct Input {
    vector<string> locations;
    vector<RouteInfo> routes;
};

void from_json(const json& j, Input& i) {
    j.at("locations").get_to(i.locations);
    j.at("routes").get_to(i.routes);
}

void to_json(json& j, const Input& r) {
    j = json{
        {"locations", r.locations},
        {"routes", r.routes}
    };
}