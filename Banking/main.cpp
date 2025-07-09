#include <iostream>
#include "BankSystem.h"
using namespace std;

int main() {
    int choice, accNo;

    do {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Display Specific Account\n";
        cout << "4. Deposit Amount\n";
        cout << "5. Withdraw Amount\n";
        cout << "6. Delete Account\n";
        cout << "7. Modify Account\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: writeAccount(); break;
            case 2: displayAll(); break;
            case 3:
                cout << "Enter Account Number: ";
                cin >> accNo;
                displayOne(accNo);
                break;
            case 4:
                cout << "Enter Account Number: ";
                cin >> accNo;
                depositWithdraw(accNo, 1);
                break;
            case 5:
                cout << "Enter Account Number: ";
                cin >> accNo;
                depositWithdraw(accNo, 2);
                break;
            case 6:
                cout << "Enter Account Number: ";
                cin >> accNo;
                deleteAccount(accNo);
                break;
            case 7:
                cout << "Enter Account Number: ";
                cin >> accNo;
                modifyAccount(accNo);
                break;
            case 0:
                cout << "Thank you for using the Bank System!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
