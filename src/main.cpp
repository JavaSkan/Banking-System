#include "../include/SinglyLinkedListMeth.hpp"
#include "../include/CustomerInterface.hpp"
#include "../include/EmployeeInterface.hpp"

#include <iostream>
#include <string>
using namespace std;


int kahlouch(){
    bool reloop;
    string input;
    
    cout << "----------------------------------------------------------------------------\n";
    cout <<
    "  ____              _    _               ____            _                  \n"
    " | __ )  __ _ _ __ | | _(_)_ __   __ _  / ___| _   _ ___| |_ ___ _ __ ___  \n"
    " |  _ \\ / _` | '_ \\| |/ / | '_ \\ / _` | \\___ \\| | | / __| __/ _ \\ '_ ` _ \\ \n"
    " | |_) | (_| | | | |   <| | | | | (_| |  ___) | |_| \\__ \\ ||  __/ | | | | |\n"
    " |____/ \\__,_|_| |_|_|\\_\\_|_| |_|\\__, | |____/ \\__, |___/\\__\\___|_| |_| |_| \n"
    "                                 |___/         |___/                        \n";
    cout << "----------------------------------------------------------------------------\n";
    cout <<
    "___  _    ____ ____ ____ ____    ____ _  _ ____ ____ ____ ____    ____ _  _ ____     \n"
    "|__] |    |___ |__| [__  |___    |    |__| |  | |  | [__  |___    |  | |\\ | |___    .\n"
    "|    |___ |___ |  | ___] |___    |___ |  | |__| |__| ___] |___    |__| | \\| |___    .\n\n";
    
    cout << "1-Customer Interface\n2-Employee Interface\n3-Exit\n";
    do {
        cout << "Please give your choice: ";
        getline(cin, input);
        reloop = !(input == "1" || input == "2" || input == "3");
    } while (reloop);
    
    if (input == "1") {
        customerInterface();
    } else if (input == "2") {
        employeeInterface();
    }
    
    return 0;
}
