#include <iostream>
#include <vector>
#include <fstream>

class BankAccount {
private:
    std::string accountNumber;
    std::string accountHolder;
    double balance;

public:
    BankAccount(const std::string& accNum, const std::string& accHolder)
        : accountNumber(accNum), accountHolder(accHolder), balance(0.0) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposit successful. Current balance: " << balance << std::endl;
        } else {
            std::cout << "Invalid deposit amount." << std::endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Withdrawal successful. Current balance: " << balance << std::endl;
        } else {
            std::cout << "Invalid withdrawal amount or insufficient balance." << std::endl;
        }
    }

    void display() const {
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Account Holder: " << accountHolder << std::endl;
        std::cout << "Balance: " << balance << std::endl;
    }

    const std::string& getAccountNumber() const {
        return accountNumber;
    }

    void saveToFile(std::ofstream& outFile) const {
        outFile << accountNumber << "," << accountHolder << "," << balance << std::endl;
    }
};

class Bank {
private:
    std::vector<BankAccount> accounts;

public:
    void addAccount(const BankAccount& account) {
        accounts.push_back(account);
    }

    BankAccount* findAccount(const std::string& accNum) {
        for (BankAccount& account : accounts) {
            if (account.getAccountNumber() == accNum) {
                return &account;
            }
        }
        return nullptr;
    }

    void displayAllAccounts() const {
        for (const BankAccount& account : accounts) {
            account.display();
            std::cout << "------------------------" << std::endl;
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const BankAccount& account : accounts) {
                account.saveToFile(outFile);
            }
            outFile.close();
            std::cout << "Data saved to " << filename << std::endl;
        } else {
            std::cerr << "Unable to open file for writing." << std::endl;
        }
    }
};

int main() {
    Bank bank;

    // Load existing accounts from a file (if available)

    // Add initial accounts
    bank.addAccount(BankAccount("123456", "Alice"));
    bank.addAccount(BankAccount("789012", "Bob"));

    int choice;
    do {
        std::cout << "Banking System Menu:" << std::endl;
        std::cout << "1. Display all accounts" << std::endl;
        std::cout << "2. Deposit" << std::endl;
        std::cout << "3. Withdraw" << std::endl;
        std::cout << "4. Save to file" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                bank.displayAllAccounts();
                break;
            case 2: {
                std::string accNum;
                double amount;
                std::cout << "Enter account number: ";
                std::cin >> accNum;
                std::cout << "Enter amount to deposit: ";
                std::cin >> amount;
                BankAccount* account = bank.findAccount(accNum);
                if (account) {
                    account->deposit(amount);
                } else {
                    std::cout << "Account not found." << std::endl;
                }
                break;
            }
            case 3: {
                std::string accNum;
                double amount;
                std::cout << "Enter account number: ";
                std::cin >> accNum;
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amount;
                BankAccount* account = bank.findAccount(accNum);
                if (account) {
                    account->withdraw(amount);
                } else {
                    std::cout << "Account not found." << std::endl;
                }
                break;
            }
            case 4:
                bank.saveToFile("bank_data.txt");
                break;
            case 0:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 0);

    return 0;
}
