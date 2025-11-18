#include "../headers/SinglyLinkedListMeth.hpp"
#include "../headers/CustomerInterface.hpp"
#include "../headers/EmployeeInterface.hpp"
#include <iostream>
#include <string>
using namespace std;

//TESTING STUFF I HATE GITHUB
//WHY NO WORK

int main() {
    bool reloop;
    string input;
    cout<<"----------------------------------------------------------------------------"<<endl;
    cout << "  ____              _    _               ____            _                  \n"
    " | __ )  __ _ _ __ | | _(_)_ __   __ _  / ___| _   _ ___| |_ ___ _ __ ___  \n"
    " |  _ \\ / _` | '_ \\| |/ / | '_ \\ / _` | \\___ \\| | | / __| __/ _ \\ '_ ` _ \\ \n"
    " | |_) | (_| | | | |   <| | | | | (_| |  ___) | |_| \\__ \\ ||  __/ | | | | |\n"
    " |____/ \\__,_|_| |_|_|\\_\\_|_| |_|\\__, | |____/ \\__, |___/\\__\\___|_| |_| |_| \n"
    "                                 |___/         |___/                        \n"<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;
    cout << "___  _    ____ ____ ____ ____    ____ _  _ ____ ____ ____ ____    ____ _  _ ____     \n"
        "|__] |    |___ |__| [__  |___    |    |__| |  | |  | [__  |___    |  | |\\ | |___    .\n"
        "|    |___ |___ |  | ___] |___    |___ |  | |__| |__| ___] |___    |__| | \\| |___    .\n"
        "                                                                                      \n"<<endl;
    cout<<"1-Customer Interface\n\n2-Employee Interface\n\n3-Exit\n\n";
    do{
        cout<<"Please give your choice : ";
        getline(cin,input);
        if(input!="1"&&input!="2"&&input!="3"){
            reloop=true;
        }else reloop=false;
    } while (reloop); 
    if (input=="1"){
         customerInterface();
        }
    else if (input=="2"){
            employeeInterface();
        }
    else if (input=="3"){
        return 0;
    }
    return 0;
}

        
