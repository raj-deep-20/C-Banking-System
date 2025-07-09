#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

class BankAccount {
    int accNumber;
    char name[50];
    char type;
    float balance;

public:
    void createAccount();
    void showAccount() const;
    void modify();
    void deposit(float);
    void withdraw(float);
    
    int getAccNumber() const;
    float getBalance() const;

    // ✅ Insert these public getters here:
    const char* getName() const { return name; }
    char getType() const { return type; }

    void displayHeader() const;
};

// Function declarations
void writeAccount();
void displayAll();
void displayOne(int);
void depositWithdraw(int, int);
void deleteAccount(int);
void modifyAccount(int);

#endif
