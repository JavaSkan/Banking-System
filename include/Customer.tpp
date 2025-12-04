#include <iostream>
#include <fstream>
#include <string>

#include <customerMeth.hpp>
#include <SinglyLinkedListMeth.hpp>
#include <DoublyLinkedListMeth.hpp>
#include <arrayMeth.hpp>
#include <Branches.hpp>
#include <Dates.hpp>
#include <MiscFuncs.hpp>
#include <LoansMeth.hpp>
#include <stackMeth.hpp>
#define TEMPLATE template <typename T>
using namespace std;
Array custArray=createCustomerArray<Customer>();

string IDGenCustomer(){
    bool test=false;
    string ID="1";
    while(!test){
        for(int i=0;i<12;i++){
            ID+= to_string(random(0,9));
        }
        test=searchByID(custArray,ID)==-1;
    }
    return ID;
}

string RIBGen(const Customer& Cus){
    string RIB = "67"+Cus.branchCode+Cus.ID;
    long long temp = stoll(RIB);
    int key=(97 - (temp%97));
    string skey=to_string(key);
    if(key<10){
        string skey="0"+skey;
    }
    RIB = RIB + skey;
    return(RIB);
}

string IBANGen(const Customer& Cus){
    string IBAN = "TN59" + RIBGen(Cus);
    return(IBAN);
}


int addCustomerToCsv(const Customer& Cus){
    ofstream file("assets/Customers.csv",ios::app);
    if (!file.is_open()){
        cerr << "Cannot open file : assets/Customers.csv" << endl;
        file.close();
        return -1;
    }
    //Customer contains pointers to a stack/list of transactions/loans respectively,SKANDER convert them to string to put in the csv file
    string line =customerToCsvLine(Cus);
    file << line << endl;
    file.close();
    return 1;
}
#include <fstream>
#include <sstream>
#include <string>

int updateCustomerInCsv(const Customer& Cus) {
    std::ifstream file("assets/Customers.csv");
    if (!file.is_open()) return -1;

    std::ofstream temp("assets/Customers.tmp");
    if (!temp.is_open()) {
        file.close();
        return -1;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string id;
        getline(ss, id, ',');  // first field is customer ID

        if (id == Cus.ID) {
            // Replace line for this customer
            line = customerToCsvLine(Cus);
        }

        temp << line << "\n";
    }

    file.close();
    temp.close();

    // Replace original file with temporary file
    if (std::remove("assets/Customers.csv") != 0) return -1;
    if (std::rename("assets/Customers.tmp", "assets/Customers.csv") != 0) return -1;

    return 1;
}
#include <sstream>
#include <string>

std::string customerToCsvLine(const Customer& Cus) {
    std::stringstream ss;

    ss << Cus.ID << ","
       << Cus.type << ","
       << Cus.IBAN << ","
       << Cus.branchCode << ","
       << Cus.name << ","
       << dateToString(Cus.openingDate) << ","
       << Cus.status << ","
       << std::to_string(Cus.balance).substr(0, std::to_string(Cus.balance).find('.') + 4) << ","
       << DLToString(Cus.loans) << ","
       << stackToString(Cus.transactions) << ","
       << Cus.password;

    return ss.str();
}



int init_customerArray(Array<Customer>& Cusarr) {
    ifstream file("assets/Customers.csv"); 
    if(!file.is_open()){
        cerr << "Cannot open file: assets/Customers.csv" << endl;
        return 0;
    }
    stringstream buf;
    string line;
    Customer c;
    string value = "";
    while(getline(file, line)){
        buf << line;
        cout<<line<<endl;
        getline(buf, c.ID, ',');
        getline(buf, c.type, ',');
        getline(buf, c.IBAN, ',');
        getline(buf, c.branchCode, ',');
        getline(buf, c.name, ',');
        getline(buf, value, ',');c.openingDate = stringToDate(value);
        getline(buf, value, ',');c.status = stoi(value);
        getline(buf, value, ',');c.balance = stof(value);
        getline(buf, value, ',');c.loans =stringToDL(value);
        getline(buf, value, ',');c.transactions = stringToStack(value);
        getline(buf, c.password, ',');
        addElement(&Cusarr, c, Cusarr.size);
    }
    file.close();
    return 1;
}

TEMPLATE
bool isUnique(const SList<T>& L, string value) {
    SNode<T>* current = L.head;
    while (current != nullptr) {
        if (current->data.ID == value) {
            return false;
        }
        current = current->next;
    }
    return true; 
}

TEMPLATE
Array<T> createCustomerArray(){
    Array<Customer> CustArray=createArray<Customer>(1); // initial value must be != 0
    return CustArray;
}

string createNewCustomer(const string& infoJSON){
    string info=unJSON(infoJSON);
    string acc_type;
    string name;
    string infoParts[2];
    int n = splitStr(info, '*',infoParts,2);
// Now parts[0..n-1] contain the substrings.

    Customer Cus;
    Cus.type=acc_type=infoParts[0];
    Cus.branchCode=globalSessBank.ID;
    Cus.ID=IDGenCustomer();
    Cus.IBAN=IBANGen(Cus);
    Cus.name=name=infoParts[1];
    Cus.openingDate=CurrentDate;
    Cus.status=1;
    Cus.balance=0;
    DList Loans=createList();
    Stack Transactions=createStack();
    Cus.loans=Loans;
    Cus.transactions=Transactions; 
    Cus.password=passwordGen(12);
    addCustomerToCsv(Cus);
    addElement<Customer>(&custArray,Cus,custArray.size);
    
    //addElement(CustArray,Cus,CustArray.size);
    cout<<endl;
    cout<<"ID : "<<Cus.ID<<endl;
    cout<<"type : "<<Cus.type<<endl;
    cout<<"IBAN : "<<Cus.IBAN<<"("<<Cus.IBAN.size()<<")"<<endl;
    cout<<"branch code : "<<Cus.branchCode<<endl;
    cout<<"name : "<<Cus.name<<endl;
    cout<<"opening date : "<<Cus.openingDate.day<<"-"<<Cus.openingDate.month<<"-"<<Cus.openingDate.year<<endl;
    cout<<"status : "<<Cus.status<<endl;
    cout<<"balance : "<<Cus.balance<<endl;
    cout<<"password : "<<Cus.password<<endl;

    //displayCusts(CustArray);
    return "\"Customer created .\"";

}
