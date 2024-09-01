#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

std::unordered_map<std::string, std::string> load_env(const std::string& file_path) {
    std::unordered_map<std::string, std::string> env_vars;
    std::ifstream file(file_path);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        std::string value;

        if (std::getline(std::getline(iss, key, '=') >> std::ws, value)) {
            env_vars[key] = value;
        }
    }

    return env_vars;
}
