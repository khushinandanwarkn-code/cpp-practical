// Practical 11 - Student Records in a CSV File
// Format of each line: id,name,marks
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    // ---- write records ----
    ofstream out("students.csv");
    if (!out) {
        cout << "Could not open file" << endl;
        return 1;
    }
    out << "49,Khushboo,88\n";
    out << "12,Riya,76\n";
    out << "33,Om,91\n";
    out.close();
    cout << "3 records written to students.csv\n" << endl;

    // ---- read records back ----
    ifstream in("students.csv");
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string id, name, marks;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, marks, ',');
        cout << "ID: " << id << "  Name: " << name << "  Marks: " << marks << endl;
    }
    in.close();

    // ---- tellp() and seekp(): write position ----
    fstream f("demo.txt", ios::out);
    f << "HELLO WORLD";
    cout << "\ntellp() after writing = " << f.tellp() << endl;
    f.seekp(6);                 // go to position 6
    f << "THERE";               // overwrite WORLD
    f.close();

    // ---- tellg() and seekg(): read position ----
    ifstream r("demo.txt");
    cout << "tellg() at start      = " << r.tellg() << endl;
    r.seekg(6);                 // jump to position 6
    string word;
    r >> word;
    cout << "Word from position 6  = " << word << endl;
    r.seekg(0);
    getline(r, line);
    cout << "Full file now         = " << line << endl;
    return 0;
}
