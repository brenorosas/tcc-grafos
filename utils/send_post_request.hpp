#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include "../nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total_size = size * nmemb;
    std::string* response = static_cast<std::string*>(userp);
    response->append(static_cast<char*>(contents), total_size);
    return total_size;
}

json sendPostRequest(const string& url, const string& body, const curl_slist* headers = nullptr) {
    CURL* curl;
    CURLcode res;
    string response_body;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    json json_response;
    try {
        json_response = json::parse(response_body);
    } catch (const json::parse_error& e) {
        cerr << "JSON parse error: " << e.what() << endl;
        return json(); // Return an empty JSON object on parse error
    }

    return json_response;
}

