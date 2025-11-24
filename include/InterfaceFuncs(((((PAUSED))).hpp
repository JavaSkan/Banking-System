/*#ifndef INTERFACEFUNCS_H
#define INTERFACEFUNCS_H
#include "../include/SinglyLinkedListMeth.hpp"
#include "../include/DataStructsFunctions.hpp"
#include "../include/bankBranch.hpp"
#include <iostream>
using namespace std;

#define TEMPLATE template <typename T>

TEMPLATE SList<Bank> BranchesList() ;
TEMPLATE Bank randomBank() ;
string unJSON(const string& input) ;
string path(string togoto) ;
void splitStr(const string& s, char splitter, string& left, string& right) ;
bool createSmallTestFile(const string& filename, const string& str1, const string& str2) ;
string sendtocpp(const string& msg) ;
string closeWindow(const string&) ;
string goToPageCpp(const string& pageJSON) ;
string getfromcpp(const string&) ;
string getBranchInfo(const string&) ;
void setupBindings() ;
void setupWebView() ;


#include "InterfaceFuncs.tpp"

#endif
*/