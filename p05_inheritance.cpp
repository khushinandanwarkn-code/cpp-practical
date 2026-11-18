// Practical 05 - Single and Multilevel Inheritance
// Person -> Student -> GraduateStudent
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <string>
using namespace std;

class Person {
protected:              // protected so derived classes can use them, outsiders can't
    string name;
    int age;
public:
    Person(string n, int a) : name(n), age(a) {}
    void showPerson() const {
        cout << "  Name      : " << name << "\n";
        cout << "  Age       : " << age << "\n";
    }
};

// single inheritance: Student IS-A Person
class Student : public Person {
protected:
    string studentId;
    string course;
public:
    Student(string n, int a, string id, string c)
        : Person(n, a), studentId(id), course(c) {}   // base part built first
    void showStudent() const {
        showPerson();                                   // reused from Person
        cout << "  Student ID: " << studentId << "\n";
        cout << "  Course    : " << course << "\n";
    }
};

// multilevel inheritance: GraduateStudent IS-A Student IS-A Person
class GraduateStudent : public Student {
    string researchTopic;
    string supervisor;
public:
    GraduateStudent(string n, int a, string id, string c, string topic, string guide)
        : Student(n, a, id, c), researchTopic(topic), supervisor(guide) {}
    void showGraduate() const {
        showStudent();                                  // which in turn calls showPerson()
        cout << "  Research  : " << researchTopic << "\n";
        cout << "  Supervisor: " << supervisor << "\n";
        cout << "  (name '" << name << "' came all the way down from Person)\n";
    }
};

int main() {
    Student s("Khushboo Nandanwar", 19, "AIDS-C-49", "B.Tech AI & Data Science");
    GraduateStudent g("Aditi Kulkarni", 23, "MT-2026-07", "M.Tech Data Science",
                      "Crop disease detection using CNNs", "Dr. S. Patil");

    cout << "Student (single inheritance: Person -> Student)\n";
    s.showStudent();

    cout << "\nGraduateStudent (multilevel: Person -> Student -> GraduateStudent)\n";
    g.showGraduate();
    return 0;
}
