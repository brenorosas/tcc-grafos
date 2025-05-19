#pragma once

#include <iostream>
#include <fstream>
#include "../nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

struct Limitations {
    int maxDendeInDeciliters;
    int maxCollectionTimeInSeconds;
    int minDendeInDeciliters;
};

void from_json(const json& j, Limitations& l) {
    j.at("maxDendeInDeciliters").get_to(l.maxDendeInDeciliters);
    j.at("maxCollectionTimeInSeconds").get_to(l.maxCollectionTimeInSeconds);
    j.at("minDendeInDeciliters").get_to(l.minDendeInDeciliters);
}

void to_json(json& j, const Limitations& l) {
    j = json{
        {"maxDendeInDeciliters", l.maxDendeInDeciliters},
        {"maxCollectionTimeInSeconds", l.maxCollectionTimeInSeconds},
        {"minDendeInDeciliters", l.minDendeInDeciliters}
    };
}