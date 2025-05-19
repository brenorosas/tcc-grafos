#pragma once

#include <iostream>
#include <fstream>
#include "../nlohmann/json.hpp"
#include "route_info.hpp"
#include "limitations.hpp"
using json = nlohmann::json;
using namespace std;

struct Location {
    string description;
    string address;
    int collectionTimeInSeconds;
    int dendeInDeciliters;
};

void from_json(const json& j, Location& l) {
    j.at("description").get_to(l.description);
    j.at("address").get_to(l.address);
    j.at("collectionTimeInSeconds").get_to(l.collectionTimeInSeconds);
    j.at("dendeInDeciliters").get_to(l.dendeInDeciliters);
}

void to_json(json& j, const Location& l) {
    j = json{
        {"description", l.description},
        {"address", l.address},
        {"collectionTimeInSeconds", l.collectionTimeInSeconds},
        {"dendeInDeciliters", l.dendeInDeciliters}
    };
}

struct Input {
    vector<Location> locations;
    vector<RouteInfo> routes;
    Limitations limitations;
};

void from_json(const json& j, Input& i) {
    j.at("locations").get_to(i.locations);
    j.at("routes").get_to(i.routes);
    j.at("limitations").get_to(i.limitations);
}

void to_json(json& j, const Input& r) {
    j = json{
        {"locations", r.locations},
        {"routes", r.routes},
        {"limitations", r.limitations}
    };
}