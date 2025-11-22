#include <iostream>
#include "../include/arrayMeth.hpp"
using namespace std;

int main(){
    Array<int> J = createArray<int>(5);
    for (int i = 0;i<J.capacity;i++){
        J.data[i] = 5;
        J.size++;
    };
    cout<<"old size is :"<<
    addElement<int>(&J,7,5);
    displayArray(J);
    cout<<"Full array ? "<<isFull(J)<<endl;
    cout<<"NIGGA mooooooooooooooooooveeeeee"<<endl;
    return 0;
}