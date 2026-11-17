// expense-tracker-cpp.cpp : Defines the entry point for the application.

#include "expense-tracker-cpp.h"
#include <iostream>
#include <limits>
#include <list>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

// Static member definition (must live in exactly one .cpp)
int Transaction::next_id = 1;

void clearConsole() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

// ---------------------------------------------------------------------------
// Input helpers
// ---------------------------------------------------------------------------

// Reads a double > minVal (default 0). Re-prompts on non-numeric or out-of-range.
double readDouble(const std::string& prompt, double minVal = 0.0) {
	double value;
	while (true) {
		std::cout << prompt;
		if (std::cin >> value) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (value > minVal) {
				return value;
			}
			std::cout << "  [!] Amount must be greater than "
				<< std::fixed << std::setprecision(2) << minVal
				<< ". Please try again." << std::endl;
		}
		else {
			std::cout << "  [!] Invalid input. Please enter a numeric value." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}

// Reads an integer. Re-prompts on non-numeric input.
int readInt(const std::string& prompt) {
	int value;
	while (true) {
		std::cout << prompt;
		if (std::cin >> value) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return value;
		}
		std::cout << "  [!] Invalid input. Please enter a whole number." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

// Reads a non-empty, non-whitespace-only string. Re-prompts if blank.
std::string readNonEmptyString(const std::string& prompt) {
	std::string value;
	while (true) {
		std::cout << prompt;
		std::getline(std::cin, value);
		// Check if string has at least one non-whitespace character
		bool hasContent = std::any_of(value.begin(), value.end(),
			[](unsigned char c) { return !std::isspace(c); });
		if (hasContent) {
			return value;
		}
		std::cout << "  [!] Description cannot be empty. Please try again." << std::endl;
	}
}

// ---------------------------------------------------------------------------

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
	int choice;
	while (true) {
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

		if (std::cin >> choice) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (choice >= 1 && choice <= 8) {
				break;
			}
			std::cout << "  [!] Please enter a number between 1 and 8." << std::endl;
		}
		else {
			std::cout << "  [!] Invalid input. Please enter a number between 1 and 8." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

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
			double amount = readDouble("Input amount : ");
			if (amount > balance.getBalance()) {
				std::cout << "  [!] Insufficient balance. You only have "
					<< std::fixed << std::setprecision(2) << balance.getBalance() << "." << std::endl;
			}
			else {
				std::string desc = readNonEmptyString("Enter expense description : ");
				ExpenseCategory cat = selectCategory();
				expenses.push_back(Transaction(desc, amount, cat));
				balance.setBalance(balance.getBalance() - amount);
				std::cout << "Expense added." << std::endl;
			}
		}
		else if (inputOption == 'b') {
			double amount = readDouble("Enter amount to add : ");
			balance.setBalance(balance.getBalance() + amount);
			std::cout << "Balance updated. New balance : "
				<< std::fixed << std::setprecision(2) << balance.getBalance() << std::endl;
		}
		else if (inputOption == 'c') {
			std::cout << "Current balance : " << std::fixed << std::setprecision(2) << balance.getBalance() << std::endl;
		}
		else if (inputOption == 'd') {
			if (expenses.empty()) {
				std::cout << "Nothing to delete - your list is empty." << std::endl;
			}
			else {
				int id = readInt("Delete transaction ID : ");

				for (it = expenses.begin(); it != expenses.end(); it++) {
					if (id == it->getID()) {
						break;
					}
				}

				if (it == expenses.end()) {
					std::cout << "  [!] No transaction found with ID " << id << "." << std::endl;
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
				int id = readInt("Edit transaction ID : ");

				for (it = expenses.begin(); it != expenses.end(); it++) {
					if (id == it->getID()) {
						break;
					}
				}

				if (it == expenses.end()) {
					std::cout << "  [!] No transaction found with ID " << id << "." << std::endl;
				}
				else {
					double available = balance.getBalance() + it->getPrice();
					std::cout << "  (Available budget for this expense: "
						<< std::fixed << std::setprecision(2) << available << ")" << std::endl;

					double amount = readDouble("Enter new amount : ");
					if (amount > available) {
						std::cout << "  [!] Insufficient balance. Available: "
							<< std::fixed << std::setprecision(2) << available << "." << std::endl;
					}
					else {
						std::string desc = readNonEmptyString("Enter new description : ");
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
		else {
			std::cout << "  [!] Invalid option '" << inputOption
				<< "'. Please choose from the menu." << std::endl;
		}

		std::cout << "\nPress enter to continue...";
		std::cin.get();
	}
}
