#include "statistics.hpp"
#include <iostream>
#include "DoublyLinkedListMeth.hpp"

//aziz fix u
int getTotalLoans(const Array<Customer>& Cus) {
    int total = 0;
    for (int i = 0; i < Cus.size; i++) {
        DNode* current = Cus.data[i].loans.head;
        while (current) {
            total++;
            current = current->next;
        }
    }
    return total;
}

int countLoansByType(Customer* Cus, int nCus, int type) {
    int count = 0;
    for (int i = 0; i < nCus; i++) {
        DNode* current = Cus[i].loans->head;
        while (current) {
            if (current->data.type == type)
                count++;
            current = current->next;
        }
    }
    return count;
}

int countLoansByStatus(Customer* Cus, int nCus, int status) {
    int count = 0;
    for (int i = 0; i < nCus; i++) {
        DNode* current = Cus[i].loans->head;
        while (current) {
            if (current->data.status == status)
                count++;
            current = current->next;
        }
    }
    return count;
}

int countActiveLoansInRange(Customer* Cus, int nCus, Date& startDate, Date& endDate) {
    int counter = 0;
    for (int i = 0; i < nCus; i++) {
        DNode* current = Cus[i].loans->head;
        while (current) {
            Loan& loan = current->data;
            if (loan.status == LNS_ACTIVE &&
                compareDates(loan.start_date, startDate) >= 0 &&
                compareDates(loan.start_date, endDate) <= 0) {
                counter++;
            }
            current = current->next;
        }
    }
    return counter;
}

Customer* customerMostLoans(Customer* Cus, int nCus) {
    if (nCus == 0) return nullptr;

    Customer* best = &Cus[0];
    int maxLoans = listSize(*Cus[0].loans);

    for (int i = 1; i < nCus; i++) {
        int loanCount = listSize(*Cus[i].loans);
        if (loanCount > maxLoans) {
            maxLoans = loanCount;
            best = &Cus[i];
        }
    }
    return best;
}

Customer* customerHighestBalance(Customer* Cus, int nCus) {
    if (nCus == 0) return nullptr;

    Customer* best = &Cus[0];
    for (int i = 1; i < nCus; i++) {
        if (Cus[i].balance > best->balance)
            best = &Cus[i];
    }
    return best;
}

Customer* customerLowestBalance(Customer* Cus, int nCus) {
    if (nCus == 0) return nullptr;

    Customer* best = &Cus[0];
    for (int i = 1; i < nCus; i++) {
        if (Cus[i].balance < best->balance)
            best = &Cus[i];
    }
    return best;
}

int totalEmp(employee* Emp, int nEmp) {
    return nEmp;
}

int countEmpByBranch(employee* Emp, int nEmp, int branchCode) {
    int count = 0;
    for (int i = 0; i < nEmp; i++) {
        if (stoi(Emp[i].bankBranch) == branchCode)
            count++;
    }
    return count;
}


