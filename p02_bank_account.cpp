// Practical 02 - Classes, Access Specifiers and Member Functions
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    // private: nobody outside the class should change these directly,
    // otherwise anyone could just write  acc.balance = 1000000;
    string accountNumber;
    string holderName;
    double balance;

public:
    // public: these functions are the only way to use the object
    BankAccount(string accNo, string name, double openingBalance) {
        accountNumber = accNo;
        holderName = name;
        if (openingBalance < 0) {
            cout << "Opening balance can't be negative, setting it to 0.\n";
            openingBalance = 0;
        }
        balance = openingBalance;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "  Deposit failed: amount must be more than 0\n";
            return;
        }
        balance += amount;
        cout << "  Deposited Rs." << amount << " into " << accountNumber << "\n";
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "  Withdraw failed: amount must be more than 0\n";
        } else if (amount > balance) {
            cout << "  Withdraw failed: not enough balance in " << accountNumber << "\n";
        } else {
            balance -= amount;
            cout << "  Withdrew Rs." << amount << " from " << accountNumber << "\n";
        }
    }

    double getBalance() const { return balance; }

    void display() const {
        cout << "  [" << accountNumber << "] " << holderName
             << " | Balance: Rs." << balance << "\n";
    }
};

int main() {
    BankAccount acc1("SB-4901", "Khushboo Nandanwar", 5000);
    BankAccount acc2("SB-4902", "Riya Deshmukh", 1200);

    cout << "Opening details:\n";
    acc1.display();
    acc2.display();

    cout << "\nTransactions:\n";
    acc1.deposit(2500);
    acc1.withdraw(1000);
    acc2.withdraw(2000);   // should fail, only 1200 in the account
    acc2.deposit(-50);     // should fail, negative amount
    acc2.deposit(800);

    cout << "\nFinal details:\n";
    acc1.display();
    acc2.display();

    // acc1.balance = 99999;   // compile error: 'balance' is private
    return 0;
}
