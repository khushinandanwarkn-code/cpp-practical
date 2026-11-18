// Practical 02 - Classes and Access Specifiers
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:            // hidden, can't be changed directly from main()
    int accNo;
    string name;
    double balance;

public:             // these functions can be used from main()
    BankAccount(int a, string n, double b) {
        accNo = a;
        name = n;
        balance = (b < 0) ? 0 : b;   // no negative opening balance
    }

    void deposit(double amount) {
        if (amount > 0)
            balance += amount;
        else
            cout << "Invalid deposit amount" << endl;
    }

    void withdraw(double amount) {
        if (amount > balance)
            cout << "Not enough balance in account " << accNo << endl;
        else
            balance -= amount;
    }

    void display() {
        cout << accNo << " | " << name << " | Balance: " << balance << endl;
    }
};

int main() {
    BankAccount a1(101, "Khushboo", 5000);
    BankAccount a2(102, "Riya", 1000);

    a1.deposit(2000);
    a1.withdraw(1500);
    a2.withdraw(3000);   // more than balance
    a2.deposit(-100);    // wrong amount

    a1.display();
    a2.display();
    return 0;
}
