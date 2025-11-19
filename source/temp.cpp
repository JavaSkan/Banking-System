#include <iostream>
#include "..\headers\ArrayMeth.hpp"
using namespace std;

int main(){
    Array<int> p = createArray<int>();
    int size = 5;
    p.data = new int[size];
    for (int i = 0;i<size;i++){
        cout<<"uihwqiud";
        cin>>p.data[i];
        p.size++;
    }
    for (int i = 0;i<size;i++){
        cout<<p.data[i];
    }

}