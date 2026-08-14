// expense-tracker-cpp.cpp : Defines the entry point for the application.
//

#include "expense-tracker-cpp.h"

#include <iostream>

void clearConsole() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

int main() {

	char input_option;
	std::string version = "PROTOTYPE - 01";

	// Basic ANSI escape codes
	const std::string RESET = "\033[0m";
	const std::string BOLD = "\033[1m";

	while (true) {
		clearConsole(); // clear screen after each iteration 

		std::cout << BOLD << "Expense Tracker CLI - " << RESET << version << std::endl;
		std::cout << "------------------------------------------------------------" << std::endl << std::endl;

		std::cout << "[a]dd transaction" << std::endl;
		std::cout <<

			std::cin.get();
	}
}

