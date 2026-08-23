// expense-tracker-cpp.cpp : Defines the entry point for the application.
//

#include "expense-tracker-cpp.h"

#include <iostream>

class Category {
private:
	static float balance;
public:
	float getBalance() {

		return balance;
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

	// Basic ANSI escape codes
	const std::string RESET = "\033[0m";
	const std::string BOLD = "\033[1m";

	while (true) {
		clearConsole(); // clear screen after each iteration 

		std::cout << BOLD << "Expense Tracker CLI - " << RESET << version << std::endl;
		std::cout << "------------------------------------------------------------" << std::endl << std::endl;

		std::cout << "[a]dd transaction" << std::endl;
		std::cout << "[d]elete transaction" << std::endl;
		std::cout << "[l]ist expenses" << std::endl;
		std::cout << "[e]dit expense" << std::endl;

		std::cout << "Select option : " << std::endl;
		std::cin >> input_option;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 


		std::cin.get();
	}
}

