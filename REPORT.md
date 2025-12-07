
# **Banking System Project – Report**

## **Project Overview**

**General Work Structure**

* **Frontend:** HTML5, CSS3, JavaScript
* **Backend:** C++
* **Bridge:** Microsoft WebView2
* **Architecture:** Desktop application rendered via WebView2

## **Directory Tree**

```
C:.
│   .gitignore
│   BankingSystem.exe
│   compile.bat
│   compiletest.bat
│   IMPORTANT.txt
│   README.md
│   REPORT.md
│   WebView2Loader.dll
│   WORKLOG.md
│
├───.vs
├───.vscode
├───assets
│       app.ico
│       back.png
│       BankBranches.csv
│       CompletedLoans.csv
│       customer.png
│       Customers.csv
│       Date.csv
│       employee.png
│       Employees.csv
│       exit.png
│       LoanRequests.csv
│
├───docs
│       REPORT.md
├───GUI
│       CustInt.html
│       CustomerInterface.html
│       CustomerScript.js
│       EmplInt.html
│       EmployeeInterface.html
│       EmployeeScript.js
│       index.html
│       LoanRequest.html
│       script.js
│       statistics.css
│       StatisticsScript.js
│       Style.css
│       StyleCustomerInterface.css
│       StyleEmployeeInterface.css
│
├───include
│   │   array.hpp
│   │   arrayMeth.hpp
│   │   arrayMeth.tpp
│   │   Branches.hpp
│   │   customer.hpp
│   │   Customer.tpp
│   │   customerMeth.hpp
│   │   Dates.hpp
│   │   DoublyLinkedList.hpp
│   │   DoublyLinkedListMeth.hpp
│   │   Employee.hpp
│   │   EmployeeTasks.hpp
│   │   EmployeeTasks.tpp
│   │   GUI.hpp
│   │   Loans.hpp
│   │   LoansMeth.hpp
│   │   MiscFuncs.hpp
│   │   Queue.hpp
│   │   QueueMeth.hpp
│   │   SinglyLinkedList.hpp
│   │   SinglyLinkedListMeth.hpp
│   │   SinglyLinkedListMeth.tpp
│   │   stack.hpp
│   │   stackMeth.hpp
│   │   statistics.hpp
│   │   transaction.hpp
│   │   TransactionMeth.hpp
│   │   webview.h
│   │   WebView2.h
│   │   WebView2EnvironmentOptions.h
│   │
│   └───webview
├───libs
│       WebView2LoaderStatic.lib
│
├───src
│       app.rc
│       app_res.o
│       Branches.cpp
│       Dates.cpp
│       DoublyLinkedListMeth.cpp
│       LoansMeth.cpp
│       main.cpp
│       main.exe
│       MiscFuncs.cpp
│       QueueMeth.cpp
│       stackMeth.cpp
│       statistics.cpp
│       temp.exe
│       TransactionMeth.cpp
│
└───tests
        BankingSystemTestVer.exe
        Test.cpp
```

---

## **Workflow**


1. Launch Application (main.cpp)
2. Load all CSV data:
   - Current Date
   - Customers, Employees
   - Loan Requests, Completed Loans
   - Transactions
3. Select random bank branch
4. Initialize WebView2:
   - Create WebView instance
   - [Bind](#Binding) C++ functions
   -  Load [index.html](GUI/index.html)
5. UI Loop:
   - Customer Interface
   - Employee Interface
6. Cleanup:
   - Free all dynamic structures
   - Exit


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

**Bridge pattern:**

>**Cpp Side :**
>```Cpp
>string cppFunction(const string& parems){   
>    /*Code*/
>    return " \"Message\" "
>}
>w.bind("functionName", cppFunction);
>``` 
><br>


// JavaScript side
window.functionName(params).then(result => {
    /*Code*/
});
```

### **Complete Binding Table (42 functions)**

| JavaScript                                  | C++                         | Description           | Returns    |
| ------------------------------------------- | --------------------------- | --------------------- | ---------- |
| closeWindow                                 | closeWindow                 | Exit app              | string     |
| getInfo                                     | getInfo                     | Branch + date         | JSON       |
| goToPage                                    | goToPageCpp                 | Navigate UI           | string     |
| sendRegCusInfo                              | createNewCustomer           | Register customer     | string     |
| CustLoginCPP                                | CustLoginCpp                | Customer login        | string     |
| EmplLoginCPP                                | EmplLoginCpp                | Employee login        | string     |
| getLoggedInCustomerInformationFromCPlusPlus | sendCusLoggedInfoJS         | Logged-in customer    | JSON       |
| getLoggedEmployeeInfoCPP                    | sendEmpLoggedInfoJS         | Logged-in employee    | JSON       |
| depositCPP                                  | deposit                     | Deposit money         | string     |
| withdrawCPP                                 | withdraw                    | Withdraw money        | string     |
| getTransactionCPP                           | sendTransactionsJS          | Transaction history   | JSON       |
| undoTranCPP                                 | undoTranCPP                 | Undo last operation   | string     |
| sendLoanToCPP                               | receiveLoanReq              | Submit loan request   | string     |
| getLoanCount                                | sendLoanCountJS             | Loan count            | JSON       |
| getLoansLine                                | sendLoanInfo                | Specific loan         | JSON       |
| receiveQueueSize                            | sendSizeOfQueue             | Queue size            | JSON       |
| receiveCurrentLoanReq                       | sendCurrentLoanReq          | Current request       | JSON       |
| sendAcceptedLoanReq                         | addAcceptedLoanReq          | Accept request        | string     |
| declineLoanReq                              | declineLoanReq              | Decline request       | string     |
| receiveLoansOfCustomer                      | sendLoansOfCustomer         | Customer loans        | JSON array |
| changeLoanStatusOfCustomer                  | updateLoanStatusOfCustomer  | Update loan           | string     |
| deleteCompletedLoans                        | deleteCompletedLoans        | Purge completed loans | string     |
| getCustomerCount                            | sendCustomerCount           | Customer count        | JSON       |
| getCustomerLine                             | sendCustomerLine            | Specific customer     | JSON       |
| changeStatusCPP                             | changeStatus                | Account status        | string     |
| receiveTransOfCustomer                      | sendTransOfCustomer         | Customer transactions | JSON       |
| getEmployeeCount                            | sendEmployeeCount           | Employee count        | JSON       |
| getEmployeeLine                             | sendEmployeeLine            | Specific employee     | JSON       |
| addEmployeeCPP                              | addEmployee                 | Add employee          | string     |
| modEmployee                                 | modifyEmployee              | Modify employee       | string     |
| delEmployee                                 | deleteEmployee              | Delete employee       | string     |
| getEarliestEmployee                         | sendEarliestEmpl            | Earliest hired        | JSON       |
| getLatestEmployee                           | sendLatestEmpl              | Latest hired          | JSON       |
| syncLoanReqs                                | syncLoanReqs                | Reload queue          | string     |
| finalizeDay                                 | finilize                    | End-of-day routine    | string     |
| getGlobalTotalLoans                         | sendTotalLoans              | Stats: total loans    | JSON       |
| getGlobalTotalEmployees                     | sendTotalEmployees          | Stats: employees      | JSON       |
| getCustomerMostLoans                        | sendCustomerMostLoans       | Most loans            | JSON       |
| getCustomerHighestBalance                   | sendCustomerHighestBalance  | Highest balance       | JSON       |
| getCustomerLowestBalance                    | sendCustomerLowestBalance   | Lowest balance        | JSON       |
| getLoansByType                              | sendLoansByTypeCount        | Stats by type         | JSON       |
| getLoansByStatus                            | sendLoansByStatusCount      | Stats by status       | JSON       |
| getActiveLoansInRange                       | sendActiveLoansInRangeCount | Loans in date range   | JSON       |
| getEmpByBranch                              | sendEmpByBranchCount        | Employees by branch   | JSON       |

---

## **🧱 Data Structures**

### **Dynamic Array**

```cpp
template <typename T>
struct Array {
    T* data;
    int size;
    int capacity;
};
```

Used for: **Customers, Employees**

---

### **Singly Linked List**

Generic list for completed loans and finalized transactions.

---

### **Doubly Linked List**

Used for **active customer loans**.

Optimized traversal:

* First half → start from head
* Second half → start from tail

---

### **Stack**

Used for **undoable transaction history**.

---

### **Queue**

Used for **loan requests** (FIFO).

---

## **📈 Data Flow Summary**

### **Customer Login**

```
HTML → JS → WebView → C++ search → Validate → Set LoggedInCustomer → Return → JS loads dashboard
```

### **Loan Request**

```
Customer form → JS → WebView → C++ writes CSV → Employee views → Accept/Decline → CSV updates → Customer DList
```

### **Transactions + Undo**

```
Deposit/Withdraw → C++ push to stack → Balance update → CSV
Undo → C++ pop → Reverse effect → CSV
```

---

# **👥 Developer Responsibilities**

## **Frontend Developer**

**Files:** ~2,591 lines
Handles:

* Customer UI
* Employee UI
* Statistics Dashboard
* Styling system (dark gold theme)
* 42 JS bridge functions
* Grids, cards, layouts, interactions

---

## **Backend Developer – Data Structures**

**Files:** ~1,020 lines
Implements:

* Dynamic arrays
* Singly and doubly linked lists
* Stacks
* Queues
* Serialization and deserialization
* Memory management

---

## **Backend Developer – Business Logic**

**Files:** ~1,540 lines
Responsible for:

* Customer management (IDs, RIB, IBAN, passwords)
* Employee management
* Loan system
* Transaction system + undo
* All 42 WebView bindings
* CSV file I/O
* Authentication and session state
* Application main flow

---

## **Backend Developer – Utilities & Statistics**

Handles:

* Date utilities (compare, increment, leap years)
* Branch selection
* JSON formatting functions
* String split/unescape helpers
* 12 statistical modules (global + per customer/employee)

---

# **📌 Summary**

This project is a complete banking management system with:

* Strong separation between **frontend**, **backend logic**, and **data structure engineering**
* A **42-function WebView bridge**
* Fully custom data structures
* Full CSV persistence system
* Polished UI and dashboards
* A detailed statistics engine
* Undoable transactions
* Loan processing with queues and lists

It is a full desktop application built like a web app.

The system is modular and scalable, making it an excellent foundation for adding:

* Graph database exports
* Encryption for CSV files
* Branch clustering logic
* React-based UI migration

The architecture leaves many interesting expansion paths to explore.
