// expense-tracker-cpp.h : Class declarations for the Expense Tracker application.

#pragma once

#include <string>
#include <list>

// ---------------------------------------------------------------------------
// ExpenseCategory
// Represents the type/category of an expense.
// ---------------------------------------------------------------------------
enum class ExpenseCategory {
	Food,
	Rent,
	Education,
	Transport,
	Entertainment,
	Health,
	Shopping,
	Other
};

std::string categoryToString(ExpenseCategory cat);
ExpenseCategory selectCategory();

// ---------------------------------------------------------------------------
// Transaction
// Represents a single expense entry with a unique auto-incremented ID,
// a human-readable description, a monetary amount, and a category.
// ---------------------------------------------------------------------------
class Transaction {
private:
	static int next_id;
	int m_id;
	std::string m_description;
	double m_price;
	ExpenseCategory m_category;

public:
	Transaction() : m_id(next_id++), m_description("Transaction"), m_price(0), m_category(ExpenseCategory::Other) {}
	Transaction(std::string desc, double amt, ExpenseCategory cat)
		: m_id(next_id++), m_description(desc), m_price(amt), m_category(cat) {}
	// Constructor used when loading from file — uses a known ID, does NOT advance next_id.
	Transaction(int knownId, std::string desc, double amt, ExpenseCategory cat)
		: m_id(knownId), m_description(desc), m_price(amt), m_category(cat) {}

	// Allows persistence layer to advance the global counter after loading all saved IDs.
	static void setNextId(int id) { next_id = id; }

	// Getters
	int getID() const { return m_id; }
	std::string getDescription() const { return m_description; }
	double getPrice() const { return m_price; }
	ExpenseCategory getCategory() const { return m_category; }

	// Setters
	void setDescription(std::string desc) { m_description = desc; }
	void setPrice(double amt) { m_price = amt; }
	void setCategory(ExpenseCategory cat) { m_category = cat; }
};

// ---------------------------------------------------------------------------
// Wallet
// Tracks the available balance. (Renamed from Category to avoid conflict with
// the ExpenseCategory enum.)
// ---------------------------------------------------------------------------
class Wallet {
private:
	double m_balance;

public:
	Wallet() : m_balance(0) {}

	double getBalance() const { return m_balance; }
	void setBalance(double bal) { m_balance = bal; }
};

// ---------------------------------------------------------------------------
// Utility
// ---------------------------------------------------------------------------
void clearConsole();
double readDouble(const std::string& prompt, double minVal = 0.0);
int readInt(const std::string& prompt);
std::string readNonEmptyString(const std::string& prompt);

// ---------------------------------------------------------------------------
// Persistence
// ---------------------------------------------------------------------------
static const std::string DATA_FILE = "expenses.json";

void saveData(const std::list<Transaction>& expenses, const Wallet& wallet);
bool loadData(std::list<Transaction>& expenses, Wallet& wallet);
