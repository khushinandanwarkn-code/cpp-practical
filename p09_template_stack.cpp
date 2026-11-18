// Practical 09 - Generic Stack using Templates
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class Stack {
    vector<T> items;   // vector does the memory work for us
public:
    void push(const T& value) { items.push_back(value); }

    T pop() {
        if (empty()) throw underflow_error("pop() called on an empty stack");
        T top = items.back();
        items.pop_back();
        return top;
    }

    const T& peek() const {          // safe way to look at the next item
        if (empty()) throw underflow_error("peek() called on an empty stack");
        return items.back();
    }

    bool empty() const { return items.empty(); }
    size_t size() const { return items.size(); }
};

// one helper that also works for every type
template <typename T>
void emptyOut(Stack<T>& s, const string& label) {
    cout << label << " (size " << s.size() << ", top = " << s.peek() << ") pops: ";
    while (!s.empty()) cout << s.pop() << "  ";
    cout << "\n";
}

int main() {
    Stack<int> intStack;
    for (int x : {10, 20, 30, 40}) intStack.push(x);

    Stack<float> floatStack;
    floatStack.push(1.5f);
    floatStack.push(2.75f);
    floatStack.push(9.9f);

    Stack<string> textStack;
    textStack.push("Khushboo");
    textStack.push("AIDS-C");
    textStack.push("Roll-49");

    emptyOut(intStack, "Stack<int>   ");
    emptyOut(floatStack, "Stack<float> ");
    emptyOut(textStack, "Stack<string>");

    cout << "\nEmpty-stack test cases:\n";
    try {
        intStack.pop();
    } catch (const underflow_error& e) {
        cout << "  Caught: " << e.what() << "\n";
    }
    try {
        textStack.peek();
    } catch (const underflow_error& e) {
        cout << "  Caught: " << e.what() << "\n";
    }
    cout << "  intStack.empty() = " << boolalpha << intStack.empty() << "\n";
    return 0;
}
