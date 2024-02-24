#include <iostream>
#include <string>
#include <map>

using namespace std;

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
    Plane(const string& from, const string& to)
    {
        // Define one-way flights with distances
        oneWayFlights[{"SCE", "PHL"}] = 160;
        oneWayFlights[{"SCE", "ORD"}] = 640;
        oneWayFlights[{"SCE", "EWR"}] = 220;

        origin = from;
        destination = to;
        distance = oneWayFlights[{origin, destination}];

        pos = 0;
        vel = 0;
        at_SCE = false;

        cout << "Plane Created at " << this << endl;
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
            distance = oneWayFlights[{origin, destination}];
        }

        else
        {
            swap(origin, destination);
            pos = 0.0;
            distance = oneWayFlights[{origin, destination}];
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

int main()
{
    Plane myPlane("SCE", "PHL");

    double flightSpeed = 490 / 3600;
    myPlane.setVel(flightSpeed);

    double timestep = 10;

    int maxIterations = 1000;

    for (int i = 0; i < maxIterations; ++i) {
        myPlane.operate(timestep);
        cout << "Time " << timestep * (i + 1) << ", Position: " << myPlane.getPos() << " miles" << endl;
    }

    return 0;
}