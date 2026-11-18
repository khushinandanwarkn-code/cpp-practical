// Practical 12 - Mini Project: Library Management System (Option A)
// Uses: classes + inheritance/polymorphism, STL map, custom exceptions, CSV file I/O
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <string>
#include <stdexcept>
#include <limits>
#include <cstdlib>
using namespace std;

// ---------- exceptions ----------
class LibraryError : public runtime_error {
public:
    LibraryError(const string& m) : runtime_error(m) {}
};

// ---------- model classes ----------
class LibraryItem {                 // general item, kept abstract for future DVDs/magazines
protected:
    int id;
    string title;
public:
    LibraryItem(int i, string t) : id(i), title(t) {}
    virtual ~LibraryItem() {}
    virtual void display() const = 0;
    int getId() const { return id; }
    string getTitle() const { return title; }
};

class Book : public LibraryItem {
    string author;
    bool available;
public:
    Book(int i = 0, string t = "", string a = "", bool av = true)
        : LibraryItem(i, t), author(a), available(av) {}

    void display() const override {
        cout << "  " << left << setw(5) << id << setw(32) << title << setw(22) << author
             << (available ? "Available" : "Issued") << "\n";
    }
    bool isAvailable() const { return available; }
    string getAuthor() const { return author; }

    void issue() {
        if (!available) throw LibraryError("'" + title + "' is already issued");
        available = false;
    }
    void giveBack() {
        if (available) throw LibraryError("'" + title + "' was not issued, can't return it");
        available = true;
    }
    string toCSV() const {
        return to_string(id) + "," + title + "," + author + "," + (available ? "1" : "0");
    }
};

// ---------- the library itself ----------
class Library {
    map<int, Book> books;           // id -> book, keeps them sorted by id
    string fileName;

public:
    Library(const string& file) : fileName(file) {}

    void load() {
        ifstream in(fileName);
        if (!in) { cout << "(No saved data found, starting with an empty library)\n"; return; }
        string line;
        int count = 0;
        while (getline(in, line)) {
            stringstream ss(line);
            string idS, title, author, avS;
            if (getline(ss, idS, ',') && getline(ss, title, ',') &&
                getline(ss, author, ',') && getline(ss, avS)) {
                try {
                    int id = stoi(idS);
                    books[id] = Book(id, title, author, avS == "1");
                    count++;
                } catch (...) { /* skip bad line */ }
            }
        }
        cout << "(Loaded " << count << " books from " << fileName << ")\n";
    }

    void save() const {
        ofstream out(fileName);
        if (!out) throw LibraryError("Could not write to " + fileName);
        for (const auto& p : books) out << p.second.toCSV() << "\n";
    }

    void addBook(int id, const string& title, const string& author) {
        if (id <= 0) throw LibraryError("Book ID must be a positive number");
        if (books.count(id)) throw LibraryError("Book ID " + to_string(id) + " already exists");
        if (title.empty() || author.empty()) throw LibraryError("Title and author can't be empty");
        if (title.find(',') != string::npos || author.find(',') != string::npos)
            throw LibraryError("Please don't use commas (they break the CSV file)");
        books[id] = Book(id, title, author);
    }

    Book& find(int id) {
        auto it = books.find(id);
        if (it == books.end()) throw LibraryError("No book with ID " + to_string(id));
        return it->second;
    }

    void searchByTitle(const string& word) const {
        bool found = false;
        for (const auto& p : books) {
            string t = p.second.getTitle(), w = word;
            for (auto& c : t) c = tolower(c);
            for (auto& c : w) c = tolower(c);
            if (t.find(w) != string::npos) { p.second.display(); found = true; }
        }
        if (!found) cout << "  No book title contains \"" << word << "\"\n";
    }

    void listAll() const {
        if (books.empty()) { cout << "  Library is empty\n"; return; }
        cout << "  " << left << setw(5) << "ID" << setw(32) << "Title" << setw(22) << "Author"
             << "Status\n";
        for (const auto& p : books) p.second.display();
    }
};

int readInt(const string& prompt) {
    int x;
    cout << prompt;
    while (!(cin >> x)) {
        if (cin.eof()) exit(0);          // input closed, nothing more to do
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Please enter a number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return x;
}

string readLine(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

int main() {
    Library lib("books.csv");
    lib.load();

    while (true) {
        cout << "\n===== LIBRARY MENU =====\n"
             << "1. Add book   2. List books   3. Search by title\n"
             << "4. Issue book 5. Return book  6. Save & exit\n";
        int choice = readInt("Enter choice: ");
        try {
            if (choice == 1) {
                int id = readInt("Book ID: ");
                string title = readLine("Title: ");
                string author = readLine("Author: ");
                lib.addBook(id, title, author);
                cout << "  Book added.\n";
            } else if (choice == 2) {
                lib.listAll();
            } else if (choice == 3) {
                lib.searchByTitle(readLine("Search word: "));
            } else if (choice == 4) {
                Book& b = lib.find(readInt("Book ID to issue: "));
                b.issue();
                cout << "  Issued '" << b.getTitle() << "'. Please return within 14 days.\n";
            } else if (choice == 5) {
                Book& b = lib.find(readInt("Book ID to return: "));
                b.giveBack();
                cout << "  Returned '" << b.getTitle() << "'. Thank you!\n";
            } else if (choice == 6) {
                lib.save();
                cout << "  Data saved to books.csv. Bye!\n";
                break;
            } else {
                cout << "  Invalid choice, pick 1-6.\n";
            }
        } catch (const LibraryError& e) {
            cout << "  Error: " << e.what() << "\n";
        }
    }
    return 0;
}
