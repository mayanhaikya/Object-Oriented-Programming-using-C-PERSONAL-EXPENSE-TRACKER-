#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <map>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <ctime>
#include <limits>
#include <cstdint>
using namespace std;
 
class Date {
    int day, month, year;
public:
    Date() {                                   
        time_t t = time(nullptr);
        tm* lt = localtime(&t);
        day = lt->tm_mday; month = lt->tm_mon + 1; year = lt->tm_year + 1900;
    }
    Date(int d, int m, int y) {
        if (!isValid(d, m, y)) throw invalid_argument("Invalid date entered.");
        day = d; month = m; year = y;
    }
    static bool isLeap(int y) { return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0); }
    static int daysInMonth(int m, int y) {
        int dim[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (isLeap(y)) dim[1] = 29;
        return dim[m - 1];
    }
    static bool isValid(int d, int m, int y) {
        if (y < 1900 || y > 2100 || m < 1 || m > 12 || d < 1) return false;
        return d <= daysInMonth(m, y);
    }
    int getDay() const   { return day; }
    int getMonth() const { return month; }
    int getYear() const  { return year; }
 
    bool operator<(const Date& o) const {      
        if (year != o.year) return year < o.year;
        if (month != o.month) return month < o.month;
        return day < o.day;
    }
    string toString() const {
        ostringstream o;
        o << setfill('0') << setw(2) << day << "-" << setw(2) << month << "-" << year;
        return o.str();
    }
    friend ostream& operator<<(ostream& os, const Date& d) { return os << d.toString(); }
};
 
class Expense {
    static int nextId;                         
protected:
    int id;
    double amount;
    string category, description;
    Date date;
public:
    Expense(double amt, const string& cat, const string& desc, const Date& dt, int fixedId = 0)
        : amount(amt), category(cat), description(desc), date(dt) {
        if (amt <= 0) throw invalid_argument("Amount must be greater than zero.");
        if (fixedId > 0) { id = fixedId; if (fixedId >= nextId) nextId = fixedId + 1; }
        else id = nextId++;
    }
    virtual ~Expense() {}
 
    virtual string type() const { return "ONE"; }
    virtual string extra() const { return "-"; }
    virtual void display() const {             
        cout << left << setw(5) << id << setw(13) << date << setw(14) << category
             << right << setw(10) << fixed << setprecision(2) << amount << "  "
             << left << setw(22) << description << setw(10) << "One-time" << "\n";
    }
    virtual string toFileString() const {
        ostringstream o;
        o << type() << "|" << id << "|" << amount << "|" << category << "|" << description
          << "|" << date.getDay() << "|" << date.getMonth() << "|" << date.getYear()
          << "|" << extra();
        return o.str();
    }
 
    int getId() const { return id; }
    double getAmount() const { return amount; }
    const string& getCategory() const { return category; }
    const Date& getDate() const { return date; }
 
    bool operator<(const Expense& o) const { return amount < o.amount; }
    static void resetCounter() { nextId = 1; }
};
int Expense::nextId = 1;
 
class RecurringExpense : public Expense {
    string frequency;                          
public:
    RecurringExpense(double amt, const string& cat, const string& desc, const Date& dt,
                     const string& freq, int fixedId = 0)
        : Expense(amt, cat, desc, dt, fixedId), frequency(freq) {}
    string type() const override  { return "REC"; }
    string extra() const override { return frequency; }
    void display() const override {
        cout << left << setw(5) << id << setw(13) << date << setw(14) << category
             << right << setw(10) << fixed << setprecision(2) << amount << "  "
             << left << setw(22) << description << setw(10) << frequency << "\n";
    }
};
 
class Budget {
    double limit;
public:
    Budget() : limit(0) {}
    void setLimit(double l) {
        if (l < 0) throw invalid_argument("Budget cannot be negative.");
        limit = l;
    }
    double getLimit() const { return limit; }
    string status(double spent) const {
        if (limit <= 0) return "No monthly budget set";
        ostringstream o;
        o << fixed << setprecision(1) << spent / limit * 100.0 << "% of Rs "
          << setprecision(2) << limit << " used"
          << (spent > limit ? " (EXCEEDED)" : " (within budget)");
        return o.str();
    }
    void check(double spent) const {
        if (limit <= 0) { cout << "  (No monthly budget set.)\n"; return; }
        double pct = spent / limit * 100.0;
        cout << "  Budget: Rs " << fixed << setprecision(2) << limit
             << " | Used: " << setprecision(1) << pct << "%\n";
        if (spent > limit)        cout << "  !! ALERT: Budget exceeded by Rs " << setprecision(2) << spent - limit << "\n";
        else if (pct >= 80.0)     cout << "  ** WARNING: You have used 80% or more of your budget.\n";
        else                      cout << "  You are within your budget.\n";
    }
};
 
class ProjectSignature {
public:
    static string owner()  { return "Mayan Pathania"; }
    static string uid()    { return "25BCD10212"; }
    static string course() { return "BCA - 2nd Year"; }
    static string university() { return "Chandigarh University"; }
 
    static string stamp(const string& content) {
        uint32_t h = 2166136261u;                        // FNV-1a hash
        for (unsigned char c : uid() + content) { h ^= c; h *= 16777619u; }
        ostringstream o;
        o << "MP-" << uid() << "-" << hex << uppercase << setw(8) << setfill('0') << h;
        return o.str();
    }
    static string banner() {
        ostringstream o;
        o           << "PERSONAL EXPENSE TRACKER  -  Smart Edition\n"
          << "Developed by : " << left << setw(40) << owner()      << "\n"
          << "UID          : " << setw(40) << uid()                << "\n"
          << "Course       : " << setw(40) << course() + " (OOPS - C++)" << "\n"
          << "University   : " << setw(40) << university()         << "\n"
          << "+------------------------------------------------------------+\n";
        return o.str();
    }
};
 
class ExpenseTracker {
    vector<unique_ptr<Expense>> expenses;
    Budget budget;
    string fileName;
 
    static void header() {
        cout << left << setw(5) << "ID" << setw(13) << "Date" << setw(14) << "Category"
             << right << setw(10) << "Amount" << "  " << left << setw(22) << "Description"
             << setw(10) << "Type" << "\n" << string(76, '-') << "\n";
    }
    static string lower(string s) { for (char& c : s) c = tolower(c); return s; }
public:
    explicit ExpenseTracker(const string& f) : fileName(f) {}
 
    void add(unique_ptr<Expense> e) { expenses.push_back(move(e)); }
 
    void viewAll() const {
        if (expenses.empty()) { cout << "No expenses recorded yet.\n"; return; }
        header();
        for (const auto& e : expenses) e->display();
        double total = 0; for (const auto& e : expenses) total += e->getAmount();
        cout << string(76, '-') << "\nTotal: Rs " << fixed << setprecision(2) << total << "\n";
    }
 
    bool remove(int id) {
        auto it = find_if(expenses.begin(), expenses.end(),
                          [id](const unique_ptr<Expense>& e) { return e->getId() == id; });
        if (it == expenses.end()) return false;
        expenses.erase(it);
        return true;
    }
 
    void searchByCategory(const string& cat) const {
        bool found = false; double sum = 0;
        for (const auto& e : expenses)
            if (lower(e->getCategory()) == lower(cat)) {
                if (!found) header();
                e->display(); sum += e->getAmount(); found = true;
            }
        if (!found) cout << "No expenses found in category '" << cat << "'.\n";
        else cout << string(76, '-') << "\nCategory total: Rs " << fixed << setprecision(2) << sum << "\n";
    }
 
    void monthlySummary(int m, int y) const {
        map<string, double> byCat; double total = 0; int count = 0;
        for (const auto& e : expenses)
            if (e->getDate().getMonth() == m && e->getDate().getYear() == y) {
                byCat[e->getCategory()] += e->getAmount();
                total += e->getAmount(); ++count;
            }
        cout << "\n--- Summary for " << setfill('0') << setw(2) << m << "/" << y << setfill(' ') << " \n";
        if (count == 0) { cout << "No expenses in this month.\n"; return; }
        for (const auto& p : byCat) {
            double pct = p.second / total * 100.0;
            cout << left << setw(15) << p.first << right << "Rs " << setw(10) << fixed
                 << setprecision(2) << p.second << "  (" << setprecision(1) << pct << "%)\n";
        }
        cout << "Transactions: " << count << "\nTotal spent : Rs " << fixed << setprecision(2) << total << "\n";
        budget.check(total);
    }
 
    void sortByDate()   { sort(expenses.begin(), expenses.end(),
                               [](const unique_ptr<Expense>& a, const unique_ptr<Expense>& b)
                               { return a->getDate() < b->getDate(); }); }
    void sortByAmount() { sort(expenses.begin(), expenses.end(),
                               [](const unique_ptr<Expense>& a, const unique_ptr<Expense>& b)
                               { return *b < *a; }); }   // highest first
 
    void setBudget(double l) { budget.setLimit(l); }
 
    /* ===== *** UNIQUE FEATURE*** ===== */

    string buildInsights(int m, int y) const {
        map<string, double> byCat; double total = 0; int count = 0;
        for (const auto& e : expenses)
            if (e->getDate().getMonth() == m && e->getDate().getYear() == y) {
                byCat[e->getCategory()] += e->getAmount(); total += e->getAmount(); ++count;
            }
        ostringstream o;
        if (count == 0) { o << "No expenses in this month, so no insights yet.\n"; return o.str(); }
 
        string topCat; double topAmt = 0;
        for (const auto& p : byCat) if (p.second > topAmt) { topAmt = p.second; topCat = p.first; }
        double share = topAmt / total * 100.0;
 
        string personality, tip, key = lower(topCat);
        if (share < 45)                 { personality = "The Balanced Spender";
                                          tip = "Great spread across categories. Keep tracking to hold this balance."; }
        else if (key == "food")         { personality = "The Foodie";
                                          tip = "Cook at home two extra days a week; food is your biggest cost."; }
        else if (key == "travel")       { personality = "The Explorer";
                                          tip = "Try a monthly pass or carpooling to cut travel costs."; }
        else if (key == "bills" || key == "rent")
                                        { personality = "The Planner";
                                          tip = "Most money goes to fixed costs; review plans for cheaper options."; }
        else if (key == "shopping")     { personality = "The Shopper";
                                          tip = "Use a 24-hour wait rule before non-essential purchases."; }
        else                            { personality = "The Specialist (" + topCat + ")";
                                          tip = "One category dominates; check if it can be trimmed."; }
 
        int dim = Date::daysInMonth(m, y);
        Date today; bool current = (today.getMonth() == m && today.getYear() == y);
        int elapsed = current ? today.getDay() : dim;
        double daily = total / elapsed;
        double projected = current ? daily * dim : total;
 
        o << fixed << setprecision(2)
          << "Spending personality : " << personality << "\n"
          << "Top category         : " << topCat << " (" << setprecision(1) << share << "% of spending)\n"
          << setprecision(2)
          << "Average per day      : Rs " << daily << "\n"
          << "Projected month-end  : Rs " << projected << "\n"
          << "Tip                  : " << tip << "\n";
        if (budget.getLimit() > 0 && current) {
            int left = dim - elapsed;
            if (total >= budget.getLimit())
                o << "Savings challenge    : Budget already used up. Aim for zero non-essential spending.\n";
            else if (left > 0)
                o << "Savings challenge    : Keep spending under Rs " << (budget.getLimit() - total) / left
                  << " per day for the remaining " << left << " day(s).\n";
        }
        return o.str();
    }
    void smartInsights(int m, int y) const {
        cout << "\n--- Smart Insights " << setfill('0') << setw(2) << m << "/" << y << setfill(' ') << " ---\n"
             << buildInsights(m, y);
    }
    void exportReport(int m, int y) const {
        double total = 0;
        for (const auto& e : expenses)
            if (e->getDate().getMonth() == m && e->getDate().getYear() == y) total += e->getAmount();
        ostringstream body;
        body << "Month/Year    : " << setfill('0') << setw(2) << m << "/" << y << setfill(' ') << "\n"
             << "Total spent   : Rs " << fixed << setprecision(2) << total << "\n"
             << "Budget status : " << budget.status(total) << "\n\n" << buildInsights(m, y);
        string fname = "Expense_Report_" + to_string(m) + "_" + to_string(y) + ".txt";
        ofstream out(fname);
        if (!out) throw runtime_error("Could not create report file.");
        out << ProjectSignature::banner() << "\n" << body.str()
            << "\nProject Signature : " << ProjectSignature::stamp(body.str()) << "\n"
            << "(Unique code generated from the owner's UID and this report's data)\n";
        cout << "Signed report saved as " << fname << "\n";
    }
    
 
    void save() const {
        ofstream out(fileName);
        if (!out) throw runtime_error("Could not open file for saving.");
        out << "BUDGET|" << budget.getLimit() << "\n";
        for (const auto& e : expenses) out << e->toFileString() << "\n";
    }
 
    void load() {
        ifstream in(fileName);
        if (!in) return;                       
        string line; int loaded = 0;
        while (getline(in, line)) {
            if (line.empty()) continue;
            vector<string> f; string tok; stringstream ss(line);
            while (getline(ss, tok, '|')) f.push_back(tok);
            try {
                if (f[0] == "BUDGET" && f.size() >= 2) { budget.setLimit(stod(f[1])); continue; }
                if (f.size() < 9) continue;
                int id = stoi(f[1]); double amt = stod(f[2]);
                Date d(stoi(f[5]), stoi(f[6]), stoi(f[7]));
                if (f[0] == "REC") add(make_unique<RecurringExpense>(amt, f[3], f[4], d, f[8], id));
                else               add(make_unique<Expense>(amt, f[3], f[4], d, id));
                ++loaded;
            } catch (const exception&) { /* skip corrupted line */ }
        }
        cout << "Loaded " << loaded << " record(s) from " << fileName << ".\n";
    }
};
 
string readLine(const string& prompt) {
    string s;
    do {
        cout << prompt;
        if (!getline(cin, s)) { cout << "\nInput closed. Exiting.\n"; exit(0); }
    } while (s.empty());
    replace(s.begin(), s.end(), '|', '/');     // '|' is our file delimiter
    return s;
}
double readDouble(const string& prompt) {
    while (true) {
        try {
            size_t pos; string s = readLine(prompt);
            double v = stod(s, &pos);
            if (pos != s.size()) throw invalid_argument("");
            return v;
        } catch (...) { cout << "Please enter a valid number.\n"; }
    }
}
double readPositive(const string& prompt) {
    while (true) {
        double v = readDouble(prompt);
        if (v > 0) return v;
        cout << "Amount must be greater than zero.\n";
    }
}
int readInt(const string& prompt) {
    while (true) {
        try {
            size_t pos; string s = readLine(prompt);
            int v = stoi(s, &pos);
            if (pos != s.size()) throw invalid_argument("");
            return v;
        } catch (...) { cout << "Please enter a valid whole number.\n"; }
    }
}
Date readDate() {
    while (true) {
        string s = readLine("Date (DD-MM-YYYY, or T for today): ");
        if (s == "T" || s == "t") return Date();
        int d, m, y; char c1, c2; istringstream is(s);
        if ((is >> d >> c1 >> m >> c2 >> y) && c1 == '-' && c2 == '-' && Date::isValid(d, m, y))
            return Date(d, m, y);
        cout << "Invalid date. Use the format DD-MM-YYYY.\n";
    }
}
string readFrequency() {
    while (true) {
        int c = readInt("Frequency (1-Weekly, 2-Monthly, 3-Yearly): ");
        if (c == 1) return "Weekly";
        if (c == 2) return "Monthly";
        if (c == 3) return "Yearly";
        cout << "Choose 1, 2 or 3.\n";
    }
}
void menu() {
    cout << "\n PERSONAL EXPENSE TRACKER \n"
         << " 1. Add expense\n 2. Add recurring expense\n 3. View all expenses\n"
         << " 4. Delete expense by ID\n 5. Search by category\n 6. Monthly summary\n"
         << " 7. Set monthly budget\n 8. Sort by date\n 9. Sort by amount (high to low)\n"
         << "10. * Smart Insights (unique feature)\n11. * Export Signed Report (unique feature)\n"
         << " 0. Save and exit\n";
}
 
int main() {
    ExpenseTracker tracker("expenses.txt");
    cout << ProjectSignature::banner();
    tracker.load();
 
    while (true) {
        menu();
        int choice = readInt("Enter choice: ");
        try {
            switch (choice) {
            case 1: {
                double a = readPositive("Amount (Rs): ");
                string c = readLine("Category (Food/Travel/Bills...): ");
                string d = readLine("Description: ");
                tracker.add(make_unique<Expense>(a, c, d, readDate()));
                cout << "Expense added.\n"; break;
            }
            case 2: {
                double a = readPositive("Amount (Rs): ");
                string c = readLine("Category: ");
                string d = readLine("Description: ");
                Date dt = readDate();
                tracker.add(make_unique<RecurringExpense>(a, c, d, dt, readFrequency()));
                cout << "Recurring expense added.\n"; break;
            }
            case 3: tracker.viewAll(); break;
            case 4: {
                int id = readInt("Enter ID to delete: ");
                cout << (tracker.remove(id) ? "Deleted.\n" : "No expense with that ID.\n"); break;
            }
            case 5: tracker.searchByCategory(readLine("Category to search: ")); break;
            case 6: {
                int m = readInt("Month (1-12): "), y = readInt("Year (e.g. 2026): ");
                if (m < 1 || m > 12) cout << "Invalid month.\n"; else tracker.monthlySummary(m, y);
                break;
            }
            case 7: tracker.setBudget(readDouble("Monthly budget (Rs): ")); cout << "Budget saved.\n"; break;
            case 8: tracker.sortByDate();   cout << "Sorted by date.\n"; break;
            case 9: tracker.sortByAmount(); cout << "Sorted by amount.\n"; break;
            case 10: case 11: {
                int m = readInt("Month (1-12): "), y = readInt("Year (e.g. 2026): ");
                if (m < 1 || m > 12) { cout << "Invalid month.\n"; break; }
                if (choice == 10) tracker.smartInsights(m, y); else tracker.exportReport(m, y);
                break;
            }
            case 0: tracker.save(); cout << "Data saved. Goodbye!\n"; return 0;
            default: cout << "Invalid choice. Try again.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
}
 
