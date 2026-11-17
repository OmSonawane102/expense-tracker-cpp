# Expense Tracker — C++

A simple **command-line Expense Tracker** built using **C++**.

> 🚧 **Project Status: In Development (Prototype)**
> Core CRUD operations, balance management, expense categories, and input validation are working. Persistence and advanced features are still in progress.

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
* **Input validation** across all user prompts:
  * Re-prompts on non-numeric input (amounts, IDs, category choice)
  * Rejects empty/whitespace-only descriptions
  * Category selection enforces 1–8 range
  * Invalid menu options show a clear error message

### 🔄 In Progress / Planned
* [ ] Save data to file (JSON via nlohmann/json — header included)
* [ ] Load data when the program starts
* [ ] Date/timestamp per expense
* [ ] Search expenses by description or ID
* [ ] Filter by category
* [ ] Monthly / weekly expense summary
* [ ] Budget tracking per category
* [ ] Color-coded output (over-budget = red, safe = green)
* [ ] Export to CSV
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
* Standard C++ Library (`<list>`, `<iomanip>`, `<string>`, `<limits>`, `<algorithm>`)
* Object-Oriented Programming
* [nlohmann/json](https://github.com/nlohmann/json) — single-header JSON library (vendored)
* CMake + Ninja build system
* MSVC compiler (Visual Studio)

## Project Structure

```
expense-tracker-cpp/
├── expense-tracker-cpp/
│   ├── expense-tracker-cpp.h    # Class declarations (Transaction, Wallet, ExpenseCategory)
│   ├── expense-tracker-cpp.cpp  # Main logic, menu, input helpers, category helpers
│   └── json.hpp                 # nlohmann/json single-header (vendored)
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

* File persistence (JSON)
* Date/timestamp per transaction
* Search & filter by category or description
* Monthly summary & statistics
* Budget tracking per category
* Color-coded terminal output
* Unit testing

## AI Assistant

This project is being developed with the help of **[Antigravity CLI](https://antigravity.dev)** — an AI coding assistant by Google DeepMind, used for code analysis, planning, and step-by-step feature development.

## Author

**Om Sonawane**

---

⭐ This project is mainly for learning and improving C++ development skills.
