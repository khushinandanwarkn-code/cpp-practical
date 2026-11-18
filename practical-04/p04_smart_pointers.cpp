// Practical 04 - RAII and Smart Pointers
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Book {
public:
    string title;
    Book(string t) {
        title = t;
        cout << "  Book created: " << title << endl;
    }
    ~Book() {
        cout << "  Book deleted: " << title << endl;
    }
};

int main() {
    cout << "1) Raw pointer" << endl;
    Book* b1 = new Book("C++ Basics");
    delete b1;          // I have to remember this myself

    cout << "\n2) unique_ptr (only one owner)" << endl;
    {
        unique_ptr<Book> p1 = make_unique<Book>("Data Science");
        unique_ptr<Book> p2 = move(p1);     // ownership moves to p2
        cout << "  p1 is " << (p1 ? "not empty" : "empty") << endl;
        cout << "  p2 has " << p2->title << endl;
    }                   // deleted automatically here

    cout << "\n3) shared_ptr (many owners)" << endl;
    {
        shared_ptr<Book> s1 = make_shared<Book>("Python");
        cout << "  owners = " << s1.use_count() << endl;
        {
            shared_ptr<Book> s2 = s1;       // second owner
            cout << "  owners = " << s1.use_count() << endl;
        }
        cout << "  owners = " << s1.use_count() << endl;
    }                   // deleted when last owner is gone

    cout << "\nEnd of program" << endl;
    return 0;
}
