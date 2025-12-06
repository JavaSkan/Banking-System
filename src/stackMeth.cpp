#include <stackMeth.hpp>
#include <transactionMeth.hpp>
#include <iostream>

Stack createStack() {
    return {};
}

void destroyStack(Stack& s) {
    s.top = -1;
}

void push(Stack& s, Transaction t) {
    if (isFull(s)) {
        std::cerr << "Stack is full\n";
    }else{
        s.data[++s.top] = t;
    }
}


Transaction pop(Stack& s) {
    if (isEmpty(s)) {
        std::cerr << "Stack underflow!\n";
        return Transaction{};
    }
    return s.data[s.top--];
}


Transaction top(const Stack& s) {
    if (isEmpty(s)) {
        std::cerr << "Stack is empty!\n";
        return Transaction{};
    }
    return s.data[s.top];
}

bool isEmpty(const Stack& s) {
    return s.top == -1;
}

bool isFull(const Stack& s){
    return s.top == MAX_STACK_ELEMENTS-1;
}

string stackToString(const Stack& s){
    if(isEmpty(s))
        return "STACK[]";
    stringstream ss;
    ss << "STACK[" << s.top+1 << "/";
    for(int i = 0; i < s.top; i++){
        ss << transactionToString(s.data[i]) << "/";
    }
    ss << transactionToString(s.data[s.top]); //To avoid adding the last redundant '/';
    ss << "]";
    return ss.str();
}

Stack stringToStack(string s){
    Stack res = createStack();
    string sub = "";
    for(int i = 6; i < s.size()-1; i++){
        if(s[i] == '/') sub += ' '; else sub += s[i];
    }
    if(sub == "") return {};
    stringstream ss;
    ss << sub;
    int num_elements;
    ss >> num_elements;
    string cur_tr_str; //current transaction string
    for(int i = 1; i <= num_elements; i++){
        ss >> cur_tr_str;
        push(res,stringToTransaction(cur_tr_str));
    }
    return res;
}

Stack copyStack(const Stack& S) {
    Stack newStack = createStack();

    for (int i = 0; i <= S.top; i++) {
        push(newStack, S.data[i]);
    }

    return newStack;
}