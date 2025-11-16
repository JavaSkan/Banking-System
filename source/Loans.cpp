#include "../headers/Loans.hpp"

string loanTypeStr(LoanType t){
    switch (t){
        case LoanType::CAR :
            return "car";
            break;
        case LoanType::HOME :
            return "home";
            break;
        case LoanType::STUDENT :
            return "student";
            break;
        case LoanType::BUSINESS:
            return "business";
            break;
    }
    return "";
}

string loanStatusStr(LoanStatus s){
    switch (s){
        case LoanStatus::ACTIVE:
            return "active";
            break;
        case LoanStatus::COMPLETED:
            return "completed";
            break;
        case LoanStatus::OVERDUE:
            return "overdue";
            break;
    }
    return "";
}

void displayLoan(const Loan& l){
    cout << "Loan (" << l.loadId << "):\n";
    cout << "\ttype: " << loanTypeStr(l.type) << "\n";
    cout << "\tprinciple amount: " << l.pr_amount << "\n";
    cout << "\tinterest rate: " << l.it_rate << "\n";
    cout << "\tamount paid: " << l.am_paid << "\n";
    cout << "\tremaining balance: " << l.rm_balance << "\n";
    
    cout << "\tstart date: ";
    displayDate(l.start_date);
    cout << "\n";
    
    cout << "\tend date: ";
    displayDate(l.end_date);
    cout << "\n";

    cout << "\tstatus: " << loanStatusStr(l.status) << "\n";
}