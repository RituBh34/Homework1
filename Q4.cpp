#include <iostream>
#include <map>
#include <string>

using namespace std;




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
        // Set origin and destination
        origin = from;
        destination = to;
        // Set distance based on the flight distance
        distance = oneWayFlights[{from, to}];
        // Initialize pos, vel, and at_SCE
        pos = 0.0;
        vel = 0.0;
        at_SCE = false;
        // Print creation message
        cout << "Plane Created at " << this << endl;
    }

    // Destructor
    ~Plane() {
        // Print destruction message
        cout << "Plane Destroyed" << endl;
    }

    // Function to operate the plane
    void operate(double dt) {
        // Check if the plane has reached its destination
        if (pos < distance) {
            // Update position based on velocity and time
            pos += vel * dt;
            // Set at_SCE to false
            at_SCE = false;
        }
        else {
            // Check if the destination is "SCE"
            if (destination == "SCE") {
                // Set at_SCE to true
                at_SCE = true;
                // Swap origin and destination
                swap(origin, destination);
                // Reset position
                pos = 0.0;
            }
            else {
                // Swap origin and destination
                swap(origin, destination);
                // Reset position
                pos = 0.0;
            }
        }
    }

    // Getter and setter functions
    double getPos() { return pos; }
    void setPos(double newPos) { pos = newPos; }

    double getVel() { return vel; }
    void setVel(double newVel) { vel = newVel; }

    double getDistance() { return distance; }

    string getOrigin() { return origin; }
    void setOrigin(string newOrigin) { origin = newOrigin; }

    string getDestination() { return destination; }
    void setDestination(string newDestination) { destination = newDestination; }

    bool getAtSCE() { return at_SCE; }
};

int main() {
    // Add one-way flights
    map<pair<string, string>, int> oneWayFlights;
    oneWayFlights[{"SCE", "PHL"}] = 160;
    oneWayFlights[{"SCE", "ORD"}] = 640;
    oneWayFlights[{"SCE", "EWR"}] = 220;

    return 0;
}