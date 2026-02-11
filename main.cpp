#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class BankAccount {
public:
    int accountNumber;
    string name;
    double balance;

    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void displayAccount() {
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nName: " << name;
        cout << "\nBalance: " << balance << endl;
    }
};

// Save account to file
void saveAccount(BankAccount acc) {
    ofstream file("bank.txt", ios::app);
    file << acc.accountNumber << " "
         << acc.name << " "
         << acc.balance << endl;
    file.close();
}

// Load all accounts from file
vector<BankAccount> loadAccounts() {
    vector<BankAccount> accounts;
    BankAccount acc;
    ifstream file("bank.txt");

    while (file >> acc.accountNumber >> acc.name >> acc.balance) {
        accounts.push_back(acc);
    }

    file.close();
    return accounts;
}

// Rewrite file
void updateFile(vector<BankAccount> accounts) {
    ofstream file("bank.txt");

    for (int i = 0; i < accounts.size(); i++) {
        file << accounts[i].accountNumber << " "
             << accounts[i].name << " "
             << accounts[i].balance << endl;
    }

    file.close();
}

// Display all accounts
void displayAllAccounts() {
    vector<BankAccount> accounts = loadAccounts();

    if (accounts.size() == 0) {
        cout << "No accounts found.\n";
        return;
    }

    for (int i = 0; i < accounts.size(); i++) {
        accounts[i].displayAccount();
    }
}

// Deposit money
void depositMoney(int accNo, double amount) {
    vector<BankAccount> accounts = loadAccounts();
    bool found = false;

    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].accountNumber == accNo) {
            accounts[i].balance += amount;
            cout << "Deposit Successful!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account Not Found!\n";
        return;
    }

    updateFile(accounts);
}

// Withdraw money
void withdrawMoney(int accNo, double amount) {
    vector<BankAccount> accounts = loadAccounts();
    bool found = false;

    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].accountNumber == accNo) {

            if (accounts[i].balance >= amount) {
                accounts[i].balance -= amount;
                cout << "Withdrawal Successful!\n";
            } else {
                cout << "Insufficient Balance!\n";
            }

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account Not Found!\n";
        return;
    }

    updateFile(accounts);
}

int main() {
    int choice;
    int accNo;
    double amount;

    while (true) {
        cout << "\n===== MINI BANKING SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        BankAccount acc;

        switch (choice) {
            case 1:
                acc.createAccount();
                saveAccount(acc);
                cout << "Account Created Successfully!\n";
                break;

            case 2:
                displayAllAccounts();
                break;

            case 3:
                cout << "Enter Account Number: ";
                cin >> accNo;
                cout << "Enter Amount to Deposit: ";
                cin >> amount;
                depositMoney(accNo, amount);
                break;

            case 4:
                cout << "Enter Account Number: ";
                cin >> accNo;
                cout << "Enter Amount to Withdraw: ";
                cin >> amount;
                withdrawMoney(accNo, amount);
                break;

            case 5:
                cout << "Thank you for using Banking System.\n";
                return 0;

            default:
                cout << "Invalid Choice!\n";
        }
    }
}
