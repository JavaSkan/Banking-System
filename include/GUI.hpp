#ifndef GUI_H
#define GUI_H
#include <string>
#include <webview.h>
using namespace std;

extern webview::webview w;


string getRegInfo(const string& msg) ;
string closeWindow(const string&) ;
string goToPageCpp(const string& pageJSON) ;
void setupBindings() ;
void setupWebView();
void runGUI();


#endif