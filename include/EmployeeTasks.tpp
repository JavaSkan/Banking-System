#include <EmployeeTasks.hpp>
#include <arrayMeth.hpp>
#include <MiscFuncs.hpp>
#include <Branches.hpp>
#include <Dates.hpp>
#include <fstream>

using namespace std;
Array EmplArray=createEmployeeArray<Employee>();

TEMPLATE
Array<T> createEmployeeArray(){
    Array<Employee> EmplArray=createArray<Employee>(1); // initial value must be != 0
    return EmplArray;
}
int init_employeeArray(Array<Employee>& EmplArray){
    ifstream file("assets/Employees.csv"); 
    if(!file.is_open()){
        cerr << "Cannot open file: assets/Employees.csv" << endl;
        return 0;
    }
    stringstream buf;
    string line;
    string temp;
    Employee e;
    string value = "";
    while(getline(file, line)){
        buf << line;
        cout<<line<<endl;
        getline(buf, e.ID, ',');
        getline(buf, e.Name, ',');
        getline(buf, e.LastName, ',');
        getline(buf, e.Adress, ',');
        getline(buf, temp, ',');e.Salary=stof(temp);
        getline(buf, temp, ',');e.HireDate = stringToDate(value);
        getline(buf, e.bankBranch, ',');
        getline(buf, e.password, ',');
        addElement(&EmplArray, e, EmplArray.size);
    }
    file.close();
    return 1;
}

string addEmployee(const string& infoJSON){
    //na9es controle de saisie (to be added)
    string EmplInfo=unJSON(infoJSON);
    string infoPart[7];
    splitStr(EmplInfo,'*',infoPart,7);
    //array format is [ID*name*lastName*Adress*Salary]
    Employee e;
    e.ID=infoPart[0];
    e.Name=infoPart[1];
    e.LastName=infoPart[2];
    e.Adress=infoPart[3];
    e.Salary=stof(infoPart[4]);
    e.HireDate=CurrentDate;
    e.bankBranch=globalSessBank.ID;
    e.password=passwordGen(12);
    addEmployeeToCsv(e);
    addElement(&EmplArray,e,EmplArray.size);
    return "\"Employee Added\"";
}

int deleteEmployee(Array<Employee>* eArr){
    string ID;
    cout<<"What is the employee´s ID ?"<<endl;
    cin>>ID;
    int pos = searchByID(*eArr, ID);
    if (pos == -1){
        cout<<"Employee not found please verify the ID"<<endl;
        return 0;
    }
    removeAtArray(eArr,pos);
    return 1;
}

int modifyEmployee(Employee& e){
    char c;
    cout<<"chet7eb tbadel ?"<<endl;
    cout<<"1 : change ID(in case of a misinput)"<<endl;
    cout<<"2 : change name"<<endl;
    cout<<"3 : change last name"<<endl;
    cout<<"4 : change adress"<<endl;
    cout<<"5 : change salary"<<endl;
    cout<<"6 : change branch code"<<endl;
    cin>>c;
    switch (c){
        case '1' :
            cout<<"What´s the new value ?"<<endl;
            cin>>e.ID;
            break;
        case '2' :
            cout<<"What´s the new value ?"<<endl;
            cin>>e.Name;
            break;
        case '3' :
            cout<<"What´s the new value ?"<<endl;
            cin>>e.LastName;
            break;
        case '4' :
            cout<<"What´s the new value ?"<<endl;
            cin>>e.Adress;
            break;
        case '5' :
            cout<<"What´s the new value ?"<<endl;
            cin>>e.Salary;
            break;
        case '6' :
            cout<<"What´s the new value ?"<<endl;
            cin>>e.bankBranch;
            break;
    }
    return 1;
}

//int displayAlpha(const Array<Employee>& eArr){
    
//}

int displayAlpha(const Array<Employee>& eArr){
    if(isEmpty(eArr)){
    cout<<"No employees to display"<<endl;
    return 0;
}
    Array<Employee> temp = copyArray(eArr);
    for(int i=0; i<temp.size-1; i++){
    for(int j=i+1; j<temp.size; j++){
    if(temp.data[i].LastName > temp.data[j].LastName){
    Employee swap = temp.data[i];
    temp.data[i] = temp.data[j];
    temp.data[j] = swap;
}
}}
    for(int i=0; i<temp.size; i++){
    cout<<temp.data[i].ID<<" "<<temp.data[i].Name<<" "<<temp.data[i].LastName<<" "
    <<temp.data[i].Adress<<" "<<temp.data[i].Salary<<" "
    <<temp.data[i].HireDate.day<<"/"<<temp.data[i].HireDate.month<<"/"<<temp.data[i].HireDate.year
    <<" Branch:"<<temp.data[i].bankBranch<<endl;
}
    return 1;
}



int displayEarliest(const Array<Employee>& eArr) {
    if (isEmpty(eArr)) {
        cout << "No employees to display" << endl;
        return 0;
    }

    int earliest = 0;
    for (int i = 1; i < eArr.size; i++) {
        Date d1 = eArr.data[i].HireDate;
        Date dE = eArr.data[earliest].HireDate;

        if ((d1.year < dE.year) ||
            (d1.year == dE.year && d1.month < dE.month) ||
            (d1.year == dE.year && d1.month == dE.month && d1.day < dE.day)) 
        {
            earliest = i;
        }
    }

    cout << "Earliest recruited: "
         << eArr.data[earliest].ID << " "
         << eArr.data[earliest].Name << " "
         << eArr.data[earliest].LastName << " "
         << eArr.data[earliest].HireDate.day << "/"
         << eArr.data[earliest].HireDate.month << "/"
         << eArr.data[earliest].HireDate.year << endl;

    return 1;
}


int displayMostRecently(const Array<Employee>& eArr) {
    if (isEmpty(eArr)) {
        cout << "No employees to display" << endl;
        return 0;
    }

    int latest = 0;
    for (int i = 1; i < eArr.size; i++) {
        Date d1 = eArr.data[i].HireDate;
        Date dL = eArr.data[latest].HireDate;

        if ((d1.year > dL.year) ||
            (d1.year == dL.year && d1.month > dL.month) ||
            (d1.year == dL.year && d1.month == dL.month && d1.day > dL.day)) 
        {
            latest = i;
        }
    }

    cout << "Most recently recruited: "
         << eArr.data[latest].ID << " "
         << eArr.data[latest].Name << " "
         << eArr.data[latest].LastName << " "
         << eArr.data[latest].HireDate.day << "/"
         << eArr.data[latest].HireDate.month << "/"
         << eArr.data[latest].HireDate.year << endl;

    return 1;
}





int addEmployeeToCsv(const Employee& e){
    ofstream file("assets/Employees.csv",ios::app);
    if (!file.is_open()){
        cerr << "Cannot open file : assets/Employees.csv" << endl;
        file.close();
        return -1;
    }else{
        string line =
        e.ID+","+
        e.Name+","+
        e.LastName+","+
        e.Adress+","+
        to_string(e.Salary)+","+
        dateToString(e.HireDate)   +","+
        e.bankBranch+","+
        e.password+",";
        file << line << endl;
        file.close();
        return 1;
    }
}


int addCustomer(Array<Customer>* cArr){
    Customer c;
    cout<<"Provide account number (ID)"<<endl;
    cin>>c.ID;
    cout<<"Provide account type"<<endl;
    cin>>c.type;
    cout<<"Provide IBAN"<<endl;
    cin>>c.IBAN;
    cout<<"Provide branch code"<<endl;
    cin>>c.branchCode;
    cout<<"Provide account holder name"<<endl;
    cin>>c.name;
    cout<<"Provide opening date (year month day)"<<endl;
    cin>>c.openingDate.year>>c.openingDate.month>>c.openingDate.day;
    cout<<"Provide status (0 = inactive, 1 = active, -1 = closed)"<<endl;
    cin>>c.status;
    cout<<"Provide balance"<<endl;
    cin>>c.balance;
    cout<<"Set password"<<endl;
    cin>>c.password;
    addElement(cArr,c,cArr->size);
    return 1;
}

int displayAccounts(const Array<Customer>& cArr){
    if(isEmpty(cArr)){
        cout<<"No accounts to display"<<endl;
        return 0;
    }
    for(int i=0;i<cArr.size;i++){
        cout<<cArr.data[i].ID<<" "<<cArr.data[i].name<<" "<<cArr.data[i].type
            <<" IBAN:"<<cArr.data[i].IBAN<<" Branch:"<<cArr.data[i].branchCode
            <<" Status:"<<cArr.data[i].status<<" Balance:"<<cArr.data[i].balance
            <<" Opened:"<<cArr.data[i].openingDate.day<<"/"<<cArr.data[i].openingDate.month<<"/"<<cArr.data[i].openingDate.year
            <<endl;
    }
    return 1;
}

int changeStatus(Customer* c){
    int newStatus;
    cout<<"Enter new status (0 = inactive, 1 = active, -1 = closed)"<<endl;
    cin>>newStatus;
    c->status = newStatus;
    return 1;
}

int deleteCustomer(Array<Customer>* cArr, Customer c){
    int pos = searchByID(*cArr,c.ID);
    if(pos==-1){
        cout<<"Customer not found"<<endl;
        return 0;
    }
    removeAtArray(cArr,pos);
    return 1;
}

/*Loan selectedLoan;
DList Dl;
SList Sl;
Array customerArray;
string changeStatusLoan(const string& infoJSON){
    int temp =stoi(unJSON(infoJSON));
    selectedLoan.status = temp;
    return "\"Status changed\"";
    
}
    */
/*
string deleteLoan(const string& infoJSON){
    //info JSON should contain : selectedLoan´s ID, a selected customer´s ID
    //and a singly linked for archived loans => has 2 members 
    //for now info´s size is set to 4 for each element
    string temp = unJSON(infoJSON);
    string info[4];
    int n = splitStr(temp,'*',info,4);
    
    

}
*/