// Practical 03 - Constructors and Rule of Five
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
using namespace std;

class Array {
    int* data;
    int size;

public:
    // default constructor
    Array() {
        size = 0;
        data = nullptr;
        cout << "Default constructor" << endl;
    }

    // parameterized constructor
    Array(int n) {
        size = n;
        data = new int[n];
        for (int i = 0; i < n; i++) data[i] = i + 1;
        cout << "Parameterized constructor" << endl;
    }

    // 1. copy constructor (deep copy - new memory)
    Array(const Array& other) {
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++) data[i] = other.data[i];
        cout << "Copy constructor" << endl;
    }

    // 2. copy assignment
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (int i = 0; i < size; i++) data[i] = other.data[i];
        }
        cout << "Copy assignment" << endl;
        return *this;
    }

    // 3. move constructor (just take the other's memory)
    Array(Array&& other) noexcept {
        size = other.size;
        data = other.data;
        other.data = nullptr;
        other.size = 0;
        cout << "Move constructor" << endl;
    }

    // 4. move assignment
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = other.data;
            other.data = nullptr;
            other.size = 0;
        }
        cout << "Move assignment" << endl;
        return *this;
    }

    // 5. destructor
    ~Array() {
        if (data != nullptr) cout << "Destructor: memory freed" << endl;
        delete[] data;
    }

    void show() {
        cout << "  [ ";
        for (int i = 0; i < size; i++) cout << data[i] << " ";
        cout << "]" << endl;
    }
};

int main() {
    Array a;              // default
    Array b(3);           // parameterized
    Array c(b);           // copy constructor
    a = b;                // copy assignment
    Array d(move(c));     // move constructor
    Array e;
    e = move(d);          // move assignment

    cout << "b:"; b.show();
    cout << "a:"; a.show();
    cout << "e:"; e.show();
    cout << "c (after move):"; c.show();
    return 0;             // destructors run here
}
