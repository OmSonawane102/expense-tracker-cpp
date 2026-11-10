// expense-tracker-cpp.cpp : Defines the entry point for the application.

#include <iostream>
#include <string>  // FIX 1: std::string was used without its header
#include <limits>  // FIX 1: std::numeric_limits was used without its header
#include <list>
#include <cstdlib> // FIX 1: system() lives here

class Transaction {
private:
	static int next_id; // FIX 2: shared counter now belongs to the class, so every constructor can use it
	int ID;
	std::string Description;
	float price;

public:
	// FIX 2 + FIX 3: initializer lists, price is no longer left uninitialized
	Transaction() : ID(next_id++), Description("Transaction"), price(0) {}
	Transaction(std::string desc, float amt) : ID(next_id++), Description(desc), price(amt) {}
};

int Transaction::next_id = 1; // FIX 2: static members must be defined once outside the class

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

	// Basic ANSI escape codes
	const std::string RESET = "\033[0m";
	const std::string BOLD = "\033[1m";

	// Initial balance creation
	Category bal;

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
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // FIX 6: flush leftover newline
			if (amount > bal.getBalance()) { // FIX 4: was '<', the check was reversed
				std::cout << "Insufficient amount" << std::endl;
			}
			else {
				std::string desc;
				std::cout << "Enter expense description : ";
				std::getline(std::cin, desc); // FIX 5: reads the whole line, not just one word
				Expense.push_back(Transaction(desc, amount)); // FIX 3: list holds Transaction objects, and desc/amount are now used
			}
		}
		else if (input_option == 'd') {
			int ID;
			std::cout << "Delete transaction ID : ";
			std::cin >> ID;
		}
		else if (input_option == 'l') {
			// FIX 7: listing doesn't need an ID, removed the copy-pasted prompt
			// TODO: print all transactions
		}
		else if (input_option == 'e') {
			int ID;
			std::cout << "Edit transaction ID : "; // FIX 7: prompt said "Delete"
			std::cin >> ID;
		}
		else if (input_option == 'q') {
			std::cout << "Press enter to exit.....";
			std::cin.get();
			return 0;
		}

		std::cin.get();
	}
}