#include <windows.h>
#include <webview.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "../include/SinglyLinkedListMeth.hpp"
#include "../include/DoublyLinkedListMeth.hpp"
#include "../include/DataStructsFunctions.hpp"
#include "../include/arrayMeth.hpp"
#include "../include/bankBranch.hpp"


using namespace std;

// --- GLOBAL VARIABLES ---
webview::webview w(true, nullptr);

string lastJsValue;
string Cus_acc_type;
string Cus_name;
Bank globalSessBank; // Store the current bank globally
Date CurrentDate={0,0,0};

// --- UTILITY FUNCTIONS ---

SList<Bank> BranchesList() {
    ifstream file("assets/BankBranches.csv"); 
    SList<Bank> BL = createList<Bank>();
    if(!file.is_open()){
        cerr << "Cannot open file: assets/BankBranches.csv" << endl;
        return BL;
    }
    string line;
    int pos = 1;
    while(getline(file, line)){
        stringstream ss(line);
        Bank data;
        if(!getline(ss, data.branchName, ',') || !getline(ss, data.ID, ',')) continue; 
        insert<Bank>(&BL, data, pos++);
    }
    return BL;
}

//COMMENT FOR SKANDER BELOW

int AddToCsvCustomer(const Customer& Cus){
    ofstream file("assets/Customers.csv",ios::app);
    if (!file.is_open()){
        cerr<<"Cannot open file : assets/"<<endl;
        return -1;
    }
    //Customer contains pointers to a stack/list of transactions/loans respectively,SKANDER convert them to string to put in the csv file
    string line = Cus.ID +","+ Cus.type +","+ Cus.IBAN +","+ Cus.branchCode +","+ Cus.name +","+ to_string(Cus.openingDate.day) +","+ to_string(Cus.openingDate.month) +","+ to_string(Cus.openingDate.year) +","+ to_string(Cus.status) +","+ to_string(Cus.balance) + ",";
    file<<line<<endl;
    return 1;

}
//COMMENT FOR SAKNDER (1)ABOVE AND (1)BELOW

Array<Customer> customerArray() {
    ifstream file("assets/Customers.csv"); 
    Array<Customer> CA = createArray<Customer>(10);
    if(!file.is_open()){
        cerr << "Cannot open file: assets/BankBranches.csv" << endl;
        return CA;
    }
    string line;
    int pos = 0;
    string temp_day;
    string temp_month;
    string temp_year;
    string temp_status;
    string temp_balance;
    while(getline(file, line)){
        stringstream ss(line);
        Customer data;
        //SKANDER please update this line after fixing the conversion part
        if(!getline(ss, data.ID, ',') || !getline(ss, data.type, ',') || !getline(ss, data.IBAN, ',') || !getline(ss, data.branchCode, ',') || !getline(ss, data.name, ',') || !getline(ss, temp_day, ',') || !getline(ss, temp_month, ',') || !getline(ss, temp_year, ',') || !getline(ss, temp_status, ',') || !getline(ss, temp_balance, ',')) continue;
        
    }
    return CA;
}

//COMMENT FOR SKANDER ABOVE



Bank randomBank() {
    SList<Bank> BL = BranchesList();
    int size = listSize<Bank>(BL);
    if(size == 0) {
        Bank dummy; dummy.branchName="Unknown"; dummy.ID="0"; 
        return dummy;
    }
    srand((unsigned int)time(NULL)); 
    int idx = rand() % size + 1;
    return getElement<Bank>(BL, idx);
}

//USUAL FUNCTIONS

//tna7ilek el [] mta3 json
string unJSON(const string& input) {
    string result;
    for(char c : input){
        if(c!='['&&c!='"'&&c!=']'){
            result+=c;
        }
    }
    return result;
}
//tesna3lek absolute path b variable file name ( faza bech nbadel men page l page)

string path(string togoto) {
    char fullPath[MAX_PATH];
    string combined = "gui\\" + togoto;           // concatenate strings properly
    GetFullPathNameA(combined.c_str(), MAX_PATH, fullPath, nullptr); 
    string html_url = "file:///" + string(fullPath);
    return html_url;
}

void splitStr(const string& s, char splitter, string& left, string& right) {
    int pos = s.find(splitter);
    if (pos != string::npos) {
        left = s.substr(0, pos);
        right = s.substr(pos + 1);
    } else {
        left = s;
        right = "";
    }
}

bool createSmallTestFile(const string& filename, const string& str1, const string& str2) {
    ofstream file(filename, ios::out); 
    if (!file.is_open()) {
        cerr << "FAILED to create file: " << filename << endl;
        return false;
    }
    cout << "[C++] SUCCESS: File created at: " << filename << endl;
    file << str1 << "\n" << str2 << "\n";
    file.close();
    return true;
}

// --- WEBVIEW CALLBACK FUNCTIONS ---
TEMPLATE
Array<T> createCustomerArray(){
    Array<Customer> CustArray=createArray<Customer>(0);
    return CustArray;
}
DList Loans;
Stack transactions;
void displayLoans(Loan L){
    //placeholder
}
/*
void displayCusts(Array<Customer> arr){
    int i=0;
    while(i<arr.size){
        cout<<arr.data->balance<<endl;
        cout<<arr.data->branchCode<<endl;
        cout<<arr.data->IBAN<<endl;
        cout<<arr.data->ID<<endl;
        Loan CustLoan=arr.data[i].loans;
        displayLoans(arr.data->loans);
        cout<<arr.data->name<<endl;
        cout<<arr.data<<endl;
    }
}
*/

Array CustArray=createCustomerArray<Customer>();

string getDateJS(const string& dateInfoJSON){
    string dateInfo=unJSON(dateInfoJSON);
    string day;
    string month;
    string year;
    string daymonth;
    splitStr(dateInfo,'&',daymonth,year);
    splitStr(daymonth,'*',day,month);
    int iday=stoi(day);
    int imonth=stoi(month);
    int iyear=stoi(year);
    CurrentDate={iday,imonth,iyear};
    return "\"Date confirmed .\"";
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
    Cus.loans=&Loans;
    Cus.transactions=&transactions;
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

    //displayCusts(CustArray);
    return "\"Customer created .\"";
}
string getRegInfo(const string& msg) {
    cout<<msg;

    return "\"ok\"";
}
string closeWindow(const string&) {
    w.terminate();
    return "\"Closed\"";
}
string goToPageCpp(const string& pageJSON) {
    cout<<endl<<"test";
    string page=unJSON(pageJSON);
    cout<<pageJSON<<" "<<page;
    w.navigate(path(page));
    return "\"page changed\"";
}
string getfromcpp(const string&) {
    return lastJsValue; // valid JSON string
}
/*
void getDate(const string& dateJSON){
    string datestr=unJSON(dateJSON);
    // datestr format "day-month*year"
    string dayMonth;
    string day;
    string month;
    string year;
    splitStr(datestr,'*',dayMonth,year);
    splitStr(dayMonth,'-',day,month);
}
*/

string getInfo(const string&) {
    string sDate=to_string(CurrentDate.day)+'-'+to_string(CurrentDate.month)+'-'+to_string(CurrentDate.year);
    string combined = globalSessBank.branchName + "*" + globalSessBank.ID+'*'+sDate;
    return "{\"data\":\"" + combined + "\"}";
}

// --- SETUP FUNCTIONS ---
void setupBindings() {
    w.bind("closeWindow", closeWindow);
    w.bind("sendDate",getDateJS);
    w.bind("getInfo", getInfo);
    w.bind("getInfo", getRegInfo);
    w.bind("getFromCpp", getfromcpp);
    w.bind("goToPage", goToPageCpp);
    w.bind("sendRegCusInfo",createNewCustomer);
}




void setupWebView() {

    w.set_title("Banking System");
    w.set_size(800, 600, WEBVIEW_HINT_NONE);

    setupBindings();

    w.navigate(path("index.html"));
    
}

// --- MAIN ---
int main() {
    //y7el lconsole
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);

    cout << "[C++] Hello, console!" << endl;

    globalSessBank = randomBank();
    cout << "[C++] Loaded Bank: " << globalSessBank.branchName << " (" << globalSessBank.ID << ")" << endl;

    setupWebView();
   
    w.run();
    return 0;
}
