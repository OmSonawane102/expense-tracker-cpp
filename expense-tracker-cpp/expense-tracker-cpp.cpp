// expense-tracker-cpp.cpp : Defines the entry point for the application.

#include <iostream>
#include <string>
#include <limits>
#include <list>
#include <iomanip> // NEW: setw() / setprecision() for the list output
#include <cstdlib>

class Transaction {
private:
	static int next_id;
	int ID;
	std::string Description;
	float price;

public:
	Transaction() : ID(next_id++), Description("Transaction"), price(0) {}
	Transaction(std::string desc, float amt) : ID(next_id++), Description(desc), price(amt) {}

	// NEW: getters (const, same style as TodoItem) so main() can read a transaction
	int getID() const { return ID; }
	std::string getDescription() const { return Description; }
	float getPrice() const { return price; }

	// NEW: setters so the edit option can change a transaction
	void setDescription(std::string desc) { Description = desc; }
	void setPrice(float amt) { price = amt; }
};

int Transaction::next_id = 1;

class Category {
private:
	float m_balance;
public:
	Category() {
		m_balance = 0;
	}
	float getBalance() {

		return m_balance;
	}
	void setBalance(float bal) {
		m_balance = bal;
	}
};

void clearConsole() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

int main() {

	char input_option;
	std::string version = "PROTOTYPE";
	float amount;
	std::list<Transaction> Expense;
	std::list<Transaction>::iterator it; // NEW: iterator used by list / delete / edit

	// Basic ANSI escape codes
	const std::string RESET = "\033[0m";
	const std::string BOLD = "\033[1m";

	// Initial balance creation
	Category bal;
	bal.setBalance(1000); // TEMPORARY starting balance so expenses can be added, change or remove later

	while (true) {
		clearConsole(); // clear screen after each iteration 

		std::cout << BOLD << "Expense Tracker CLI - " << RESET << version << std::endl;
		std::cout << "------------------------------------------------------------" << std::endl << std::endl;

		std::cout << "[a]dd expense" << std::endl;
		std::cout << "[d]elete expense" << std::endl;
		std::cout << "[l]ist expenses" << std::endl;
		std::cout << "[e]dit expense" << std::endl;
		std::cout << "[q]uit" << std::endl;

		std::cout << "Select option : ";
		std::cin >> input_option;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (input_option == 'a') {
			std::cout << "Input amount : ";
			std::cin >> amount;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (amount > bal.getBalance()) {
				std::cout << "Insufficient amount" << std::endl;
			}
			else {
				std::string desc;
				std::cout << "Enter expense description : ";
				std::getline(std::cin, desc);
				Expense.push_back(Transaction(desc, amount));
				bal.setBalance(bal.getBalance() - amount); // NEW: money spent leaves the balance
			}
		}
		else if (input_option == 'd') {
			if (Expense.empty()) { // NEW: nothing to delete
				std::cout << "Nothing to delete - your list is empty." << std::endl;
			}
			else {
				int ID;
				std::cout << "Delete transaction ID : ";
				std::cin >> ID;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				// search the list, stop at the matching ID (or reach the end if none matches)
				for (it = Expense.begin(); it != Expense.end(); it++) {
					if (ID == it->getID()) {
						break;
					}
				}

				if (it == Expense.end()) {
					std::cout << "Invalid ID no transaction found." << std::endl;
				}
				else {
					bal.setBalance(bal.getBalance() + it->getPrice()); // NEW: deleted expense gives money back
					Expense.erase(it);
					std::cout << "Transaction deleted." << std::endl;
				}
			}
		}
		else if (input_option == 'l') {
			if (Expense.empty()) {
				std::cout << "No expenses to show." << std::endl;
			}
			else {
				std::cout << std::fixed << std::setprecision(2); // show amounts with 2 decimals
				std::cout << std::right << std::setw(4) << "ID" << " | " << std::left << std::setw(30) << "Description" << " | " << "Amount" << std::endl;
				std::cout << "------------------------------------------------------------" << std::endl;
				for (it = Expense.begin(); it != Expense.end(); it++) {
					std::cout << std::right << std::setw(4) << it->getID() << " | " << std::left << std::setw(30) << it->getDescription() << " | " << it->getPrice() << std::endl;
				}
			}
			std::cout << "------------------------------------------------------------" << std::endl;
			std::cout << "Remaining balance : " << std::fixed << std::setprecision(2) << bal.getBalance() << std::endl;
		}
		else if (input_option == 'e') {
			if (Expense.empty()) { // NEW: nothing to edit
				std::cout << "Nothing to edit - your list is empty." << std::endl;
			}
			else {
				int ID;
				std::cout << "Edit transaction ID : ";
				std::cin >> ID;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				for (it = Expense.begin(); it != Expense.end(); it++) {
					if (ID == it->getID()) {
						break;
					}
				}

				if (it == Expense.end()) {
					std::cout << "Invalid ID no transaction found." << std::endl;
				}
				else {
					// money available = current balance + the old amount (which we are replacing)
					float available = bal.getBalance() + it->getPrice();

					std::cout << "Enter new amount : ";
					std::cin >> amount;
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (amount > available) {
						std::cout << "Insufficient amount" << std::endl;
					}
					else {
						std::string desc;
						std::cout << "Enter new description : ";
						std::getline(std::cin, desc);
						it->setDescription(desc);
						it->setPrice(amount);
						bal.setBalance(available - amount);
						std::cout << "Transaction updated." << std::endl;
					}
				}
			}
		}
		else if (input_option == 'q') {
			std::cout << "Press enter to exit.....";
			std::cin.get();
			return 0;
		}

		std::cin.get();
	}
}