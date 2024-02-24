// #2
#include <iostream>
#include <map>
#include <string>

using namespace std;

// Define a map to store one-way flights with distances
map<pair<string, string>, int> oneWayFlights;

// Add one-way flights
oneWayFlights[{"SCE", "PHL"}] = 160;
oneWayFlights[{"SCE", "ORD"}] = 640;
oneWayFlights[{"SCE", "EWR"}] = 220;