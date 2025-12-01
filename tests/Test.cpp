#include <MiscFuncs.hpp>
#include  <customerMeth.hpp>
#include <arrayMeth.hpp>

int main(int argc, char const *argv[])
{
    Array<Customer> s = createArray<Customer>(10);
    init_customerArray(s);
    cout << "SIZE OF ARRAY CUSTOMER: " << s.size << endl;
    for(int i = 0; i < s.size; i++){
        Customer Cus = s.data[i];
        cout<<"ID : "<<Cus.ID<<endl;
        cout<<"type : "<<Cus.type<<endl;
        cout<<"IBAN : "<<Cus.IBAN<<"("<<Cus.IBAN.size()<<")"<<endl;
        cout<<"branch code : "<<Cus.branchCode<<endl;
        cout<<"name : "<<Cus.name<<endl;
        cout<<"opening date : "<<Cus.openingDate.day<<"-"<<Cus.openingDate.month<<"-"<<Cus.openingDate.year<<endl;
        cout<<"status : "<<Cus.status<<endl;
        cout<<"balance : "<<Cus.balance<<endl;
        cout<<"password : "<<Cus.password<<endl;
    }
    return 0;
}
