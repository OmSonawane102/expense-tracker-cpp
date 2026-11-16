# Expense Tracker — C++

A simple **command-line Expense Tracker** built using **C++**.

> 🚧 **Project Status: In Development (Prototype)**
> Core CRUD operations are working. Persistence, categories, and other features are still in progress.

## About

The Expense Tracker allows users to record and manage their daily expenses from the terminal.

The main goal of this project is to practice **C++ programming, OOP, file handling, data structures, and clean project organization**.

## Features

### ✅ Completed
* Display main menu with ANSI styling
* Add a new expense (with balance check)
* View all expenses in a formatted table
* Edit an existing expense (description + amount)
* Delete an expense (refunds balance)
* In-memory balance tracking

### 🔄 In Progress / Planned
* [ ] Input validation (guard against non-numeric input)
* [ ] Save data to file (CSV or JSON)
* [ ] Load data when the program starts
* [ ] Search expenses by description or ID
* [ ] Categorize expenses
* [ ] Track income separately
* [ ] Calculate total expenses
* [ ] Monthly expense summary
* [ ] Budget tracking

## Technologies

* **C++20**
* Standard C++ Library (`<list>`, `<iomanip>`, `<string>`)
* Object-Oriented Programming
* CMake + Ninja build system
* MSVC compiler (Visual Studio)

## Project Status

The project is developed **phase by phase**. The prototype has the core menu and all basic CRUD operations working in-memory. The next major milestone is **file persistence** so data survives between sessions.

This README is updated as the project grows.

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
* Expense categories
* Monthly summary & statistics
* Unit testing
* Improved CLI interface

## AI Assistant

This project is being developed with the help of **[Antigravity CLI](https://antigravity.dev)** — an AI coding assistant by Google DeepMind, used for code analysis, planning, and step-by-step feature development.

## Author

**Om Sonawane**

---

⭐ This project is mainly for learning and improving C++ development skills.
