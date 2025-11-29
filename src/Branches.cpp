#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>

#include <SinglyLinkedListMeth.hpp>
#include <Dates.hpp>
#include <Branches.hpp>
#include <MiscFuncs.hpp>
#include <iostream>
using namespace std;

Bank globalSessBank; // Store the current bank globally


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
SList<Bank> BranchesList() {
    ifstream file("assets/BankBranches.csv"); 
    SList<Bank> BL = createList<Bank>();
    if(!file.is_open()){
        cerr << "Cannot open file: assets/BankBranches.csv" << endl;
        file.close();
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
    file.close();
    return BL;
}