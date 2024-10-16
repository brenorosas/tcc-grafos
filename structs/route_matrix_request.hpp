#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "../nlohmann/json.hpp"

struct Waypoint {
    std::string address;
};

struct Origin {
    Waypoint waypoint;
};

struct Destination {
    Waypoint waypoint;
};

struct RouteMatrixRequest {
    std::vector<Origin> origins;
    std::vector<Destination> destinations;

    void add_origin(const std::string& address) {
        origins.push_back(Origin{{address}});
    }

    void add_destination(const std::string& address) {
        destinations.push_back(Destination{{address}});
    }
};

void to_json(nlohmann::json& j, const Waypoint& w) {
    j = nlohmann::json{{"address", w.address}};
}

void to_json(nlohmann::json& j, const Origin& o) {
    j = nlohmann::json{{"waypoint", o.waypoint}};
}

void to_json(nlohmann::json& j, const Destination& d) {
    j = nlohmann::json{{"waypoint", d.waypoint}};
}

void to_json(nlohmann::json& j, const RouteMatrixRequest& r) {
    j = nlohmann::json{
        {"origins", r.origins},
        {"destinations", r.destinations}
    };
}