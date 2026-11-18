// Practical 09 - Generic Stack using Template
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <typename T>
class Stack {
    vector<T> items;
public:
    void push(T value) {
        items.push_back(value);
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty, nothing to pop" << endl;
            return;
        }
        cout << "Popped: " << items.back() << endl;
        items.pop_back();
    }

    T top() {
        if (isEmpty()) {
            cout << "Stack is empty, no top item" << endl;
            return T();
        }
        return items.back();
    }

    bool isEmpty() {
        return items.empty();
    }
};

int main() {
    Stack<int> s1;
    s1.push(10);
    s1.push(20);
    cout << "Top of int stack: " << s1.top() << endl;
    s1.pop();
    s1.pop();
    s1.pop();           // empty now

    Stack<float> s2;
    s2.push(1.5);
    s2.push(2.5);
    cout << "\nTop of float stack: " << s2.top() << endl;
    s2.pop();

    Stack<string> s3;
    s3.push("Hello");
    s3.push("World");
    cout << "\nTop of string stack: " << s3.top() << endl;
    s3.pop();
    s3.pop();
    s3.top();           // empty now
    return 0;
}
