// Practical 08 - Factory Design Pattern
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <string>
using namespace std;

class Vehicle {
public:
    virtual void info() = 0;
    virtual ~Vehicle() {}
};

class Bike : public Vehicle {
public:
    void info() { cout << "Bike: 2 wheels, 1 seat" << endl; }
};

class Car : public Vehicle {
public:
    void info() { cout << "Car: 4 wheels, 4 seats" << endl; }
};

class Bus : public Vehicle {
public:
    void info() { cout << "Bus: 6 wheels, 40 seats" << endl; }
};

// the factory - decides which object to create
Vehicle* createVehicle(string type) {
    if (type == "bike") return new Bike();
    if (type == "car")  return new Car();
    if (type == "bus")  return new Bus();
    return nullptr;     // unknown type
}

int main() {
    string orders[4] = {"bike", "car", "bus", "train"};

    for (int i = 0; i < 4; i++) {
        Vehicle* v = createVehicle(orders[i]);
        if (v != nullptr) {
            v->info();
            delete v;
        } else {
            cout << "Sorry, no vehicle called " << orders[i] << endl;
        }
    }
    return 0;
}
