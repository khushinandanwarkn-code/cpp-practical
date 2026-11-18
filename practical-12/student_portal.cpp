// Practical 12 - Mini Project: Student Portal
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
// Add students, see all with grades, search by ID.
// Data is saved in students_data.csv.
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

class Person {
protected:
    string name;
public:
    Person(string n) { name = n; }
    virtual void show() { cout << name << endl; }
    virtual ~Person() {}
};

class Student : public Person {
public:
    int id, marks;

    Student(int i, string n, int m) : Person(n) {
        id = i;
        marks = m;
    }

    string getName() { return name; }

    string grade() {
        if (marks >= 75) return "A";
        if (marks >= 60) return "B";
        if (marks >= 40) return "C";
        return "F";
    }

    void show() override {
        cout << id << "  " << name << "  " << marks << "  Grade " << grade() << endl;
    }
};

vector<Student> students;

void loadFile() {
    ifstream in("students_data.csv");
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string id, name, marks;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, marks, ',');
        students.push_back(Student(stoi(id), name, stoi(marks)));
    }
    cout << "(" << students.size() << " students loaded)" << endl;
}

void saveFile() {
    ofstream out("students_data.csv");
    for (Student s : students)
        out << s.id << "," << s.getName() << "," << s.marks << "\n";
}

string ask(string question) {
    string answer;
    cout << question;
    getline(cin, answer);
    return answer;
}

int main() {
    loadFile();

    while (true) {
        cout << "\n1. Add  2. Show all  3. Search  4. Save & exit" << endl;
        string choice = ask("Choice: ");

        try {
            if (choice == "1") {
                int id = stoi(ask("ID: "));
                string name = ask("Name: ");
                int marks = stoi(ask("Marks: "));

                if (marks < 0 || marks > 100)
                    throw runtime_error("marks must be 0 to 100");
                for (Student s : students)
                    if (s.id == id) throw runtime_error("this ID already exists");

                students.push_back(Student(id, name, marks));
                cout << "Student added" << endl;
            }
            else if (choice == "2") {
                for (Student s : students) s.show();
            }
            else if (choice == "3") {
                int id = stoi(ask("ID to search: "));
                bool found = false;
                for (Student s : students)
                    if (s.id == id) { s.show(); found = true; }
                if (!found) cout << "No student with ID " << id << endl;
            }
            else if (choice == "4") {
                saveFile();
                cout << "Saved. Bye!" << endl;
                break;
            }
            else {
                cout << "Please choose 1 to 4" << endl;
            }
        }
        catch (invalid_argument&) {
            cout << "Error: please type a number" << endl;
        }
        catch (runtime_error& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    return 0;
}
