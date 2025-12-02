#ifndef MISCFUNCS_H
#define MISCFUNCS_H
#define TEMPLATE template <typename T>
#include <SinglyLinkedListMeth.hpp>
#include <customer.hpp>
#include <string>
using namespace std;



string unJSON(const string& input);
string path(string togoto) ;
int splitStr(const string& s, char splitter, string out[], int maxParts);
bool createSmallTestFile(const string& filename, const string& str1, const string& str2);
TEMPLATE bool isUnique(const SList<T>& L, int value);
bool isValidEmail(const string& email);
int random(int min, int max);
string trim(string s);
bool isAlpha(string s);
bool checkName(string name);
string replace(string input, string replaced, string replacedWith);
string toLower(string s);
string passwordGen(int size);

#endif //MISCFUNCS_H