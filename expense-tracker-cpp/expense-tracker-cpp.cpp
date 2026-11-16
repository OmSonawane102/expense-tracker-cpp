// expense-tracker-cpp.cpp : Defines the entry point for the application.

#include "expense-tracker-cpp.h"
#include <iostream>
#include <limits>
#include <list>
#include <iomanip>
#include <cstdlib>

// Static member definition (must live in exactly one .cpp)
int Transaction::next_id = 1;

void clearConsole() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

int main() {

	char inputOption;
	std::string version = "PROTOTYPE";
	float amount;
	std::list<Transaction> expenses;
	std::list<Transaction>::iterator it; // iterator used by list / delete / edit

	// Basic ANSI escape codes
	const std::string RESET = "\033[0m";
	const std::string BOLD = "\033[1m";

	// Initial balance creation
	Category balance;
	balance.setBalance(1000); // TEMPORARY starting balance so expenses can be added, change or remove later

	while (true) {
		clearConsole(); // clear screen after each iteration 

		std::cout << BOLD << "Expense Tracker CLI - " << RESET << version << std::endl;
		std::cout << "------------------------------------------------------------" << std::endl << std::endl;

		std::cout << "[a]dd expense" << std::endl;
		std::cout << "[b]alance add" << std::endl;
		std::cout << "[d]elete expense" << std::endl;
		std::cout << "[l]ist expenses" << std::endl;
		std::cout << "[e]dit expense" << std::endl;
		std::cout << "[q]uit" << std::endl;

		std::cout << "------------------------------------------------------------" << std::endl << std::endl;


		std::cout << "Select option : ";
		std::cin >> inputOption;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (inputOption == 'a') {
			std::cout << "Input amount : ";
			std::cin >> amount;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (amount > balance.getBalance()) {
				std::cout << "Insufficient amount" << std::endl;
			}
			else {
				std::string desc;
				std::cout << "Enter expense description : ";
				std::getline(std::cin, desc);
				expenses.push_back(Transaction(desc, amount));
				balance.setBalance(balance.getBalance() - amount); // money spent leaves the balance
			}
		}
		else if (inputOption == 'b') {
			std::cout << "Enter amount to add : ";
			std::cin >> amount;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (amount <= 0) {
				std::cout << "Amount must be greater than zero." << std::endl;
			}
			else {
				balance.setBalance(balance.getBalance() + amount);
				std::cout << "Balance updated. New balance : " << std::fixed << std::setprecision(2) << balance.getBalance() << std::endl;
			}
		}
		else if (inputOption == 'd') {
			if (expenses.empty()) { // nothing to delete
				std::cout << "Nothing to delete - your list is empty." << std::endl;
			}
			else {
				int id;
				std::cout << "Delete transaction ID : ";
				std::cin >> id;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				// search the list, stop at the matching ID (or reach the end if none matches)
				for (it = expenses.begin(); it != expenses.end(); it++) {
					if (id == it->getID()) {
						break;
					}
				}

				if (it == expenses.end()) {
					std::cout << "Invalid ID no transaction found." << std::endl;
				}
				else {
					balance.setBalance(balance.getBalance() + it->getPrice()); // deleted expense gives money back
					expenses.erase(it);
					std::cout << "Transaction deleted." << std::endl;
				}
			}
		}
		else if (inputOption == 'l') {
			if (expenses.empty()) {
				std::cout << "No expenses to show." << std::endl;
			}
			else {
				
				std::cout << std::fixed << std::setprecision(2); // show amounts with 2 decimals
				std::cout << std::right << std::setw(4) << "ID" << " | " << std::left << std::setw(30) << "Description" << " | " << "Amount" << std::endl;
				std::cout << "------------------------------------------------------------" << std::endl;
				for (it = expenses.begin(); it != expenses.end(); it++) {
					std::cout << std::right << std::setw(4) << it->getID() << " | " << std::left << std::setw(30) << it->getDescription() << " | " << it->getPrice() << std::endl;
				}
			}
			std::cout << "------------------------------------------------------------" << std::endl;
			std::cout << "Remaining balance : " << std::fixed << std::setprecision(2) << balance.getBalance() << std::endl;
		}
		else if (inputOption == 'e') {
			if (expenses.empty()) { // nothing to edit
				std::cout << "Nothing to edit - your list is empty." << std::endl;
			}
			else {
				int id;
				std::cout << "Edit transaction ID : ";
				std::cin >> id;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				for (it = expenses.begin(); it != expenses.end(); it++) {
					if (id == it->getID()) {
						break;
					}
				}

				if (it == expenses.end()) {
					std::cout << "Invalid ID no transaction found." << std::endl;
				}
				else {
					// money available = current balance + the old amount (which we are replacing)
					float available = balance.getBalance() + it->getPrice();

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
						balance.setBalance(available - amount);
						std::cout << "Transaction updated." << std::endl;
					}
				}
			}
		}
		else if (inputOption == 'q') {
			std::cout << "Press enter to exit.....";
			std::cin.get();
			return 0;
		}

		std::cin.get();
	}
}