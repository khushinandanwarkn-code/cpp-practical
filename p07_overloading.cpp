// Practical 07 - Compile-Time Polymorphism: Function and Operator Overloading
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
using namespace std;

// ---- function overloading: same name, different parameter lists ----
int add(int a, int b)             { return a + b; }
double add(double a, double b)    { return a + b; }
int add(int a, int b, int c)      { return a + b + c; }

// ---- operator overloading ----
class ComplexNumber {
    double real, imag;
public:
    ComplexNumber(double r = 0, double i = 0) : real(r), imag(i) {}

    ComplexNumber operator+(const ComplexNumber& other) const {
        return ComplexNumber(real + other.real, imag + other.imag);
    }
    ComplexNumber operator-(const ComplexNumber& other) const {
        return ComplexNumber(real - other.real, imag - other.imag);
    }
    // (a+bi)(c+di) = (ac - bd) + (ad + bc)i
    ComplexNumber operator*(const ComplexNumber& other) const {
        return ComplexNumber(real * other.real - imag * other.imag,
                             real * other.imag + imag * other.real);
    }
    bool operator==(const ComplexNumber& other) const {
        return real == other.real && imag == other.imag;
    }
    // friend so that  cout << c  works
    friend ostream& operator<<(ostream& out, const ComplexNumber& c) {
        out << c.real << (c.imag < 0 ? " - " : " + ")
            << (c.imag < 0 ? -c.imag : c.imag) << "i";
        return out;
    }
};

int main() {
    cout << "Function overloading:\n";
    cout << "  add(4, 9)        = " << add(4, 9) << "      -> add(int, int)\n";
    cout << "  add(2.5, 3.75)   = " << add(2.5, 3.75) << "   -> add(double, double)\n";
    cout << "  add(1, 2, 3)     = " << add(1, 2, 3) << "      -> add(int, int, int)\n";

    ComplexNumber c1(3, 4), c2(1, -2);
    cout << "\nOperator overloading:\n";
    cout << "  c1      = " << c1 << "\n";
    cout << "  c2      = " << c2 << "\n";
    cout << "  c1 + c2 = " << c1 + c2 << "\n";
    cout << "  c1 - c2 = " << c1 - c2 << "\n";
    cout << "  c1 * c2 = " << c1 * c2 << "\n";

    // test case: (3 + 4i) + (1 - 2i) should be (4 + 2i)
    ComplexNumber expected(4, 2);
    cout << "  Test: c1 + c2 == 4 + 2i ? " << ((c1 + c2) == expected ? "PASS" : "FAIL") << "\n";
    return 0;
}
