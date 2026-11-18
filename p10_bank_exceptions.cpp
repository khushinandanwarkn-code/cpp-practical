// Practical 10 - Custom Exceptions: Banking Transaction
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// base for all of my banking errors, so I can also catch them all together if I want
class BankException : public runtime_error {
public:
    BankException(const string& msg) : runtime_error(msg) {}
};

class InvalidAmount : public BankException {
public:
    InvalidAmount(double amt)
        : BankException("Invalid amount Rs." + to_string((int)amt) + " (must be greater than 0)") {}
};

class InsufficientFunds : public BankException {
public:
    InsufficientFunds(double needed, double available)
        : BankException("Insufficient funds: tried Rs." + to_string((int)needed) +
                        " but balance is only Rs." + to_string((int)available)) {}
};

class BankAccount {
    string owner;
    double balance;
public:
    BankAccount(string o, double b) : owner(o), balance(b) {}

    void withdraw(double amount) {
        if (amount <= 0) throw InvalidAmount(amount);
        if (amount > balance) throw InsufficientFunds(amount, balance);
        balance -= amount;           // only reached if both checks pass
    }

    void transfer(BankAccount& to, double amount) {
        withdraw(amount);            // if this throws, nothing below runs
        to.balance += amount;
    }

    double getBalance() const { return balance; }
    string getOwner() const { return owner; }
};

void tryWithdraw(BankAccount& acc, double amount) {
    cout << "Withdraw Rs." << amount << " from " << acc.getOwner() << ": ";
    try {
        acc.withdraw(amount);
        cout << "SUCCESS";
    } catch (const InvalidAmount& e) {
        cout << "FAILED [InvalidAmount] " << e.what();
    } catch (const InsufficientFunds& e) {
        cout << "FAILED [InsufficientFunds] " << e.what();
    }
    cout << "  -> balance now Rs." << acc.getBalance() << "\n";
}

int main() {
    BankAccount khushboo("Khushboo", 10000);
    BankAccount riya("Riya", 2000);

    tryWithdraw(khushboo, 3500);   // ok
    tryWithdraw(khushboo, -200);   // invalid amount
    tryWithdraw(khushboo, 0);      // invalid amount
    tryWithdraw(riya, 5000);       // more than balance

    cout << "\nTransfer Rs.4000 Khushboo -> Riya: ";
    try {
        khushboo.transfer(riya, 4000);
        cout << "SUCCESS\n";
    } catch (const BankException& e) {
        cout << "FAILED " << e.what() << "\n";
    }

    cout << "Transfer Rs.9000 Riya -> Khushboo: ";
    try {
        riya.transfer(khushboo, 9000);
        cout << "SUCCESS\n";
    } catch (const BankException& e) {   // catching through the base class
        cout << "FAILED " << e.what() << "\n";
    }

    cout << "\nFinal balances -> Khushboo: Rs." << khushboo.getBalance()
         << ", Riya: Rs." << riya.getBalance() << "\n";
    return 0;
}
