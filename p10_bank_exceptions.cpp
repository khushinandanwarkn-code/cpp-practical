// Practical 10 - Custom Exceptions in Banking
// Khushboo Nandanwar | Roll No. 49 | AIDS-C
#include <iostream>
#include <exception>
using namespace std;

class InvalidAmount : public exception {
public:
    const char* what() const noexcept override {
        return "Amount must be greater than 0";
    }
};

class InsufficientFunds : public exception {
public:
    const char* what() const noexcept override {
        return "Not enough balance";
    }
};

class BankAccount {
    double balance;
public:
    BankAccount(double b) { balance = b; }

    void withdraw(double amount) {
        if (amount <= 0) throw InvalidAmount();
        if (amount > balance) throw InsufficientFunds();
        balance -= amount;
        cout << "Withdrawn " << amount << ", balance left: " << balance << endl;
    }

    double getBalance() { return balance; }
};

int main() {
    BankAccount acc(5000);
    double tests[4] = {2000, -500, 8000, 1000};

    for (int i = 0; i < 4; i++) {
        try {
            acc.withdraw(tests[i]);
        } catch (InvalidAmount& e) {
            cout << "Error (" << tests[i] << "): " << e.what() << endl;
        } catch (InsufficientFunds& e) {
            cout << "Error (" << tests[i] << "): " << e.what() << endl;
        }
    }

    cout << "Final balance: " << acc.getBalance() << endl;
    return 0;
}
