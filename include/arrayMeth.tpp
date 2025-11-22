#include "arrayMeth.hpp"
#define TEMPLATE template <typename T>
using namespace std;

TEMPLATE
Array<T> createArray(int capacity) {
    if (capacity < 1){
        cerr<<"Error : the array`s capacity must be at least 1.The provided capacity is :"<<capacity<<endl;
        return Array<T>{nullptr,0,1};
    }
    else{
        return Array<T>{new T[capacity], 0,capacity};
    }
    
}

TEMPLATE
void destroyArray(Array<T> p) {
    delete[] p.data;
    p.size = 0;
    p.capacity = 0;
}


TEMPLATE
bool isEmpty(const Array<T>& p) {
    return p.size == 0;
}

TEMPLATE
bool isFull(const Array<T>& p) {
    return(p.size == p.capacity);
}


TEMPLATE
void displayArray(const Array<T>& p) {
    for (int i = 0; i < p.size; ++i)
        cout << p.data[i] << ",";
    cout << endl;
}

TEMPLATE

int addElement(Array<T>* p,T e,int pos){
    if (pos<0 || pos> p->size+1){
        cout<<"invalid position"<<endl;
        return (-1);
    }
    if (isFull(*p)){
            resizeArray(*p,(p->capacity)*2);
        }

    for(int i = p->size; i>pos;i--){
                p->data[i]=p->data[i-1];
            }
    p->data[pos]=e;
    p->size++;
    return 1;

}



TEMPLATE
Array<T> copyArray(const Array<T>& p){
    Array<T> copy = createArray(p.capacity);
    copy.size = p.size;

    for (int i = 0; i<p.size; i++){
        copy.data[i] = p.data[i];
    }
    return(copy);
}

TEMPLATE
void resizeArray(Array<T>& p, int newCapacity) {
    T* data = new T[newCapacity];

    for (int i = 0; i < p.size; i++) {
        data[i] = p.data[i];
    }

    delete[] p.data;

    p.data = data;
    p.capacity = newCapacity;
}

TEMPLATE
void removeAtArray(Array<T>& p, int pos) {
    if (pos < 0 || pos >= p.size) {
        cout << "invalid position" << std::endl;
        return;
    }

    for (int i = pos; i < p.size - 1; i++) {
        p.data[i] = p.data[i + 1];
    }

    p.size--;
}
