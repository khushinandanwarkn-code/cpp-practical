// Practical 12 - Mini Project: Student Portal (Option C)
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
//
// A small console app for a class teacher: add students, see the whole list
// with grades, and search a student by ID. Everything is saved in
// students_data.csv, so the data is still there the next time it runs.

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdexcept>
#include <limits>
#include <cstdlib>
using namespace std;

// my own exception, used whenever the user enters something wrong
class PortalError : public runtime_error {
public:
    PortalError(const string& msg) : runtime_error(msg) {}
};

// base class - every person has a name
class Person {
protected:
    string name;
public:
    Person(string n) : name(n) {}
    virtual void show() const { cout << name << "\n"; }
    virtual ~Person() {}
};

// Student IS-A Person, plus ID, course and marks
class Student : public Person {
    int id;
    string course;
    int marks;
public:
    Student(int i, string n, string c, int m) : Person(n), id(i), course(c), marks(m) {}

    int getId() const { return id; }
    int getMarks() const { return marks; }

    string grade() const {
        if (marks >= 75) return "A";
        if (marks >= 60) return "B";
        if (marks >= 50) return "C";
        if (marks >= 40) return "D";
        return "F";
    }

    void show() const override {     // overrides Person::show()
        cout << "  " << left << setw(6) << id << setw(22) << name << setw(8) << course
             << setw(7) << marks << grade() << "\n";
    }

    string toCSV() const {
        return to_string(id) + "," + name + "," + course + "," + to_string(marks);
    }
};

class Portal {
    vector<Student> students;               // STL vector holds all the records
    string fileName = "students_data.csv";

public:
    void load() {
        ifstream in(fileName);
        if (!in) {
            cout << "(No saved file yet, starting fresh)\n";
            return;
        }
        string line;
        while (getline(in, line)) {
            stringstream ss(line);
            string id, name, course, marks;
            if (getline(ss, id, ',') && getline(ss, name, ',') &&
                getline(ss, course, ',') && getline(ss, marks)) {
                try {
                    students.push_back(Student(stoi(id), name, course, stoi(marks)));
                } catch (...) {
                    cout << "(Skipped a broken line in the file)\n";
                }
            }
        }
        cout << "(Loaded " << students.size() << " students from " << fileName << ")\n";
    }

    void save() const {
        ofstream out(fileName);
        if (!out) throw PortalError("Could not open " + fileName + " for saving");
        for (const Student& s : students) out << s.toCSV() << "\n";
    }

    void add(int id, const string& name, const string& course, int marks) {
        if (id <= 0) throw PortalError("ID must be a positive number");
        for (const Student& s : students)
            if (s.getId() == id) throw PortalError("ID " + to_string(id) + " is already taken");
        if (name.empty() || course.empty()) throw PortalError("Name and course can't be empty");
        if (name.find(',') != string::npos || course.find(',') != string::npos)
            throw PortalError("Please don't use commas, they break the CSV file");
        if (marks < 0 || marks > 100) throw PortalError("Marks should be between 0 and 100");
        students.push_back(Student(id, name, course, marks));
    }

    const Student& find(int id) const {
        for (const Student& s : students)
            if (s.getId() == id) return s;
        throw PortalError("No student with ID " + to_string(id));
    }

    void showAll() const {
        if (students.empty()) {
            cout << "  No students added yet\n";
            return;
        }
        cout << "  " << left << setw(6) << "ID" << setw(22) << "Name" << setw(8) << "Course"
             << setw(7) << "Marks" << "Grade\n";
        int total = 0;
        for (const Student& s : students) {
            s.show();
            total += s.getMarks();
        }
        cout << "  Class average: " << fixed << setprecision(2)
             << (double)total / students.size() << "\n";
    }
};

// keeps asking until the user actually types a number
int readInt(const string& prompt) {
    int x;
    cout << prompt;
    while (!(cin >> x)) {
        if (cin.eof()) exit(0);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  That's not a number, try again: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return x;
}

string readText(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

int main() {
    Portal portal;
    portal.load();

    while (true) {
        cout << "\n----- STUDENT PORTAL -----\n"
             << "1. Add student\n2. Show all students\n3. Search by ID\n4. Save and exit\n";
        int choice = readInt("Your choice: ");

        try {
            if (choice == 1) {
                int id = readInt("ID: ");
                string name = readText("Name: ");
                string course = readText("Course: ");
                int marks = readInt("Marks (0-100): ");
                portal.add(id, name, course, marks);
                cout << "  Student added!\n";
            } else if (choice == 2) {
                portal.showAll();
            } else if (choice == 3) {
                const Student& s = portal.find(readInt("Enter ID: "));
                s.show();
            } else if (choice == 4) {
                portal.save();
                cout << "  Saved. See you next time!\n";
                break;
            } else {
                cout << "  Please choose 1, 2, 3 or 4\n";
            }
        } catch (const PortalError& e) {
            cout << "  Oops: " << e.what() << "\n";
        }
    }
    return 0;
}
