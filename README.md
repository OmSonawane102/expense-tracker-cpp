# Expense Tracker — C++

A simple **command-line Expense Tracker** built using **C++**.

> 🚧 **Project Status: In Development (Prototype)**
> Core CRUD operations, balance management, and expense categories are working. Persistence and advanced features are still in progress.

## About

The Expense Tracker allows users to record and manage their daily expenses from the terminal.

The main goal of this project is to practice **C++ programming, OOP, file handling, data structures, and clean project organization**.

## Features

### ✅ Completed
* Display main menu with ANSI styling
* Add a new expense (with balance check)
* View all expenses in a formatted table (ID, Description, Category, Amount)
* Edit an existing expense (description, amount, and category)
* Delete an expense (refunds balance)
* Check current balance at any time
* Add balance manually via dedicated menu option
* **Expense categories** — select from a sub-menu when adding/editing:
  * Food, Rent, Education, Transport, Entertainment, Health, Shopping, Other
* Monetary values use `double` for precision
* Balance starts at zero — user adds balance before logging expenses
* "Press enter to continue" UX after every action

### 🔄 In Progress / Planned
* [ ] Input validation (guard against non-numeric input)
* [ ] Save data to file (CSV or JSON)
* [ ] Load data when the program starts
* [ ] Search expenses by description or ID
* [ ] Track income separately
* [ ] Calculate total expenses
* [ ] Monthly expense summary
* [ ] Budget tracking
* [ ] Unit testing

## Menu Options

| Key | Action |
|-----|--------|
| `a` | Add a new expense |
| `b` | Add balance to wallet |
| `c` | Check current balance |
| `d` | Delete an expense by ID |
| `l` | List all expenses |
| `e` | Edit an existing expense |
| `q` | Quit |

## Expense Categories

When adding or editing an expense, a category sub-menu is shown:

```
  Select category :
  [1] Food
  [2] Rent
  [3] Education
  [4] Transport
  [5] Entertainment
  [6] Health
  [7] Shopping
  [8] Other
```

## Technologies

* **C++20**
* Standard C++ Library (`<list>`, `<iomanip>`, `<string>`, `<limits>`)
* Object-Oriented Programming
* CMake + Ninja build system
* MSVC compiler (Visual Studio)

## Project Structure

```
expense-tracker-cpp/
├── expense-tracker-cpp/
│   ├── expense-tracker-cpp.h    # Class declarations (Transaction, Wallet, ExpenseCategory enum)
│   └── expense-tracker-cpp.cpp  # Main logic, menu, category helpers
├── CMakeLists.txt
└── CMakePresets.json
```

## How to Run

**Requirements:** Visual Studio 2022, CMake ≥ 3.10, Ninja

```bash
# Configure (x64 Debug)
cmake --preset x64-debug

# Build
cmake --build out/build/x64-debug

# Run
.\out\build\x64-debug\expense-tracker-cpp\expense-tracker-cpp.exe
```

## Future Improvements

* File persistence (CSV / JSON)
* Input validation & error handling
* Search & filter by category or description
* Monthly summary & statistics
* Budget tracking per category
* Unit testing

## AI Assistant

This project is being developed with the help of **[Antigravity CLI](https://antigravity.dev)** — an AI coding assistant by Google DeepMind, used for code analysis, planning, and step-by-step feature development.

## Author

**Om Sonawane**

---

⭐ This project is mainly for learning and improving C++ development skills.
