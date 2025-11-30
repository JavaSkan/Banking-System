#include <LoansMeth.hpp>

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
    cout << "Loan (" << l.ID << "):\n";
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

string loanToString(const Loan& ln){
    stringstream out;
    out << "LOAN[";
    out << ln.ID << "*"
        << ln.type << "*"
        << ln.status << "*"
        << ln.pr_amount << "*"
        << ln.it_rate << "*"
        << ln.am_paid << "*"
        << ln.rm_balance << "*"
        << dateToString(ln.start_date) << "*"
        << dateToString(ln.end_date)
        << "]";
    return out.str();
}

Loan stringToLoan(string s){
    Loan res;
    string sub = "";
    for(int i = 5; i < s.size()-1; i++){
        if(s[i] == '*') sub += ' '; else sub += s[i];
    }
    if(sub == "") return {};
    stringstream ss;
    ss << sub;
    ss >> res.ID >> res.type >> res.status >> res.pr_amount >> res.it_rate >> res.am_paid >> res.rm_balance;
    string buf;
    ss >> buf;
    res.start_date = stringToDate(buf);
    ss >> buf;
    res.end_date = stringToDate(buf);
    return res;
}