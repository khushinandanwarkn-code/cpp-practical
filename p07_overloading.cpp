// Practical 07 - Function and Operator Overloading
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
using namespace std;

// function overloading - same name, different parameters
int add(int a, int b) { return a + b; }
double add(double a, double b) { return a + b; }
int add(int a, int b, int c) { return a + b + c; }

class Complex {
    int real, imag;
public:
    Complex(int r = 0, int i = 0) {
        real = r;
        imag = i;
    }

    // operator overloading - lets us write c1 + c2
    Complex operator+(Complex other) {
        return Complex(real + other.real, imag + other.imag);
    }

    void show() {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    cout << "add(2, 3)       = " << add(2, 3) << endl;
    cout << "add(2.5, 1.5)   = " << add(2.5, 1.5) << endl;
    cout << "add(1, 2, 3)    = " << add(1, 2, 3) << endl;

    Complex c1(3, 4), c2(1, 2);
    Complex c3 = c1 + c2;

    cout << "\nc1 = "; c1.show();
    cout << "c2 = "; c2.show();
    cout << "c1 + c2 = "; c3.show();
    return 0;
}
