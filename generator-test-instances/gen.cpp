#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <random>
#include <cmath>
using namespace std;

namespace {
static std::mt19937 &random_engine() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  return gen;
}

template <typename T> static T rand_int(const T &a, const T &b) {
  std::uniform_int_distribution<T> dis(a, b);
  return dis(random_engine());
}

template <typename Container>
static auto rand_elem(const Container &container) ->
    typename Container::value_type {
  assert(container.size() > 0);
  return container[rand_int(0, (int)container.size() - 1)];
}

// Structure to represent a point in 2D space
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    double distanceTo(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx*dx + dy*dy);
    }
};

// Structure to represent a Baiana location
struct BaianaLocation {
    Point pos;
    bool isTouristArea;
    bool isResidentialArea;
    
    BaianaLocation(Point p, bool tourist, bool residential) 
        : pos(p), isTouristArea(tourist), isResidentialArea(residential) {}
};

// Function to calculate realistic duration based on distance and conditions
int calculateDuration(int distanceMeters, bool isTouristArea, bool isResidentialArea) {
    // Base speed in m/s (varies by area type)
    double baseSpeed;
    if (isTouristArea) {
        baseSpeed = 8.0; // Slower in tourist areas due to traffic and crowds
    } else if (isResidentialArea) {
        baseSpeed = 12.0; // Moderate speed in residential areas
    } else {
        baseSpeed = 15.0; // Faster in regular areas
    }
    
    // Add random variation to simulate traffic conditions
    double trafficFactor = 0.7 + (rand_int(0, 100) / 100.0) * 0.6; // 0.7 to 1.3
    
    // Calculate base duration
    double duration = distanceMeters / (baseSpeed * trafficFactor);
    
    // Add extra time for hills and curves (random factor)
    duration *= (1.0 + (rand_int(0, 100) / 100.0) * 0.3); // Up to 30% extra time
    
    return static_cast<int>(duration);
}

} // namespace

int main(int argc, char *argv[]) {
    string arg = argv[2];
    int instance = stoi(arg);
    
    int n;
    // Regular instances for testing (1-105)
    if (instance <= 20) {
        n = 25;
    } else if (instance <= 30) {
        n = 50;
    } else if (instance <= 40) {
        n = 75;
    } else if (instance <= 60) {
        n = 100;
    } else if (instance <= 80) {
        n = 250;
    } else if (instance <= 100) {
        n = 500;
    } else if (instance <= 105) {  // 5 instances for N=1000 for testing
        n = 1000;
    }
    // Irace instances (106-119)
    else if (instance <= 107) {  // 2 instances for N=25
        n = 25;
    } else if (instance <= 109) {  // 2 instances for N=50
        n = 50;
    } else if (instance <= 111) {  // 2 instances for N=75
        n = 75;
    } else if (instance <= 113) {  // 2 instances for N=100
        n = 100;
    } else if (instance <= 115) {  // 2 instances for N=250
        n = 250;
    } else if (instance <= 117) {  // 2 instances for N=500
        n = 500;
    } else if (instance <= 119) {  // 2 instances for N=1000
        n = 1000;
    } else {
        cerr << "Invalid instance number" << endl;
        return 1;
    }

    // Define tourist areas (clusters)
    vector<Point> touristCenters = {
        Point(0.0, 0.0),    // Pelourinho
        Point(0.8, 0.8),    // Rio Vermelho
        Point(0.2, 0.7),    // Barra
        Point(0.6, 0.3),    // Itapuã
        Point(0.4, 0.5)     // Ondina
    };

    // Generate Baiana locations
    vector<BaianaLocation> locations;
    for (int i = 0; i < n; i++) {
        // Determine if this location is in a tourist area
        bool isTouristArea = rand_int(0, 100) < 30; // 30% chance of being in tourist area
        bool isResidentialArea = !isTouristArea && rand_int(0, 100) < 40; // 40% chance of being residential
        
        Point pos;
        if (isTouristArea) {
            // Place near a tourist center with some random variation
            Point center = rand_elem(touristCenters);
            double angle = (rand_int(0, 360) * M_PI) / 180.0;
            double distance = rand_int(0, 1000) / 10000.0; // Up to 1km variation
            pos = Point(
                center.x + distance * cos(angle),
                center.y + distance * sin(angle)
            );
        } else {
            // Random position for non-tourist areas
            pos = Point(
                rand_int(0, 1000) / 1000.0,
                rand_int(0, 1000) / 1000.0
            );
        }
        
        locations.emplace_back(pos, isTouristArea, isResidentialArea);
    }

    cout << n << endl;
    
    // Output vertex parameters
    for (const auto& loc : locations) {
        int collectionTimeInSeconds = rand_int(60 * 10, 60 * 20);
        int dendeInMililiters = rand_int(5000, 10000);
        cout << collectionTimeInSeconds << " " << dendeInMililiters << endl;
    }

    // Output graph edges
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cout << i << " " << j << " 0 0" << endl;
                continue;
            }

            // Calculate distance in meters (scaling the normalized coordinates)
            int distanceMeters = static_cast<int>(
                locations[i].pos.distanceTo(locations[j].pos) * 30000
            );
            
            // Calculate duration based on area types and distance
            int durationSeconds = calculateDuration(
                distanceMeters,
                locations[i].isTouristArea || locations[j].isTouristArea,
                locations[i].isResidentialArea || locations[j].isResidentialArea
            );

            cout << i << " " << j << " " << distanceMeters << " " << durationSeconds << endl;
        }
    }
}
