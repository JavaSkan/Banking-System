#include <QueueMeth.hpp>
using namespace std;

Queue* createQueue(){
    Queue* q = new (nothrow) Queue;
    if (!q) {
        cout << "Memory is full, did not create the Queue"<<endl;
        return nullptr;
    }
    return q;
}

bool isEmpty(const Queue& q){
    return(q.front==-1);
}

int queueSize(const Queue& q){
    if (isEmpty(q)){
        return 0;
    }
    return(q.tail-q.front+1);
}

bool isFull(const Queue& q){
    return q.tail == MAX_ELEM_QUEUE-1;
}

int enqueue(Queue* q, LoanRequest L){
    if (isFull(*q)){
        cout<<"The queue is full, could not enqueue your LoanRequest"<<endl;
        return 0;
    }
    if (isEmpty(*q)){
        q->front = q->tail = 0;
    } 
    else {
        q->tail++;
    }
    q->r_loans[q->tail] = L;
    return 1;
}

LoanRequest dequeue(Queue* q){
    if (isEmpty(*q)){
        cout<<"The queue is empty, nothing to dequeue"<<endl;
        return LoanRequest{};
    }
    LoanRequest L = q->r_loans[q->front];
    if (q->front == q->tail){
        q->front = q->tail = 0;
    }
    else{
         q->front++;
    }
    return(L);
}

LoanRequest front(const Queue& q){
    if((isEmpty(q))){
        cout<<"queue is empty, no LoanRequest on the front"<<endl;
        return LoanRequest{};
    }
    return(q.r_loans[q.front]);
}

void destroyQueue(Queue* q){
    delete q;
}