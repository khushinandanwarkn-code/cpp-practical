// Practical 01 - C++ Fundamentals (data types, constants, operators, I/O)
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    const int TOTAL_SUBJECTS = 3;     // this never changes, so it's a const
    const float PASS_MARKS = 40.0f;   // minimum marks needed in each subject

    string name;
    int rollNo;
    char division;
    float m1, m2, m3;

    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter roll number: ";
    cin >> rollNo;
    cout << "Enter division: ";
    cin >> division;
    cout << "Enter marks of 3 subjects (out of 100): ";
    cin >> m1 >> m2 >> m3;

    // arithmetic operators
    float total = m1 + m2 + m3;
    float percentage = total / TOTAL_SUBJECTS;
    int wholeTotal = static_cast<int>(total);
    int leftOver = wholeTotal % TOTAL_SUBJECTS;   // just to try out the % operator

    // relational and logical operators
    bool passedAll = (m1 >= PASS_MARKS) && (m2 >= PASS_MARKS) && (m3 >= PASS_MARKS);
    bool distinction = (percentage >= 75) && passedAll;
    bool weakSubject = (m1 < 50) || (m2 < 50) || (m3 < 50);

    cout << fixed << setprecision(2);
    cout << "\n--------- Result Card ---------\n";
    cout << "Name            : " << name << "\n";
    cout << "Roll No / Div   : " << rollNo << " / " << division << "\n";
    cout << "Marks           : " << m1 << ", " << m2 << ", " << m3 << "\n";
    cout << "Total           : " << total << " / " << TOTAL_SUBJECTS * 100 << "\n";
    cout << "Percentage      : " << percentage << "%\n";
    cout << "Total % 3       : " << leftOver << "\n";
    cout << "Passed all?     : " << (passedAll ? "Yes" : "No") << "\n";
    cout << "Distinction?    : " << (distinction ? "Yes" : "No") << "\n";
    cout << "Any weak subject: " << (weakSubject ? "Yes" : "No") << "\n";
    cout << "Size of int/float/double/char: " << sizeof(int) << "/" << sizeof(float)
         << "/" << sizeof(double) << "/" << sizeof(char) << " bytes\n";
    return 0;
}
