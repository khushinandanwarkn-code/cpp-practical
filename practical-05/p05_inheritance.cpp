// Practical 05 - Single and Multilevel Inheritance
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    Person(string n, int a) {
        name = n;
        age = a;
    }
    void showPerson() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

// single inheritance
class Student : public Person {
protected:
    int id;
    string course;
public:
    Student(string n, int a, int i, string c) : Person(n, a) {
        id = i;
        course = c;
    }
    void showStudent() {
        showPerson();
        cout << "ID: " << id << ", Course: " << course << endl;
    }
};

// multilevel inheritance
class GraduateStudent : public Student {
    string topic;
public:
    GraduateStudent(string n, int a, int i, string c, string t) : Student(n, a, i, c) {
        topic = t;
    }
    void showGraduate() {
        showStudent();
        cout << "Research: " << topic << endl;
    }
};

int main() {
    Student s("Khushboo", 19, 49, "AIDS");
    GraduateStudent g("Aditi", 23, 7, "M.Tech", "Machine Learning");

    cout << "--- Student ---" << endl;
    s.showStudent();

    cout << "\n--- Graduate Student ---" << endl;
    g.showGraduate();
    return 0;
}
