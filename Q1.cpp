// #1


#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Seat {
    double weight;
    double arm;
};

class Aircraft {
private:
    double emptyWeight;
    double emptyWeightMoment;
    vector<Seat> frontSeats;
    vector<Seat> rearSeats;
    int numGallons;
    double fuelPerGallon;
    double baggageWeight;
    double fuelArm;
    double baggageArm;

public:
    Aircraft(double emptyWeight, double emptyWeightMoment) : emptyWeight(emptyWeight), emptyWeightMoment(emptyWeightMoment) {}

    void addFrontSeat(double weight, double arm) {
        frontSeats.push_back({ weight, arm });
    }

    void addRearSeat(double weight, double arm) {
        rearSeats.push_back({ weight, arm });
    }

    void setFuel(int numGallons, double fuelPerGallon, double fuelArm) {
        this->numGallons = numGallons;
        this->fuelPerGallon = fuelPerGallon;
        this->fuelArm = fuelArm;
    }

    void setBaggage(double weight, double arm) {
        this->baggageWeight = weight;
        this->baggageArm = arm;
    }

    void calculateWeightAndBalance() const {
        double totalWeight = emptyWeight;
        double totalMoment = emptyWeightMoment;

        for (const auto& seat : frontSeats) {
            totalWeight += seat.weight;
            totalMoment += seat.weight * seat.arm;
        }

        for (const auto& seat : rearSeats) {
            totalWeight += seat.weight;
            totalMoment += seat.weight * seat.arm;
        }

        totalWeight += numGallons * fuelPerGallon;
        totalMoment += numGallons * fuelPerGallon * fuelArm;

        totalWeight += baggageWeight;
        totalMoment += baggageWeight * baggageArm;

        double cg = totalMoment / totalWeight;

        cout << "Gross Weight: " << totalWeight << " lbs" << endl;
        cout << "C.G. Location: " << cg << " inches" << endl;

        if (totalWeight > 2950 || cg < 82.1 || cg > 84.7) {
            cout << "Aircraft exceeds design limits." << endl;
        }
        else {
            cout << "Aircraft within design limits." << endl;
        }
    }
};

int main() {
    double emptyWeight, emptyWeightMoment;
    cout << "Enter airplane empty weight (pounds): ";
    cin >> emptyWeight;
    cout << "Enter airplane empty-weight moment (pounds-inches): ";
    cin >> emptyWeightMoment;

    Aircraft aircraft(emptyWeight, emptyWeightMoment);

    int numFrontSeats, numRearSeats;
    cout << "Enter the number of front seat occupants: ";
    cin >> numFrontSeats;
    for (int i = 0; i < numFrontSeats; ++i) {
        double weight, arm;
        cout << "Enter weight of front seat occupant " << i + 1 << " (pounds): ";
        cin >> weight;
        cout << "Enter front seat moment arm (inches): ";
        cin >> arm;
        aircraft.addFrontSeat(weight, arm);
    }

    cout << "Enter the number of rear seat occupants: ";
    cin >> numRearSeats;
    for (int i = 0; i < numRearSeats; ++i) {
        double weight, arm;
        cout << "Enter weight of rear seat occupant " << i + 1 << " (pounds): ";
        cin >> weight;
        cout << "Enter rear seat moment arm (inches): ";
        cin >> arm;
        aircraft.addRearSeat(weight, arm);
    }

    int numGallons;
    double fuelPerGallon, fuelArm;
    cout << "Enter the number of gallons of usable fuel (gallons): ";
    cin >> numGallons;
    cout << "Enter usable fuel weights per gallon (pounds): ";
    cin >> fuelPerGallon;
    cout << "Enter fuel tank moment arm (inches): ";
    cin >> fuelArm;
    aircraft.setFuel(numGallons, fuelPerGallon, fuelArm);

    double baggageWeight, baggageArm;
    cout << "Enter baggage weight (pounds): ";
    cin >> baggageWeight;
    cout << "Enter baggage moment arm (inches): ";
    cin >> baggageArm;
    aircraft.setBaggage(baggageWeight, baggageArm);

    aircraft.calculateWeightAndBalance();

    return 0;
}


