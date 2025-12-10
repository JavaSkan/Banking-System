
# **Banking System Project – Report**

## **Project Overview**

**General Work Structure**

* **Frontend:** HTML5, CSS3, JavaScript
* **Backend:** C++
* **Bridge:** Microsoft WebView2
* **Architecture:** Desktop application rendered via WebView2

## **Directory Tree**

<div style="padding;">

```
C:.
├────────────────────────────────────────────────────────────────┐
│   .gitignore       BankingSystem.exe      WebView2Loader.dll   │
│   compile.bat      IMPORTANT.txt          WORKLOG.md           │
│   compiletest.bat  README.md              REPORT.md            │
└────────────────────────────────────────────────────────────────┘

.vs/
.vscode/

assets/
├─────────────────────────────────────────────────────────────────┐
│ app.ico        back.png        customer.png    employee.png     │
│ BankBranches.csv  Customers.csv  Employees.csv  Transactions... │
│ CompletedLoans.csv  LoanRequests.csv  Date.csv                  │
└─────────────────────────────────────────────────────────────────┘

docs/
└── REPORT.md

GUI/
├──────────────────────────────────────────────────────────────────────────────┐
│ index.html          script.js               statistics.css                   │
│ CustomerInterface.html   CustInt.html      CustomerScript.js                 │
│ EmployeeInterface.html   EmplInt.html      EmployeeScript.js                 │
│ LoanRequest.html         Style.css          StyleCustomerInterface.css       │
│ StyleEmployeeInterface.css                                                   │
└──────────────────────────────────────────────────────────────────────────────┘

include/
├──────────────────────────────────────────────────────────────────────────────┐
│ array.hpp         arrayMeth.hpp     arrayMeth.tpp     customer.hpp           │
│ Customer.tpp      customerMeth.hpp  Dates.hpp          DoublyLinkedList.hpp  │
│ DoublyLinkedListMeth.hpp            Employee.hpp       EmployeeTasks.hpp     │
│ EmployeeTasks.tpp GUI.hpp           Loans.hpp          LoansMeth.hpp         │
│ MiscFuncs.hpp     Queue.hpp         QueueMeth.hpp      SinglyLinkedList.hpp  │
│ SinglyLinkedListMeth.hpp   SinglyLinkedListMeth.tpp   stack.hpp              │
│ stackMeth.hpp     statistics.hpp    transaction.hpp    TransactionMeth.hpp   │
│ webview.h         WebView2.h        WebView2EnvironmentOptions.h             │
└──────────────────────────────────────────────────────────────────────────────┘
    webview/

libs/
└── WebView2LoaderStatic.lib

src/
├─────────────────────────────────────────────────────────────────────────────────┐
│ app.rc             Branches.cpp        Dates.cpp       DoublyLinkedListMeth.cpp │
│ LoansMeth.cpp      main.cpp            main.exe        MiscFuncs.cpp            │
│ QueueMeth.cpp      stackMeth.cpp       statistics.cpp  TransactionMeth.cpp      │
│ app_res.o          temp.exe                                                     │
└─────────────────────────────────────────────────────────────────────────────────┘

tests/
└── BankingSystemTestVer.exe   Test.cpp

```
</div>
---

## **Workflow**
<div align='center' >

```
┌──────────────────────────────────────────────┐
│             APPLICATION STARTUP              │
└─────────────────────────┬────────────────────┘
     │
     ▼
┌──────────────────────────────────────────────┐
│ 1. Launch Application                        │
│    • main.cpp                                │
└─────────────────────────┬────────────────────┘
     │
     ▼
┌───────────────────────────────────────────────┐
│ 2. Load CSV Data                              │
│    • Current Date                             │
│    • Customers, Employees                     │
│    • Loan Requests, Completed Loans           │
│    • Transactions                             │
└─────────────────────────┬─────────────────────┘
    │
    ▼
┌───────────────────────────────────────────────┐
│ 3. Select Random Bank Branch                  │
└─────────────────────────┬─────────────────────┘
    │
    ▼
┌─────────────────────────────────────────────────────┐
│ 4. Initialize WebView2                              │
│    • Create WebView instance                        │
│    • Bind C++ functions                             │
│    • Load GUI/index.html                            │
└────────────────────────────┬────────────────────────┘
    │
    ▼
┌───────────────────────────────────────────────┐
│ 5. User Interfaces (HTML/CSS/JS)              │
│    • Customer Interface                       │
│    • Employee Interface                       │
└─────────────────────────┬─────────────────────┘
    │
    ▼
┌───────────────────────────────────────────────┐
│ 6. Cleanup                                    │
│    • Free dynamic structures                  │
│    • Exit                                     │
└───────────────────────────────────────────────┘
```
</div>


---

## **WebView Bindings**

### Webvies uses a `JSON string` Handshake protocol :
 - <span style="color:#F7DF1E">JavaScript</span> Sends a string.
 - <span style="color:#085E9F;font-weight:bold;">C++</span> recieves the string as a `JSON string` it uses the unJSON function to turn it back into a normal string.
 - Multiple data is sent to <span style="color:#085E9F;font-weight:bold;">C++</span> as a concatination , generally using a seperator `'*'` which it splits using the `splitStr()` function.
 - Multiple data is sent to <span style="color:#F7DF1E">JavaScript</span> as a small `JSON object` for clarity :
 
 > Example :
 > ```Cpp
>return "{\"data\":\"" + Data + "\"}";
> ```
> **a7la project**

# **Bridge pattern:**

>**Cpp Side :**
>```Cpp
>string cppFunction(const string& parems){   
>    /*Code*/
>    return " \"Message\" "
>}
>w.bind("functionName", cppFunction);
>``` 
><br>
<br>

>**JavaScript side**
>```JavaScript
>functionName(params).then(result => {
>    /*Code*/
>});
>```
><br>
---
### **Complete Bindings Table**
<div align="center">

| <span style="color:#F7DF1E">JavaScript</span>| <span style="color:#085E9F;font-weight:bold;">C++</span>|Description           | 
| ------------------------------------------- | --------------------------- | --------------------- | 
| closeWindow                                 | closeWindow                 | Exits app             | 
| getInfo                                     | getInfo                     | Sends Branch + date info <br> to <span style="color:#F7DF1E">JavaScript</span> to display         | 
| goToPage                                    | goToPageCpp                 | Navigate UI           | 
| sendRegCusInfo                              | createNewCustomer           | Registers new customer     | 
| CustLoginCPP                                | CustLoginCpp                | Customer login        | 
| EmplLoginCPP                                | EmplLoginCpp                | Employee login        | 
| getLoggedInCustomerInformationFromCPlusPlus | sendCusLoggedInfoJS         | Sends Logged-in customer Name+balance    |
| getLoggedEmployeeInfoCPP                    | sendEmpLoggedInfoJS         | Sends Logged-in employee Name+ID    | 
| depositCPP                                  | deposit                     | Deposit money into account        | 
| withdrawCPP                                 | withdraw                    | Withdraw money from account        | 
| getTransactionCPP                           | sendTransactionsJS          | Transaction history   | 
| undoTranCPP                                 | undoTranCPP                 | Undo last operation   | 
| sendLoanToCPP                               | receiveLoanReq              | Submit loan request   | 
| getLoanCount                                | sendLoanCountJS             | Sends loan count to <span style="color:#F7DF1E">JavaScript</span>            | 
| getLoansLine                                | sendLoanInfo                | Send info of a specific loan         | 
| receiveQueueSize                            | sendSizeOfQueue             | Send queue size            | 
| receiveCurrentLoanReq                       | sendCurrentLoanReq          | Send current request       | 
| sendAcceptedLoanReq                         | addAcceptedLoanReq          | Treats accepted loans        | 
| declineLoanReq                              | declineLoanReq              | Treats declined request       | 
| receiveLoansOfCustomer                      | sendLoansOfCustomer         | Sends all specific customer loans        | 
| changeLoanStatusOfCustomer                  | updateLoanStatusOfCustomer  | Update loan           | 
| deleteCompletedLoans                        | deleteCompletedLoans        | Deletes completed loans | 
| getCustomerCount                            | sendCustomerCount           | Sends Customer count        | 
| getCustomerLine                             | sendCustomerLine            | Sends Specific customer info     | 
| changeStatusCPP                             | changeStatus                | Changes account status        | 
| receiveTransOfCustomer                      | sendTransOfCustomer         | Sends Customer transactions | 
| getEmployeeCount                            | sendEmployeeCount           | Sends Employee count        | 
| getEmployeeLine                             | sendEmployeeLine            | Specific employee     | 
| addEmployeeCPP                              | addEmployee                 | Adds employee          | 
| modEmployee                                 | modifyEmployee              | Modifies employee       | 
| delEmployee                                 | deleteEmployee              | Deletes employee       | 
| getEarliestEmployee                         | sendEarliestEmpl            | Sends Earliest hired Employee info        | 
| getLatestEmployee                           | sendLatestEmpl              | Sends Latest hired Employee info          | 
| syncLoanReqs                                | syncLoanReqs                | Reloads Loan requests queue          | 
| finalizeDay                                 | finilize                    | End-of-day routine    | 
| getGlobalTotalLoans                         | sendTotalLoans              | Stats: total loans    | 
| getGlobalTotalEmployees                     | sendTotalEmployees          | Stats: employees      | 
| getCustomerMostLoans                        | sendCustomerMostLoans       | Most loans            | 
| getCustomerHighestBalance                   | sendCustomerHighestBalance  | Sends info of Customer <br> with Highest balance       | 
| getCustomerLowestBalance                    | sendCustomerLowestBalance   | Lowest balance        | 
| getLoansByType                              | sendLoansByTypeCount        | Stats by type         | 
| getLoansByStatus                            | sendLoansByStatusCount      | Stats by status       | 
| getActiveLoansInRange                       | sendActiveLoansInRangeCount | Loans in date range   | 
| getEmpByBranch                              | sendEmpByBranchCount        | Employees by branch   | 
</div>


## **Use of Templates**

### We opted to use C++ Templates as it adds a level of abstraction much needed to fit our needs.At the top of most header file we added :
>### Template Definition
>```Cpp
>#define TEMPLATE template <typename T>
>```
><br>
## **Structs used**


> ### **Dynamic Array :**
>```cpp
>template <typename T>
>struct Array {
>    T* data;
>    int size;
>    int capacity;
>};
>```
><br>

> ### **Bank :**
>```cpp
>struct Bank{
>    string branchName;
>    string ID;
>};
>```
><br>

> ### **Customer :**
>```cpp
>struct Customer{
>constexpr int CST_INACTIVE = 0;
>constexpr int CST_ACTIVE = 1;
>constexpr int CST_CLOSED = -1;
>
>    string ID="";
>    string type="";
>    string IBAN="";
>    string branchCode="";
>    string name="";
>    Date openingDate={0,0,0};
>    int status=2;
>    float balance=0;
>    DList loans;
>    Stack transactions;
>    string password="";
>    bool rolledback = false;
>};
>```
>### This also comes with a curentDate global variable defiend using `extern`
><br>

> ### **Date :**
>```cpp
>struct Date
>{
>    int day = 1;
>    int month = 1;
>    int year = 1970;
>};
>```
>### This also comes with a global variable `curentDate` 
><br>

> ### **Doubly Linked List :**
>```cpp
>struct DNode{
>    Loan data={};
>    DNode* next=nullptr;
>    DNode* prev=nullptr;
>};
>
>struct DList {
>    DNode* head=nullptr;
>    DNode* tail=nullptr;
>    int size=0;
>};
>```
><br>

> ### **Employee :**
>```cpp
>struct Employee{
>    string ID;
>    string Name;
>    string LastName;
>    string Adress;
>    float Salary;
>    Date HireDate;
>    string bankBranch;
>    string password;
>};
>```
><br>

> ### **Loan and LoanRequest :**
>```cpp
>//Loan Types
>constexpr int LNT_CAR = 1;
>constexpr int LNT_HOME = 2;
>constexpr int LNT_STUDENT = 3;
>constexpr int LNT_BUSINESS = 4;
>
>//Loan Status
>constexpr int LNS_ACTIVE = 5;
>constexpr int LNS_COMPLETED = 6;
>constexpr int LNS_OVERDUE = 7;
>
>struct Loan{
>    string ID = "";
>    int type = LNT_CAR;
>    int status = LNS_OVERDUE;
>    float pr_amount = -1.0; //principle amount
>    float it_rate = 0.0; //interest rate
>    float am_paid = 0.0; //amount paid
>    float rm_balance = 0.0; //remaining balance
>    Date start_date;
>    Date end_date;
>};
>
>struct LoanRequest{
>    Loan loan = {};
>    int duration = 0;
>    string ID_customer = "NO-CUSTOMER";
>};
>```
>### Addition of LoanRequest was necessary in order to store who sent the request and the duration (makes work easier for us lol)
><br>

> ### **Queue :**
>```cpp
>constexpr int MAX_ELEM_QUEUE = 100;
>
>struct Queue {
>    LoanRequest r_loans[MAX_ELEM_QUEUE];
>    int front = -1;
>    int tail = -1;
>};
>```
><br>

> ### **Singly Linked List :**
>```cpp
>TEMPLATE
>struct SNode {
>    T data;
>    SNode<T>* next;
>};
>
>TEMPLATE
>struct SList {
>    SNode<T>* head=nullptr;
>    int size=0;
>};
>```
>### Singly Linked List is a Templated Struct , it allows us to use the same struct for different cases.
><br>

> ### **Stack :**
>```cpp
>constexpr int MAX_STACK_ELEMENTS = 1024;
>
>struct Stack {
>    Transaction data[MAX_STACK_ELEMENTS];
>    int top = -1;
>};
>```
><br>

> ### **Transaction :**
>```cpp
>constexpr int TR_WITHDRAWAL = 0;
>constexpr int TR_DEPOSIT = 1;
>
>struct Transaction{
>    string ID = "NOID";
>    string accountNumber ="NOACCNUM";
>    int type = -1;
>    int amount = -1;
>    Date date = {};
>};
>```
><br>


## **Data Flow Summary**

### **Customer Login**

```HTML
┌──────────┐     ┌────────┐     ┌──────────┐     ┌───────────────┐
│   HTML   │ ─→  │   JS   │ ─→  │ WebView  │ ─→  │   C++ Search  │
└──────────┘     └────────┘     └──────────┘     └───────┬───────┘
                                                         │
                                                   Validate Login
                                                         │
                                                         ▼
                                                ┌──────────────────┐
                                                │ Set LoggedInUser │
                                                └─────────┬────────┘
                                                          │
                                                          ▼
                                                JS loads customer dashboard
```

### **Loan Request**

```
┌────────────────┐     ┌────────┐     ┌──────────┐     ┌──────────────┐
│ Customer Form  │ ─→  │   JS   │ ─→  │ WebView  │ ─→  │    C++ CSV   │
└────────────────┘     └────────┘     └──────────┘     └───────┬──────┘
                                                               │
                                                      Write Loan Request
                                                               │
                                                               ▼
                                                  ┌─────────────────────────────────┐
                                                  │ Employee Interface (HTML/JS)    │
                                                  └───────────┬─────────────────────┘
                                                              │
                                                  Accept / Decline Loan Request
                                                              │
                                                  Updates CSV & Customer DList
```

### **Transactions + Undo**

```
Deposit/Withdraw Flow                  Undo Flow
───────────────────────────────────    ───────────────────────────────────

    ┌───────────────┐                      ┌──────────┐
    │  C++ Actions  │                      │  C++ Pop │
    └───────┬───────┘                      └─────┬────┘
            │                                    │
    Push transaction onto stack           Reverse operation
            │                                    │
            ▼                                    ▼
 Balance update + CSV write                Update CSV


```

---
# **References**

# **Summary**

This project is a banking management system with:

* Separation between **frontend**, **backend logic**, and **data structuring**
* A **WebView bridge**.
* Fully custom data structures.
* Full CSV persistence system.
* A statistics dashboard.
* Undoable transactions.
* Loan processing with queues and lists.

# Aymen Abdelmoumen |   Skander Sfar Gandoura    |   Melik Bibi   |   Mohammed Aziz Ayouni
