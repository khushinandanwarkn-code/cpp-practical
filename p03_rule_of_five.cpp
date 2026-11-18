// Practical 03 - Constructors and the Rule of Five
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <utility>
using namespace std;

class IntArray {
    int* data;
    size_t size;
public:
    static int liveBuffers;   // my own small leak counter

    // default constructor
    IntArray() : data(nullptr), size(0) {
        cout << "Default constructor (empty array)\n";
    }

    // parameterized constructor
    IntArray(size_t n, int startValue) : data(new int[n]), size(n) {
        for (size_t i = 0; i < n; i++) data[i] = startValue + (int)i;
        liveBuffers++;
        cout << "Parameterized constructor (size " << n << ")\n";
    }

    // 1) destructor - frees the memory this object owns
    ~IntArray() {
        if (data) liveBuffers--;
        delete[] data;
    }

    // 2) copy constructor - deep copy, so both objects get their OWN array
    IntArray(const IntArray& other) : data(nullptr), size(other.size) {
        if (other.data) {
            data = new int[size];
            for (size_t i = 0; i < size; i++) data[i] = other.data[i];
            liveBuffers++;
        }
        cout << "Copy constructor (deep copy)\n";
    }

    // 3) copy assignment - copy first, then swap, so a failed copy loses nothing
    IntArray& operator=(const IntArray& other) {
        cout << "Copy assignment (deep copy)\n";
        if (this == &other) return *this;   // a = a should do nothing
        IntArray temp(other);
        swap(data, temp.data);
        swap(size, temp.size);
        return *this;                       // temp's destructor frees our old array
    }

    // 4) move constructor - just take the pointer, no new allocation
    IntArray(IntArray&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "Move constructor (ownership transferred)\n";
    }

    // 5) move assignment - free ours, take theirs
    IntArray& operator=(IntArray&& other) noexcept {
        cout << "Move assignment (ownership transferred)\n";
        if (this != &other) {
            if (data) liveBuffers--;
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    void set(size_t i, int v) { if (i < size) data[i] = v; }

    void print(const char* label) const {
        cout << "  " << label << " = [";
        for (size_t i = 0; i < size; i++) cout << data[i] << (i + 1 < size ? ", " : "");
        cout << "]  (size " << size << ")\n";
    }
};
int IntArray::liveBuffers = 0;

int main() {
    {
        IntArray a;                 // default
        IntArray b(4, 10);          // parameterized
        b.print("b");

        IntArray c(b);              // copy constructor
        c.set(0, 99);               // change c only
        b.print("b");
        c.print("c (changed index 0)");

        a = b;                      // copy assignment
        a.print("a");

        IntArray d(std::move(c));   // move constructor
        d.print("d");
        c.print("c after move");

        IntArray e;
        e = std::move(d);           // move assignment
        e.print("e");
        d.print("d after move");

        cout << "Buffers alive before leaving scope: " << IntArray::liveBuffers << "\n";
    }
    cout << "Buffers alive after all objects destroyed: " << IntArray::liveBuffers << "\n";
    return 0;
}
