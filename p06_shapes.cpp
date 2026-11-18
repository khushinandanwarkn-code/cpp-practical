// Practical 06 - Runtime Polymorphism and Abstract Classes
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

const double PI = 3.14159265358979;

string num(double x) { ostringstream o; o << x; return o.str(); }   // 7 -> "7", 2.5 -> "2.5"

class Shape {                          // abstract class: has a pure virtual function
public:
    virtual double area() const = 0;   // "= 0" means every child MUST write its own area()
    virtual string name() const = 0;
    virtual ~Shape() {}                // virtual so the correct child destructor runs
};

class Circle : public Shape {
    double r;
public:
    Circle(double radius) : r(radius) {}
    double area() const override { return PI * r * r; }
    string name() const override { return "Circle (r = " + num(r) + ")"; }
};

class Rectangle : public Shape {
    double l, w;
public:
    Rectangle(double length, double width) : l(length), w(width) {}
    double area() const override { return l * w; }
    string name() const override { return "Rectangle (" + num(l) + " x " + num(w) + ")"; }
};

class Triangle : public Shape {
    double b, h;
public:
    Triangle(double base, double height) : b(base), h(height) {}
    double area() const override { return 0.5 * b * h; }
    string name() const override { return "Triangle (b = " + num(b) + ", h = " + num(h) + ")"; }
};

int main() {
    // Shape s;   // error: cannot declare variable 's' to be of abstract type 'Shape'

    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Circle>(7));
    shapes.push_back(make_unique<Rectangle>(6, 4.5));
    shapes.push_back(make_unique<Triangle>(10, 5));

    cout << fixed << setprecision(2);
    double total = 0;
    for (const auto& s : shapes) {     // s is a Shape pointer, but the right area() runs
        cout << left << setw(26) << s->name() << " area = " << s->area() << "\n";
        total += s->area();
    }
    cout << "Total area of all shapes = " << total << "\n";
    return 0;
}
