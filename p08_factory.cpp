// Practical 08 - Factory Design Pattern
// Use case: a ride-booking app creates the right vehicle from what the user picks
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
using namespace std;

class Vehicle {
public:
    virtual string type() const = 0;
    virtual int capacity() const = 0;
    virtual double farePerKm() const = 0;
    double fare(double km) const { return km * farePerKm(); }
    virtual ~Vehicle() {}
};

class Bike : public Vehicle {
public:
    string type() const override { return "Bike"; }
    int capacity() const override { return 1; }
    double farePerKm() const override { return 7; }
};

class Auto : public Vehicle {
public:
    string type() const override { return "Auto"; }
    int capacity() const override { return 3; }
    double farePerKm() const override { return 12; }
};

class Cab : public Vehicle {
public:
    string type() const override { return "Cab"; }
    int capacity() const override { return 4; }
    double farePerKm() const override { return 18; }
};

// The factory: the ONLY place that knows which class to "new"
class VehicleFactory {
public:
    static unique_ptr<Vehicle> create(const string& choice) {
        if (choice == "bike") return make_unique<Bike>();
        if (choice == "auto") return make_unique<Auto>();
        if (choice == "cab")  return make_unique<Cab>();
        throw invalid_argument("No vehicle of type '" + choice + "'");
    }
};

int main() {
    string requests[] = {"bike", "cab", "auto", "helicopter"};
    double distanceKm = 8.5;   // e.g. Deccan to Hinjewadi side, roughly

    for (const string& r : requests) {
        try {
            unique_ptr<Vehicle> v = VehicleFactory::create(r);   // main never says "new Cab"
            cout << "Requested '" << r << "' -> got " << v->type()
                 << " | seats: " << v->capacity()
                 << " | fare for " << distanceKm << " km: Rs." << v->fare(distanceKm) << "\n";
        } catch (const invalid_argument& e) {
            cout << "Requested '" << r << "' -> error: " << e.what() << "\n";
        }
    }
    return 0;
}
