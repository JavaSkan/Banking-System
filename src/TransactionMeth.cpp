#include <TransactionMeth.hpp>
#include <customer.hpp>

string transactionToString(const Transaction& tr){
    stringstream s;
    s << "TRANSACTION[" << tr.ID << "|";
    s << tr.accountNumber << "|";
    s << tr.type << "|";
    s << tr.amount << "|";
    s << dateToString(tr.date) << "]";
    return s.str();
}

Transaction stringToTransaction(string s){
    //get sub from TRANSACTION[<sub>] and replace '|' with ' '
    //to use stringstream for string to Transaction conversion
    string sub;
    for(int i = 12; i < s.size()-1; i++){
        if(s[i] == '|') sub += ' '; else sub += s[i];
    }
    stringstream ss;
    ss << sub;
    Transaction res;
    ss >> res.ID;
    ss >> res.accountNumber;
    ss >> res.type;
    ss >> res.amount;
    string date_str;
    ss >> date_str;
    res.date = stringToDate(date_str);
    return res;
}

string transTypeToStr(int type){
    return type == TR_WITHDRAWAL ? "withdrawal" : "deposit";
}