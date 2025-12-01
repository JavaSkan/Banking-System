#include "Queue.hpp"
using namespace std;

Queue* createQueue(){
    Queue* q = new (nothrow) Queue;
    if (!q) {
    cout << "Memory is full, did not create the Queue"<<endl;
}
    else {
        q->front = -1;
        q->tail = 0;
}
    return q;
}

int queueSize(const Queue& q){
    if (isEmpty(q)){
        return 0;
    }
    return(q.tail-q.front+1);
}

bool isEmpty(const Queue& q){
    return(q.front==-1);

}

bool isFull(const Queue& q){
    return(q.tail == 99);
}

int enqueue(Queue* q, Loan L){
    if (isFull(*q)){
        cout<<"The queue is full, could not enqueue your loan"<<endl;
        return 0;
    }
    if (isEmpty(*q)){
        q->front = 0;
    } 
    else {
        q->tail++;
    }
    q->r_loans[q->tail] = L;
    return 1;

}

Loan dequeue(Queue* q){
    if (isEmpty(*q)){
        cout<<"The queue is empty, nothing to dequeue"<<endl;
        return Loan{};
    }
    Loan L = q->r_loans[q->front];
    if (q->front == q->tail){
        q->front = -1;
        q->tail = 0;
    }
    else{
         q->front++;
    }
    return(L);
    
}

Loan front(const Queue& q){
    if((isEmpty(q))){
        cout<<"queue is empty, no loan on the front"<<endl;
        return Loan{};
    }
    return(q.r_loans[q.front]);
}




void destroyQueue(Queue* q){
    delete q;
}