#ifndef BRANCHES_H
#define BRANCHES_H
#include <string>
#include <iostream>
using namespace std;

struct Bank{
    string branchName;
    string ID;
};
extern Bank globalSessBank; // Store the current bank globally



Bank randomBank();
SList<Bank> BranchesList();


#endif //BRANCHES_H