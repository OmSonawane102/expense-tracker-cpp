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

std::string categoryToString(ExpenseCategory cat) {
	switch (cat) {
		case ExpenseCategory::Food:          return "Food";
		case ExpenseCategory::Rent:          return "Rent";
		case ExpenseCategory::Education:     return "Education";
		case ExpenseCategory::Transport:     return "Transport";
		case ExpenseCategory::Entertainment: return "Entertainment";
		case ExpenseCategory::Health:        return "Health";
		case ExpenseCategory::Shopping:      return "Shopping";
		case ExpenseCategory::Other:         return "Other";
		default:                             return "Unknown";
	}
}

ExpenseCategory selectCategory() {
	std::cout << std::endl;
	std::cout << "  Select category :" << std::endl;
	std::cout << "  [1] Food" << std::endl;
	std::cout << "  [2] Rent" << std::endl;
	std::cout << "  [3] Education" << std::endl;
	std::cout << "  [4] Transport" << std::endl;
	std::cout << "  [5] Entertainment" << std::endl;
	std::cout << "  [6] Health" << std::endl;
	std::cout << "  [7] Shopping" << std::endl;
	std::cout << "  [8] Other" << std::endl;
	std::cout << "  Choice : ";

	int choice;
	std::cin >> choice;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	switch (choice) {
		case 1: return ExpenseCategory::Food;
		case 2: return ExpenseCategory::Rent;
		case 3: return ExpenseCategory::Education;
		case 4: return ExpenseCategory::Transport;
		case 5: return ExpenseCategory::Entertainment;
		case 6: return ExpenseCategory::Health;
		case 7: return ExpenseCategory::Shopping;
		default: return ExpenseCategory::Other;
	}
}

int main() {

	char inputOption;
	std::string version = "PROTOTYPE";
	double amount;
	std::list<Transaction> expenses;
	std::list<Transaction>::iterator it;

	// Basic ANSI escape codes
	const std::string RESET = "\033[0m";
	const std::string BOLD = "\033[1m";

	// Initial wallet
	Wallet balance;
	balance.setBalance(0); // starts at zero; use [b]alance add to top up

	while (true) {
		clearConsole();

		std::cout << BOLD << "Expense Tracker CLI - " << RESET << version << std::endl;
		std::cout << "------------------------------------------------------------" << std::endl << std::endl;

		std::cout << "[a]dd expense" << std::endl;
		std::cout << "[b]alance add" << std::endl;
		std::cout << "[c]heck balance" << std::endl;
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
				ExpenseCategory cat = selectCategory();
				expenses.push_back(Transaction(desc, amount, cat));
				balance.setBalance(balance.getBalance() - amount);
				std::cout << "Expense added." << std::endl;
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
		else if (inputOption == 'c') {
			std::cout << "Current balance : " << std::fixed << std::setprecision(2) << balance.getBalance() << std::endl;
		}
		else if (inputOption == 'd') {
			if (expenses.empty()) {
				std::cout << "Nothing to delete - your list is empty." << std::endl;
			}
			else {
				int id;
				std::cout << "Delete transaction ID : ";
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
					balance.setBalance(balance.getBalance() + it->getPrice());
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
				std::cout << std::fixed << std::setprecision(2);
				std::cout << std::right << std::setw(4) << "ID"
					<< " | " << std::left << std::setw(25) << "Description"
					<< " | " << std::left << std::setw(15) << "Category"
					<< " | " << "Amount" << std::endl;
				std::cout << "------------------------------------------------------------" << std::endl;
				for (it = expenses.begin(); it != expenses.end(); it++) {
					std::cout << std::right << std::setw(4) << it->getID()
						<< " | " << std::left << std::setw(25) << it->getDescription()
						<< " | " << std::left << std::setw(15) << categoryToString(it->getCategory())
						<< " | " << it->getPrice() << std::endl;
				}
			}
			std::cout << "------------------------------------------------------------" << std::endl;
			std::cout << "Remaining balance : " << std::fixed << std::setprecision(2) << balance.getBalance() << std::endl;
		}
		else if (inputOption == 'e') {
			if (expenses.empty()) {
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
					double available = balance.getBalance() + it->getPrice();

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
						ExpenseCategory cat = selectCategory();
						it->setDescription(desc);
						it->setPrice(amount);
						it->setCategory(cat);
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

		std::cout << "\nPress enter to continue...";
		std::cin.get();
	}
}
