#include <iostream>
#include <fstream>
#include <string>

#include <SinglyLinkedListMeth.hpp>
#include <DoublyLinkedListMeth.hpp>
#include <arrayMeth.hpp>
#include <Branches.hpp>
#include <Dates.hpp>
#include <MiscFuncs.hpp>
#include <customerMeth.hpp>
#include <LoansMeth.hpp>
#include <EmployeeTasks.hpp>
#include <stackMeth.hpp>
#define TEMPLATE template <typename T>

using namespace std;

string IDGenCustomer(){
    // THIS DOESNT CHECK FOR UNIQUE , TO FIX LATER
    bool test=false;
    string ID="1";
    for(int i=0;i<12;i++){
        ID+= to_string(random(0,9));
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

string passwordGen(int size){
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&()-_=+[]{}|;:.<>/?";
    string password;
    for(int i=0;i<size;i++){
        password+=chars[random(0,chars.size())];
    }
    return password;
}

int addCustomerToCsv(const Customer& Cus){
    ofstream file("assets/Customers.csv",ios::app);
    if (!file.is_open()){
        cerr << "Cannot open file : assets/Customers.csv" << endl;
        file.close();
        return -1;
    }
    //Customer contains pointers to a stack/list of transactions/loans respectively,SKANDER convert them to string to put in the csv file
    string line =
    Cus.ID                          +","+
    Cus.type                        +","+
    Cus.IBAN                        +","+
    Cus.branchCode                  +","+
    Cus.name                        +","+
    dateToString(Cus.openingDate)   +","+
    to_string(Cus.status)           +","+
    to_string(Cus.balance)          +","+
    DLToString(Cus.loans)           +","+
    stackToString(Cus.transactions) +","+
    Cus.password;
    cout << line << endl; //For debugging purposes
    file << line << endl;
    file.close();
    return 1;

}

int init_customerArray(Array<Customer>& Cusarr) {
    ifstream file("assets/Customers.csv"); 
    if(!file.is_open()){
        cerr << "Cannot open file: assets/Customers.csv" << endl;
        return 0;
    }
    stringstream buf;
    string line;
    string value;
    Customer c;
    while(getline(file, line)){
        buf << line;
        getline(buf, c.ID, ',');
        getline(buf, c.type, ',');
        getline(buf, c.IBAN, ',');
        getline(buf, c.branchCode, ',');
        getline(buf, c.name, ',');
        getline(buf, value, ',');
        c.openingDate = stringToDate(value);
        getline(buf, value, ',');
        c.status = stoi(value);
        getline(buf, value, ',');
        c.balance = stof(value);
        getline(buf, value, ',');
        c.loans = stringToDL(value);
        getline(buf, value, ',');
        c.transactions = stringToStack(value);
        getline(buf, value, ',');
        c.password = value;
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
    splitStr(info,'*',acc_type,name);
    Customer Cus;
    Cus.type=acc_type;
    Cus.branchCode=globalSessBank.ID;
    Cus.ID=IDGenCustomer();
    Cus.IBAN=IBANGen(Cus);
    Cus.name=name;
    Cus.openingDate=CurrentDate;
    Cus.status=1;
    Cus.balance=0;
    DList Loans=createList();
    Stack Transactions=createStack();
    Cus.loans=Loans;
    Cus.transactions=Transactions; 
    Cus.password=passwordGen(12);
    addCustomerToCsv(Cus);
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
    cout<<"balance : "<<Cus.password<<endl;

    //displayCusts(CustArray);
    return "\"Customer created .\"";

}
