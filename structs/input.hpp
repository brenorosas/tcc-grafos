#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;


struct RouteInfo {
    int originIndex;
    int destinationIndex;
    int distanceMeters;
    int durationSeconds;
};

struct Input {
    vector<string> origins;
    vector<string> destinations;
    vector<RouteInfo> routes;
};

void from_json(const json& j, RouteInfo& r) {
    j.at("originIndex").get_to(r.originIndex);
    j.at("destinationIndex").get_to(r.destinationIndex);
    j.at("distanceMeters").get_to(r.distanceMeters);
    j.at("durationSeconds").get_to(r.durationSeconds);
}

void from_json(const json& j, Input& i) {
    j.at("origins").get_to(i.origins);
    j.at("destinations").get_to(i.destinations);
    j.at("routes").get_to(i.routes);
}
