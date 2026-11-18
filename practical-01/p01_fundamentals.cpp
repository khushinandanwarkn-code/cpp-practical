// Practical 01 - C++ Fundamentals
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <string>
using namespace std;

int main() {
    const int SUBJECTS = 3;      // constant, never changes
    const int PASS_MARKS = 40;   // constant

    string name;
    int roll;
    float m1, m2, m3;

    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter roll number: ";
    cin >> roll;
    cout << "Enter marks of 3 subjects: ";
    cin >> m1 >> m2 >> m3;

    // arithmetic operators
    float total = m1 + m2 + m3;
    float average = total / SUBJECTS;

    // relational and logical operators
    bool passed = (m1 >= PASS_MARKS) && (m2 >= PASS_MARKS) && (m3 >= PASS_MARKS);
    bool topper = (average >= 75) || (total >= 225);

    cout << "\nName    : " << name << endl;
    cout << "Roll No : " << roll << endl;
    cout << "Total   : " << total << endl;
    cout << "Average : " << average << endl;
    cout << "Passed  : " << (passed ? "Yes" : "No") << endl;
    cout << "Topper  : " << (topper ? "Yes" : "No") << endl;
    return 0;
}
