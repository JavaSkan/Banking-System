#include "EmployeeTasks.hpp"
using namespace std;

void addEmployee(Array<Employee>* eArr){
    //na9es controle de saisie (to be added)
    Employee e;
    cout<<"Provide his ID"<<endl;
    cin>>e.ID;
    cout<<"Provide his name"<<endl;
    cin>>e.ID;
    cout<<"Provide his last name"<<endl;
    cin>>e.LastName;
    cout<<"Provide his Adress"<<endl;
    cin>>e.Adress;
    cout<<"Provide his Salary"<<endl;
    cin>>e.Salary;
    cout<<"Year of hiring ?"<<endl;
    cin>>e.HireDate.year;
    cout<<"Month of hiring ?"<<endl;
    cin>>e.HireDate.month;
    cout<<"Day of hiring ?"<<endl;
    cin>>e.HireDate.day;
    //Bank branch should probably be auto added
    cout<<"Provide his bank branch code"<<endl;
    cin>>e.bankBranch;
    //@Aymen_the_interface_guy pls replace this with wtvr u need
    addElement(eArr, e, eArr->size);
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

int modifyEmployee(Employee e){
    char c;
    cout<<"chet7eb tbadel ?"<<endl;
    cout<<"1 : change ID(in case of a misinput)"<<endl;
    cout<<"2 : change name"<<endl;
    cout<<"3 : change last name"<<endl;
    cout<<"4 : change adress"<<endl;
    cout<<"5 : change slary"<<endl;
    cout<<"6 : change branch code"<<endl;
}

