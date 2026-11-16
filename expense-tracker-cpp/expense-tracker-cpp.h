// expense-tracker-cpp.h : Class declarations for the Expense Tracker application.

#pragma once

#include <string>

// ---------------------------------------------------------------------------
// Transaction
// Represents a single expense entry with a unique auto-incremented ID,
// a human-readable description, and a monetary amount.
// ---------------------------------------------------------------------------
class Transaction {
private:
	static int next_id;
	int m_id;
	std::string m_description;
	double m_price;

public:
	Transaction() : m_id(next_id++), m_description("Transaction"), m_price(0) {}
	Transaction(std::string desc, double amt) : m_id(next_id++), m_description(desc), m_price(amt) {}

	// Getters
	int getID() const { return m_id; }
	std::string getDescription() const { return m_description; }
	double getPrice() const { return m_price; }

	// Setters
	void setDescription(std::string desc) { m_description = desc; }
	void setPrice(double amt) { m_price = amt; }
};

// ---------------------------------------------------------------------------
// Category
// Tracks the available balance. Will be extended later to support named
// expense categories (e.g. Food, Travel, Utilities).
// ---------------------------------------------------------------------------
class Category {
private:
	double m_balance;

public:
	Category() : m_balance(0) {}

	double getBalance() const { return m_balance; }
	void setBalance(double bal) { m_balance = bal; }
};

// ---------------------------------------------------------------------------
// Utility
// ---------------------------------------------------------------------------
void clearConsole();
