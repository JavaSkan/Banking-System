#include "../headers/Loans.hpp"

string loanTypeStr(int t){
    switch (t){
        case LNT_CAR :
            return "car";
            break;
        case LNT_HOME :
            return "home";
            break;
        case LNT_STUDENT :
            return "student";
            break;
        case LNT_BUSINESS:
            return "business";
            break;
    }
    return "";
}

string loanStatusStr(int s){
    switch (s){
        case LNS_ACTIVE:
            return "active";
            break;
        case LNS_COMPLETED:
            return "completed";
            break;
        case LNS_OVERDUE:
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