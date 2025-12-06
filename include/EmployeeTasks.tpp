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
    while(getline(file, line)){
        buf << line;
        cout<<line<<endl;
        getline(buf, e.ID, ',');
        getline(buf, e.Name, ',');
        getline(buf, e.LastName, ',');
        getline(buf, e.Adress, ',');
        getline(buf, temp, ',');e.Salary=stof(temp);
        getline(buf, temp, ',');e.HireDate = stringToDate(temp);
        getline(buf, e.bankBranch, ',');
        getline(buf, e.password, ',');
        addElement(&EmplArray, e, EmplArray.size);
    }
    file.close();
    return 1;
}
string IDGenEmployee(){
    bool test=false;
    string ID="0";
    while(!test){
        for(int i=0;i<6;i++){
            ID+= to_string(random(0,9));
        }
        test=searchByID(EmplArray,"E"+ID)==-1;
    }
    return "E"+ID;
}

string addEmployee(const string& infoJSON){
    //na9es controle de saisie (to be added)
    string EmplInfo=unJSON(infoJSON);
    string infoPart[4];
    splitStr(EmplInfo,'*',infoPart,4);
    //array format is [name*lastName*Adress*Salary]
    Employee e;
    e.ID=IDGenEmployee();
    e.Name=infoPart[0];
    e.LastName=infoPart[1];
    e.Adress=infoPart[2];
    e.Salary=stof(infoPart[3]);
    e.HireDate=CurrentDate;
    e.bankBranch=globalSessBank.ID;
    e.password=passwordGen(12);
    addEmployeeToCsv(e);
    addElement(&EmplArray,e,EmplArray.size);
    return "\"Employee Added\"";
}
int updateEmployeeInCsv(const Employee& Emp) {
    std::ifstream file("assets/Employees.csv");
    if (!file.is_open()) return -1;

    std::ofstream temp("assets/Employees.tmp");
    if (!temp.is_open()) {
        file.close();
        return -1;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string id;

        getline(ss, id, ',');

        if (id == Emp.ID) {
            line =
                Emp.ID + "," +
                Emp.Name + "," +
                Emp.LastName + "," +
                Emp.Adress + "," +
                std::to_string(Emp.Salary) + "," +
                dateToString(Emp.HireDate) + "," +
                Emp.bankBranch + "," +
                Emp.password+",";
        }

        temp << line << "\n";
    }

    file.close();
    temp.close();

    if (std::remove("assets/Employees.csv") != 0) return -1;
    if (std::rename("assets/Employees.tmp", "assets/Employees.csv") != 0) return -1;

    return 1;
}

int deleteEmployeeFromCsv(const Employee& Emp) {
    std::ifstream file("assets/Employees.csv");
    if (!file.is_open()) return -1;

    std::ofstream temp("assets/Employees.tmp");
    if (!temp.is_open()) {
        file.close();
        return -1;
    }
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string id;
        getline(ss, id, ',');

        if (id == Emp.ID) {
            continue;
        }
        temp << line << "\n";
    }

    file.close();
    temp.close();

    if (std::remove("assets/Employees.csv") != 0) return -1;
    if (std::rename("assets/Employees.tmp", "assets/Employees.csv") != 0) return -1;

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



Employee earliestEmployee() {
    
    int earliest = 0;
    for (int i = 1; i < EmplArray.size; i++) {
        Date d1 = EmplArray.data[i].HireDate;
        Date dE = EmplArray.data[earliest].HireDate;

        if ((d1.year < dE.year) ||
            (d1.year == dE.year && d1.month < dE.month) ||
            (d1.year == dE.year && d1.month == dE.month && d1.day < dE.day)) 
        {
            earliest = i;
        }
    }

    return EmplArray.data[earliest];
}


Employee latestEmployee() {
    if (isEmpty(EmplArray)) {
        cout << "No employees to display" << endl;
        return {};
    }

    int latest = 0;
    for (int i = 1; i < EmplArray.size; i++) {
        Date d1 = EmplArray.data[i].HireDate;
        Date dL = EmplArray.data[latest].HireDate;

        if ((d1.year > dL.year) ||
            (d1.year == dL.year && d1.month > dL.month) ||
            (d1.year == dL.year && d1.month == dL.month && d1.day > dL.day)) 
        {
            latest = i;
        }
    }

    return EmplArray.data[latest];
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

string changeStatus(const string& infoJSON){
    string info=unJSON(infoJSON);
    string parts[2];
    splitStr(info,'*',parts,2);
    string id=parts[0];
    int newStatus=stoi(parts[1]);
    cout<<endl<<id<<endl<<newStatus;
    int pos=searchByID(custArray,id);
    Customer Cus=custArray.data[pos];
    custArray.data[pos].status=newStatus; // to change the actual value in the array
    Cus.status=newStatus; //changes the local value to be able to reconstruct the CSV line , faza faza , nheb nor9od
    updateCustomerInCsv(Cus);
    return "\"true\"";
}
/*
int deleteCustomer(Array<Customer>* cArr, Customer c){
    int pos = searchByID(*cArr,c.ID);
    if(pos==-1){
        cout<<"Customer not found"<<endl;
        return 0;
    }
    removeAtArray(cArr,pos);
    return 1;
}
*/



string deleteCompletedLoans(const string&){
    for (int i = 0; i<custArray.size;i++){
        DNode* currentLoan = custArray.data[i].loans.head;
        while (currentLoan != nullptr){
            if (currentLoan->data.status == LNS_COMPLETED)
            {
                if(!insert(&completed_loans,currentLoan->data, completed_loans.size + 1)){
                    cerr << "[deleteCompletedLoans]: Failed too insert completed loan\n";
                }
                removeAt(&custArray.data[i].loans,searchByID(custArray.data[i].loans,currentLoan->data.ID));
                updateCustomerInCsv(custArray.data[i]);
                updateCompletedLoansCsv(completed_loans);
            }
            currentLoan = currentLoan->next;
        }
    }
    return "\"Completed loans have been deleted\"";
}

string finilize(const string&){
    for (int i = 0; i<custArray.size;i++){
        custArray.data[i].rolledback = 0;
        int nb = custArray.data[i].transactions.top;
        for (int j = 0; j<nb;j++){
            Transaction t = pop(custArray.data[i].transactions);
            insert(&finalized_transactions,t,finalized_transactions.size+1);
        }
    }
    nextDay();
    
    return "\"Day is finalized\"";
}



string employeeToStr(const Employee& Emp) {
    stringstream ss;

    ss << Emp.ID << "*"
    << Emp.Name << "*"
    << Emp.LastName << "*"
       << Emp.Adress << "*"
       << to_string(Emp.Salary).substr(0, to_string(Emp.Salary).find('.') + 4) << "*"
       << dateToString(Emp.HireDate) << "*"
       << Emp.bankBranch << "*"
       << Emp.password;
    return ss.str();
}


