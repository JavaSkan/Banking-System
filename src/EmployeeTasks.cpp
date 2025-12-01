#include <EmployeeTasks.hpp>
#include <MiscFuncs.hpp>
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

int displayAlpha(const Array<Employee>& eArr){
    //making all last names lower case
    Array<Employee> temp = copyArray<Employee>(eArr);
    for (int i = 0; i<temp.size;i++){
        temp.data[i].LastName = toLower(temp.data[i].LastName);
    }
    //sorting (bubble sort)

     for (int i = 0; i < temp.size - 1; i++){
        for (int j = 0; j < temp.size - i - 1; j++){
            if (temp.data[j].LastName > temp.data[j + 1].LastName){
                Employee aux = temp.data[j];
                temp.data[j] = temp.data[j + 1];
                temp.data[j + 1] = aux;
            }
        }
    }
    //clean display 
    for (int i = 0; i < temp.size; i++){
        cout << "ID: " << temp.data[i].ID << endl;
        cout << "Name: " << temp.data[i].Name << endl;
        cout << "Last Name: " << temp.data[i].LastName << endl;
        cout << "Address: " << temp.data[i].Adress << endl;
        cout << "Salary: " << temp.data[i].Salary << endl;
        cout << "Hire Date: "
             << temp.data[i].HireDate.day << "/"
             << temp.data[i].HireDate.month << "/"
             << temp.data[i].HireDate.year << endl;
        cout << "Bank Branch: " << temp.data[i].bankBranch << endl;
        cout << "------------------------" << endl;
    }
    return 1;


}

