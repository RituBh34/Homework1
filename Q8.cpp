#include <iostream>
#include <string>
#include <map>
#include <memory>

using namespace std;

class Plane {
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    string origin;
    string destination;
    map<string, map<string, int>> flightDistances;

public:
    // Constructor
    Plane(const string& from, const string& to)
    {
        flightDistances["SCE"]["PHL"] = 160;
        flightDistances["SCE"]["ORD"] = 640;
        flightDistances["SCE"]["EWR"] = 220;

        origin = from;
        destination = to;
        distance = flightDistances[origin][destination];

        pos = 0;
        vel = 0;
        at_SCE = false;

        cout << "Plane Created with a tail number " << this << endl;
    }

    // Destructor
    ~Plane()
    {
        cout << "Plane Destroyed" << endl;
    }

    // Member function to operate the plane
    void operate(double dt)
    {
        if (pos < distance)
        {
            pos += vel * dt;
            if (pos < 0) pos = 0;
            at_SCE = false;
        }

        else if (destination == "SCE")
        {
            at_SCE = true;
            swap(origin, destination);
            pos = 0.0;
            distance = flightDistances[origin][destination];
        }

        else
        {
            swap(origin, destination);
            pos = 0.0;
            distance = flightDistances[origin][destination];
        }
    }

    // Getter functions
    double getPos() const
    {
        return pos;
    }

    double getVel() const
    {
        return vel;
    }

    double getDistance() const
    {
        return distance;
    }

    bool getAt_SCE() const
    {
        return at_SCE;
    }

    string getOrigin() const
    {
        return origin;
    }

    string getDestination() const
    {
        return destination;
    }

    // Setter function for velocity
    void setVel(double newVel)
    {
        vel = newVel;
    }
};

class Pilot {
private:
    string name;
    shared_ptr<Plane> myPlane;

public:
    // Constructor
    Pilot(const string& pilotName, const shared_ptr<Plane>& planePtr) : name(pilotName), myPlane(planePtr) {
        cout << "Pilot " << name << " Created at " << this << " - Ready to board the plane." << endl;
    }

    // Destructor
    ~Pilot() {
        cout << "Pilot " << name << " - Out of the plane." << endl;
    }

    // Getter function for name
    string getName() const {
        return name;
    }

    // Getter function to access the plane object
    shared_ptr<Plane> getPlane() const {
        return myPlane;
    }
};

int main() {
    // Instantiate a Plane object
    auto plane = make_shared<Plane>("SCE", "PHL");

    // Set the speed of the airplane using the set function for "vel"
    double flightSpeed = 450.0 / 3600; // Assuming a speed between 400-500 mph
    plane->setVel(flightSpeed);

    // Set timestep to 50 seconds
    double timestep = 3000;

    // Choose the maximum number of iterations between [1000, 2000]
    int maxIterations = 1000;

    // Instantiate Pilot objects for Pilot-in-Command and Co-Pilot
    Pilot pilot1("Pilot Alpha", plane);
    Pilot pilot2("Pilot Bravo", plane);

    // Variable to track which pilot is currently controlling the plane
    Pilot* currentPilot = &pilot1;

    for (int i = 0; i < maxIterations; ++i) {
        // Print out the current pilot's name, memory address, and the plane's memory address
        cout << currentPilot->getName() << " with certificate number " << currentPilot << " is in control of a plane: " << currentPilot->getPlane() << endl;

        // Call the "operate" function with timestep as an input
        plane->operate(timestep);

        // Check if the plane has landed at SCE
        if (plane->getAt_SCE()) {
            // Print out the memory address of the plane and indicate it is at SCE
            cout << "Plane at memory address " << plane.get() << " has landed at SCE." << endl;

            // Switch the current pilot
            if (currentPilot == &pilot1) {
                currentPilot = &pilot2;
            }
            else {
                currentPilot = &pilot1;
            }
        }
    }

    return 0;
}