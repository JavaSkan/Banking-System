#include "Statistics.hpp"
#include "MiscFuncs.hpp" // For unJSON, splitStr
#include <sstream>

// Access global data from main.cpp
extern Array<Customer> custArray;
extern Array<Employee> EmplArray;

// ==========================================
//            CORE LOGIC
// ==========================================

int getTotalLoans(const Array<Customer>& Cus) {
    int total = 0;
    for (int i = 0; i < Cus.size; i++) {
        total += listSize(Cus.data[i].loans);
    }
    return total;
}

int countLoansByType(const Array<Customer>& Cus, int nCus, int type) {
    int count = 0;
    for (int i = 0; i < nCus; i++) {
        DNode* current = Cus.data[i].loans.head;
        while (current) {
            if (current->data.type == type)
                count++;
            current = current->next;
        }
    }
    return count;
}

int countLoansByStatus(const Array<Customer>& Cus, int nCus, int status) {
    int count = 0;
    for (int i = 0; i < nCus; i++) {
        DNode* current = Cus.data[i].loans.head;
        while (current) {
            if (current->data.status == status)
                count++;
            current = current->next;
        }
    }
    return count;
}

int countActiveLoansInRange(const Array<Customer>& Cus, int nCus, Date startDate, Date endDate) {
    int counter = 0;
    for (int i = 0; i < nCus; i++) {
        DNode* current = Cus.data[i].loans.head;
        while (current) {
            Loan& loan = current->data;
            bool isInRangeStart=compareDates(loan.start_date, startDate) >= 0;
            bool isInRangeEnd=compareDates(loan.start_date, endDate) <= 0;
        
            cout <<endl<<dateToString(startDate)<<"/"<<dateToString(loan.start_date)<<"/"+dateToString(endDate)<<" "<<loan.status<<" "<<isInRangeStart<<"/"<<isInRangeEnd;
            if (loan.status == 5 && 
                compareDates(loan.start_date, startDate) >= 0 &&
                compareDates(loan.start_date, endDate) <= 0) {
                counter++;
            }
            current = current->next;
        }
    }
    return counter;
}

Customer* customerMostLoans(const Array<Customer>& Cus, int nCus) {
    if (nCus == 0) return nullptr;
    Customer* best = &Cus.data[0];
    int maxLoans = listSize(Cus.data[0].loans);

    for (int i = 1; i < nCus; i++) {
        int loanCount = listSize(Cus.data[i].loans);
        if (loanCount > maxLoans) {
            maxLoans = loanCount;
            best = &Cus.data[i];
        }
    }
    return best;
}

Customer* customerHighestBalance(const Array<Customer>& Cus, int nCus) {
    if (nCus == 0) return nullptr;
    Customer* best = &Cus.data[0];
    for (int i = 1; i < nCus; i++) {
        if (Cus.data[i].balance > best->balance)
            best = &Cus.data[i];
    }
    return best;
}

Customer* customerLowestBalance(const Array<Customer>& Cus, int nCus) {
    if (nCus == 0) return nullptr;
    Customer* best = &Cus.data[0];
    for (int i = 1; i < nCus; i++) {
        if (Cus.data[i].balance < best->balance)
            best = &Cus.data[i];
    }
    return best;
}

int totalEmp(const Array<Employee>& Emp) {
    return Emp.size;
}

int countEmpByBranch(const Array<Employee>& Emp, int branchCode) {
    int count = 0;
    for (int i = 0; i < Emp.size; i++) {
        // Assuming bankBranch is stored as string "001", "002" etc.
        try {
            if (stoi(Emp.data[i].bankBranch) == branchCode)
                count++;
        } catch (...) { continue; }
    }
    return count;
}


// ==========================================
//      COMMUNICATION WRAPPERS (For JS)
// ==========================================

// Helper to format a customer as a simple string for the stats view
string formatCustStats(Customer* c) {
    if (!c) return "None";
    return c->name + " (ID: " + c->ID + ")";
}

string sendTotalLoans(const string&) {
    int res = getTotalLoans(custArray);
    return "{\"data\":\"" + to_string(res) + "\"}";
}

string sendLoansByTypeCount(const string& typeJSON) {
    string tStr = unJSON(typeJSON);
    int type = stoi(tStr);
    int res = countLoansByType(custArray, custArray.size, type);
    return "{\"data\":\"" + to_string(res) + "\"}";
}

string sendLoansByStatusCount(const string& statusJSON) {
    string sStr = unJSON(statusJSON);
    int status = stoi(sStr);
    int res = countLoansByStatus(custArray, custArray.size, status);
    return "{\"data\":\"" + to_string(res) + "\"}";
}

string sendActiveLoansInRangeCount(const string& datesJSON) {
    string info = unJSON(datesJSON);
    string parts[2];
    splitStr(info, '*', parts, 2); // Split "StartString*EndString"
    
    Date start = stringToDate(parts[0]);
    Date end = stringToDate(parts[1]);
    
    int res = countActiveLoansInRange(custArray, custArray.size, start, end);
    return "{\"data\":\"" + to_string(res) + "\"}";
}

string sendCustomerMostLoans(const string&) {
    Customer* c = customerMostLoans(custArray, custArray.size);
    return "{\"data\":\"" + formatCustStats(c) + "\"}";
}

string sendCustomerHighestBalance(const string&) {
    Customer* c = customerHighestBalance(custArray, custArray.size);
    return "{\"data\":\"" + formatCustStats(c) + " - " + to_string(c->balance) + " TND\"}";
}

string sendCustomerLowestBalance(const string&) {
    Customer* c = customerLowestBalance(custArray, custArray.size);
    return "{\"data\":\"" + formatCustStats(c) + " - " + to_string(c->balance) + " TND\"}";
}

string sendTotalEmployees(const string&) {
    int res = totalEmp(EmplArray);
    return "{\"data\":\"" + to_string(res) + "\"}";
}

string sendEmpByBranchCount(const string& branchJSON) {
    string bStr = unJSON(branchJSON);
    int branchCode = stoi(bStr);
    int res = countEmpByBranch(EmplArray, branchCode);
    return "{\"data\":\"" + to_string(res) + "\"}";
}