#include <EmployeeTasks.hpp>
#include <arrayMeth.hpp>
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



int displayEarliest(const Array<Employee>& eArr){
    if(isEmpty(eArr)){
        cout<<"No employees to display"<<endl;
        return 0;
    }
    int earliest = 0;
    int latest = 0;
    for(int i=1; i<eArr.size; i++){
        Date d1 = eArr.data[i].HireDate;
        Date dEarliest = eArr.data[earliest].HireDate;
        Date dLatest = eArr.data[latest].HireDate;
        if( (d1.year < dEarliest.year) || 
            (d1.year == dEarliest.year && d1.month < dEarliest.month) || 
            (d1.year == dEarliest.year && d1.month == dEarliest.month && d1.day < dEarliest.day)){
            earliest = i;
        }
        if( (d1.year > dLatest.year) || 
            (d1.year == dLatest.year && d1.month > dLatest.month) || 
            (d1.year == dLatest.year && d1.month == dLatest.month && d1.day > dLatest.day)){
            latest = i;
        }
    }
    cout<<"Earliest recruited: "<<eArr.data[earliest].ID<<" "<<eArr.data[earliest].Name<<" "<<eArr.data[earliest].LastName
        <<" "<<eArr.data[earliest].HireDate.day<<"/"<<eArr.data[earliest].HireDate.month<<"/"<<eArr.data[earliest].HireDate.year<<endl;
    cout<<"Most recently recruited: "<<eArr.data[latest].ID<<" "<<eArr.data[latest].Name<<" "<<eArr.data[latest].LastName
        <<" "<<eArr.data[latest].HireDate.day<<"/"<<eArr.data[latest].HireDate.month<<"/"<<eArr.data[latest].HireDate.year<<endl;
    return 1;
}


