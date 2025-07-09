#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "BankSystem.h"
using namespace std;

void BankAccount::createAccount() {
    cout << "Enter Account Number: ";
    cin >> accNumber;
    cin.ignore();
    cout << "Enter Account Holder Name: ";
    cin.getline(name, 50);
    cout << "Enter Account Type (S/C): ";
    cin >> type;
    type = toupper(type);
    cout << "Enter Initial Deposit: ";
    cin >> balance;
    cout << "Account Created Successfully!\n";
}

void BankAccount::showAccount() const {
    cout << "\nAccount No: " << accNumber
         << "\nName: " << name
         << "\nType: " << type
         << "\nBalance: " << balance << endl;
}

void BankAccount::modify() {
    cout << "Modify Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Modify Account Type (S/C): ";
    cin >> type;
    type = toupper(type);
    cout << "Modify Balance: ";
    cin >> balance;
    cout << "Account Modified Successfully!\n";
}

void BankAccount::deposit(float amt) {
    balance += amt;
}

void BankAccount::withdraw(float amt) {
    if (amt > balance)
        cout << "Insufficient Balance!\n";
    else
        balance -= amt;
}

int BankAccount::getAccNumber() const {
    return accNumber;
}

float BankAccount::getBalance() const {
    return balance;
}

void BankAccount::displayHeader() const {
    cout << left << setw(10) << "Acc No"
         << setw(20) << "Name"
         << setw(10) << "Type"
         << setw(10) << "Balance" << endl;
}

void writeAccount() {
    BankAccount acc;
    ofstream outFile("accounts.dat", ios::binary | ios::app);
    acc.createAccount();
    outFile.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
    outFile.close();
}

void displayAll() {
    BankAccount acc;
    ifstream inFile("accounts.dat", ios::binary);
    if (!inFile) {
        cout << "No account records found.\n";
        return;
    }
    acc.displayHeader();
    cout << "--------------------------------------------\n";
    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        cout << left << setw(10) << acc.getAccNumber()
            << setw(20) << acc.getName()
            << setw(10) << acc.getType()
            << setw(10) << acc.getBalance() << endl;
    }
    inFile.close();
}

void displayOne(int n) {
    BankAccount acc;
    bool found = false;
    ifstream inFile("accounts.dat", ios::binary);
    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        if (acc.getAccNumber() == n) {
            acc.showAccount();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found)
        cout << "Account not found.\n";
}

void depositWithdraw(int n, int option) {
    BankAccount acc;
    fstream File("accounts.dat", ios::binary | ios::in | ios::out);
    bool found = false;
    float amount;

    while (!File.eof() && !found) {
        streampos pos = File.tellg();
        File.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
        if (acc.getAccNumber() == n) {
            acc.showAccount();
            cout << (option == 1 ? "Enter amount to deposit: " : "Enter amount to withdraw: ");
            cin >> amount;
            if (option == 1)
                acc.deposit(amount);
            else
                acc.withdraw(amount);
            File.seekp(pos);
            File.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
            found = true;
            cout << "Transaction successful.\n";
        }
    }
    File.close();
    if (!found)
        cout << "Account not found.\n";
}

void deleteAccount(int n) {
    BankAccount acc;
    ifstream inFile("accounts.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        if (acc.getAccNumber() != n)
            outFile.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
        else
            found = true;
    }

    inFile.close();
    outFile.close();
    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if (found)
        cout << "Account deleted successfully.\n";
    else
        cout << "Account not found.\n";
}

void modifyAccount(int n) {
    BankAccount acc;
    fstream File("accounts.dat", ios::binary | ios::in | ios::out);
    bool found = false;

    while (!File.eof() && !found) {
        streampos pos = File.tellg();
        File.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
        if (acc.getAccNumber() == n) {
            acc.showAccount();
            acc.modify();
            File.seekp(pos);
            File.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));
            found = true;
        }
    }
    File.close();
    if (!found)
        cout << "Account not found.\n";
}
