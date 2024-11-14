#pragma once

#include <iostream>
#include <fstream>
#include "../nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

struct Limitations {
    int maxDendeInMililiters;
    int maxCollectionTimeInSeconds;
    int minDendeInMililiters;
};

void from_json(const json& j, Limitations& l) {
    j.at("maxDendeInMililiters").get_to(l.maxDendeInMililiters);
    j.at("maxCollectionTimeInSeconds").get_to(l.maxCollectionTimeInSeconds);
    j.at("minDendeInMililiters").get_to(l.minDendeInMililiters);
}

void to_json(json& j, const Limitations& l) {
    j = json{
        {"maxDendeInMililiters", l.maxDendeInMililiters},
        {"maxCollectionTimeInSeconds", l.maxCollectionTimeInSeconds},
        {"minDendeInMililiters", l.minDendeInMililiters}
    };
}