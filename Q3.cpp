// #3

#include <iostream>
#include <map>
#include <string>

using namespace std;

// Define a map to store one-way flights with distances


// Class definition for Plane
class Plane {
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    string origin;
    string destination;
    map<pair<string, string>, int> oneWayFlights;

public:
    // Constructor
    Plane(string from, string to) : origin(from), destination(to) {
        // Initialize pos, vel, and at_SCE
        pos = 0.0;
        vel = 0.0;
        at_SCE = true;
        // Initialize distance based on the flight distance
        distance = oneWayFlights[{from, to}];
    }

    // Destructor
    ~Plane() {}

    // Function to operate the plane
    void operate(double dt) {
        // Update position based on velocity and time
        pos += vel * dt;
        // Check if the plane reaches its destination
        if (pos >= distance) {
            at_SCE = false;
        }
    }

    // Getter functions
    double getPos() { return pos; }
    string getOrigin() { return origin; }
    string getDestination() { return destination; }
    bool getAtSCE() { return at_SCE; }

    // Getter and setter function for velocity
    double getVel() { return vel; }
    void setVel(double newVel) { vel = newVel; }
};

int main() {
    // Add one-way flights
    map<pair<string, string>, int> oneWayFlights;
    oneWayFlights[{"SCE", "PHL"}] = 160;
    oneWayFlights[{"SCE", "ORD"}] = 640;
    oneWayFlights[{"SCE", "EWR"}] = 220;


    return 0;

}