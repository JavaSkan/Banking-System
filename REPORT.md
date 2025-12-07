
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
│    • Bind C++ functions  →  see: [Binding](#binding)│
│    • Load GUI/index.html                            │
└────────────────────────────┬────────────────────────┘
    │
    ▼
┌───────────────────────────────────────────────┐
│ 5. User Interfaces (HTML/CSS/JS)              │
│    • Customer Interface                       │
│    • Employee Interface                       │
└───────────────────────────┬───────────────────┘
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
