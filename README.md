# Object-Oriented-Programming-using-C-PERSONAL-EXPENSE-TRACKER-
A Smart Personal Expense Tracker built using C++17 and Object-Oriented Programming. Manage daily and recurring expenses, track monthly budgets, analyse spending habits, generate smart financial insights, and export digitally signed expense reports.
# 💰 Personal Expense Tracker – Smart Edition

A console-based **Personal Expense Tracker** developed using **C++17** and Object-Oriented Programming (OOP). This application helps users manage daily expenses, track recurring payments, monitor monthly budgets, analyse spending patterns, and generate signed financial reports.

The project also includes a unique **Smart Insights System** that analyses spending behaviour and provides personalised financial suggestions.

## 🚀 Features

- **Add Expenses:** Record daily expenses with amount, category, description, and date.
- **Recurring Expenses:** Add weekly, monthly, and yearly recurring expenses.
- **View Expenses:** Display all recorded expenses in a formatted table.
- **Delete Expenses:** Remove expenses using their unique ID.
- **Search Expenses:** Search expenses by category with case-insensitive matching.
- **Monthly Summary:** View category-wise spending totals and percentages.
- **Budget Management:** Set monthly budgets and monitor spending.
- **Budget Alerts:** Receive warnings when 80% of the budget is used and alerts when the budget is exceeded.
- **Sorting:** Sort expenses by date or amount.
- **Smart Insights:** Analyse spending personality, identify top spending categories, calculate daily averages, and predict month-end expenditure.
- **Daily Savings Challenge:** Get a suggested daily spending limit to stay within your budget.
- **Signed Reports:** Generate text reports containing a unique Project Signature.
- **File Handling:** Automatically save and load expense records using `expenses.txt`.

## ⭐ Unique Features

### 1. Smart Spending Insights
The application analyses monthly spending and identifies the user's spending personality:

- The Foodie
- The Explorer
- The Planner
- The Shopper
- The Specialist
- The Balanced Spender

It also calculates:
- Top spending category
- Average daily expenditure
- Projected month-end spending
- Personalised savings suggestions
- Daily savings challenges

### 2. Project Signature
The application generates a unique Project Signature using the FNV-1a hashing algorithm.

The signature is generated using the project owner's UID and report data, making each exported report traceable to the project.

## 🛠️ Technologies Used

- **Programming Language:** C++
- **Standard:** C++17
- **Compiler:** GCC / G++
- **Concepts:** Object-Oriented Programming
- **Libraries:** C++ Standard Template Library (STL)
- **File Handling:** `ifstream` and `ofstream`
- **Data Structures:** Vector and Map
- **Memory Management:** Smart Pointers (`unique_ptr`)

## 📚 OOP Concepts Implemented

This project demonstrates the following concepts:

1. Classes and Objects
2. Encapsulation
3. Inheritance
4. Polymorphism
5. Abstraction
6. Operator Overloading
7. Constructors and Destructors
8. Static Members
9. Exception Handling
10. Smart Pointers

## 💻 System Requirements

- Windows / Linux / macOS
- GCC or MinGW compiler
- C++17 support
- Any standard computer

## ⚙️ Installation and Execution

### Step 1: Clone the Repository

```bash
git clone https://github.com/YOUR-USERNAME/Personal-Expense-Tracker.git
```

### Step 2: Open the Project Folder

```bash
cd Personal-Expense-Tracker
```

### Step 3: Compile the Program

```bash
g++ -std=c++17 -Wall -o expense_tracker expense_tracker.cpp
```

### Step 4: Run the Program

**Windows:**
```bash
expense_tracker.exe
```

**Linux / macOS:**
```bash
./expense_tracker
```

## 📋 Application Menu

The application provides the following menu:

```text
PERSONAL EXPENSE TRACKER

1. Add expense
2. Add recurring expense
3. View all expenses
4. Delete expense by ID
5. Search by category
6. Monthly summary
7. Set monthly budget
8. Sort by date
9. Sort by amount (high to low)
10. Smart Insights
11. Export Signed Report
0. Save and exit
```

## 📁 Project Structure

```text
Personal-Expense-Tracker/
│
├── expense_tracker.cpp
├── expenses.txt
├── README.md
└── Expense_Report_MM_YYYY.txt
```

- `expense_tracker.cpp` – Main C++ source code.
- `expenses.txt` – Stores expense records and monthly budget.
- `README.md` – Project documentation.
- `Expense_Report_MM_YYYY.txt` – Generated monthly expense reports.

The data and report files are generated when the application runs.

## 🔮 Future Improvements

- Graphical User Interface (GUI)
- Database integration using SQLite
- Category-wise budget management
- Expense charts and visual analytics
- CSV and Excel report export
- Password protection and user authentication

## 🎯 Project Objective

The main objective of this project is to develop a practical expense management application while demonstrating the implementation of Object-Oriented Programming concepts in C++.

It combines expense tracking, budget monitoring, file handling, and intelligent spending analysis in one application.

## 👨‍💻 Author

**Mayan Pathania**

BCA (Data Science) – 2nd Year

Chandigarh University

## 📜 License

This project is available for educational and learning purposes. You may use and modify it with appropriate attribution.

---

⭐ If you find this project useful, consider giving this repository a star!
