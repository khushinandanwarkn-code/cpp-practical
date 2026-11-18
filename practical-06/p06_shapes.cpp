// Practical 06 - Runtime Polymorphism and Abstract Class
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <string>
using namespace std;

class Shape {
public:
    virtual double area() = 0;     // pure virtual function
    virtual ~Shape() {}
};

class Circle : public Shape {
    double r;
public:
    Circle(double radius) { r = radius; }
    double area() { return 3.14 * r * r; }
};

class Rectangle : public Shape {
    double l, w;
public:
    Rectangle(double length, double width) { l = length; w = width; }
    double area() { return l * w; }
};

class Triangle : public Shape {
    double b, h;
public:
    Triangle(double base, double height) { b = base; h = height; }
    double area() { return 0.5 * b * h; }
};

int main() {
    Circle c(5);
    Rectangle r(4, 6);
    Triangle t(10, 3);

    Shape* shapes[3] = {&c, &r, &t};       // base class pointers
    string names[3] = {"Circle", "Rectangle", "Triangle"};

    for (int i = 0; i < 3; i++)
        cout << names[i] << " area = " << shapes[i]->area() << endl;

    // Shape s;   // error: Shape is abstract
    return 0;
}
