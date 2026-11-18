// Practical 11 - CSV Student Records using File I/O
// CSV format I decided on:  id,name,marks   (first line is a header)
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct Student {
    int id;
    string name;
    double marks;
};

bool writeCSV(const string& file, const vector<Student>& list) {
    ofstream out(file);                      // default mode = truncate and write
    if (!out) { cout << "Could not open " << file << " for writing\n"; return false; }
    out << "id,name,marks\n";
    for (const auto& s : list) out << s.id << "," << s.name << "," << s.marks << "\n";
    return out.good();                       // true if every write worked
}

vector<Student> readCSV(const string& file) {
    vector<Student> list;
    ifstream in(file);
    if (!in) { cout << "Could not open " << file << " for reading\n"; return list; }

    string line;
    getline(in, line);                       // skip header
    int lineNo = 1;
    while (getline(in, line)) {
        lineNo++;
        stringstream ss(line);
        string idStr, name, marksStr;
        if (!getline(ss, idStr, ',') || !getline(ss, name, ',') || !getline(ss, marksStr)) {
            cout << "  Skipping malformed line " << lineNo << ": \"" << line << "\"\n";
            continue;
        }
        try {
            list.push_back({stoi(idStr), name, stod(marksStr)});
        } catch (...) {
            cout << "  Skipping bad number on line " << lineNo << ": \"" << line << "\"\n";
        }
    }
    return list;
}

void positionDemo() {
    cout << "\n--- File position demo (positions.txt) ---\n";

    // tellp / seekp : the PUT (write) position
    fstream f("positions.txt", ios::out | ios::trunc);
    f << "ABCDEFGHIJ";
    cout << "tellp() after writing 10 letters  = " << f.tellp() << "\n";
    f.seekp(3);                              // jump back to index 3
    cout << "tellp() after seekp(3)            = " << f.tellp() << "\n";
    f << "xyz";                              // overwrite D,E,F
    f.close();

    // tellg / seekg : the GET (read) position
    ifstream r("positions.txt");
    cout << "tellg() when just opened          = " << r.tellg() << "\n";
    r.seekg(5);
    char c;
    r.get(c);
    cout << "after seekg(5), get() reads       = '" << c << "', tellg() = " << r.tellg() << "\n";
    r.seekg(-2, ios::end);                   // 2 chars before the end
    string tail;
    r >> tail;
    cout << "seekg(-2, ios::end) then read     = \"" << tail << "\"\n";
    r.clear();                               // reset EOF flag before seeking again
    r.seekg(0, ios::beg);
    string whole;
    r >> whole;
    cout << "whole file after the overwrite    = \"" << whole << "\"\n";
}

int main() {
    vector<Student> students = {
        {49, "Khushboo Nandanwar", 88.5},
        {12, "Riya Deshmukh", 76},
        {33, "Om Jadhav", 91.25},
        {50, "Sneha Pawar", 67}
    };

    if (writeCSV("students.csv", students))
        cout << "Wrote " << students.size() << " records to students.csv\n";

    // add one broken line on purpose, to test the malformed-input handling
    ofstream app("students.csv", ios::app);
    app << "77,Incomplete Row\n";
    app.close();

    cout << "\nReading students.csv back:\n";
    vector<Student> loaded = readCSV("students.csv");
    cout << left << setw(6) << "ID" << setw(22) << "Name" << "Marks\n";
    for (const auto& s : loaded)
        cout << left << setw(6) << s.id << setw(22) << s.name << s.marks << "\n";
    cout << "Valid records loaded: " << loaded.size() << "\n";

    positionDemo();
    return 0;
}
