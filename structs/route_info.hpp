#pragma once

#include <iostream>
#include <fstream>
#include "../nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

struct RouteInfo {
    int originIndex;
    int destinationIndex;
    int distanceMeters;
    int durationSeconds;
};

void from_json(const json& j, RouteInfo& r) {
    j.at("originIndex").get_to(r.originIndex);
    j.at("destinationIndex").get_to(r.destinationIndex);

    if (j.contains("distanceMeters")) {
        j.at("distanceMeters").get_to(r.distanceMeters);
    } else {
        r.distanceMeters = 0;
    }

    if (j.contains("durationSeconds")) {
        j.at("durationSeconds").get_to(r.durationSeconds);
    } else if(j.contains("duration")) {
        string duration;
        j.at("duration").get_to(duration);
        r.durationSeconds = stoi(duration.substr(0, duration.size() - 1));
    } else {
        r.durationSeconds = 0;
    }
}

void to_json(json& j, const RouteInfo& r) {
    j = json{
        {"originIndex", r.originIndex},
        {"destinationIndex", r.destinationIndex},
        {"distanceMeters", r.distanceMeters},
        {"durationSeconds", r.durationSeconds}
    };
}