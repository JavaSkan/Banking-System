#include <iostream>
using namespace std;

int* copy(int* p,int n,int*q){
    for (int i = 0;i<n;i++){
        q[i]=p[i];
    }
    
}


int* add(int* p,int n,int usedSpace,int x){
    if (usedSpace==n-1){
        int* q = new int[2*n];
        copy(p,n,q);
        q[n+1]=x;
        delete p;
        return(q);
    }
    else{
        p[usedSpace+1]=x;
        return(p);
    }

}


int main(){
    int n;
    cout<<"het karmous";
    cin>>n;
    int* p = new int[n];
    int usedSpace = 0;
    for (int i =0;i<n;i++){
        cout<<"give stuff number"<<i+1;
        cin>>p[i];
        usedSpace++;
    }
    p= add(p,n,usedSpace,25);
    for (int i=0;i<n)




}