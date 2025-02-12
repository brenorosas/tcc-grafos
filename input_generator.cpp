#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include "nlohmann/json.hpp"
#include "structs/route_matrix_request.hpp"
#include "structs/route_info.hpp"
#include "structs/input.hpp"
#include "utils/load_env.hpp"
#include "utils/send_post_request.hpp"

using json = nlohmann::json;
using namespace std;

int main() {
    auto env_vars = load_env(".env");

    ifstream file("locations.json");
    json j;
    file >> j;

    vector<Location> locations = j.get<vector<Location>>();
    ofstream format_locations_file("locations.json");
    format_locations_file << json(locations).dump(4) << endl;

    RouteMatrixRequest request;

    for (const auto& location : locations) {
        request.add_origin(location.address);
        request.add_destination(location.address);
    }

    string api_key = env_vars["GOOGLE_API_KEY"];
    string url = "https://routes.googleapis.com/distanceMatrix/v2:computeRouteMatrix?key=" + api_key;
    string body = json(request).dump();

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "X-Goog-FieldMask: originIndex");
    headers = curl_slist_append(headers, "X-Goog-FieldMask: destinationIndex");
    headers = curl_slist_append(headers, "X-Goog-FieldMask: distanceMeters");
    headers = curl_slist_append(headers, "X-Goog-FieldMask: duration");
    headers = curl_slist_append(headers, "X-Goog-FieldMask: condition");
    json response_json = sendPostRequest(url, body, headers);

    vector<RouteInfo> routes = response_json.get<vector<RouteInfo>>();

    Limitations limitations;
    ifstream limitations_file("limitations.json");
    json limitations_json;
    limitations_file >> limitations_json;
    limitations = limitations_json.get<Limitations>();

    Input input;
    input.locations = locations;
    input.routes = routes;
    input.limitations = limitations;

    ofstream output_file("input.json");
    output_file << json(input).dump(4) << endl;

    return 0;
}