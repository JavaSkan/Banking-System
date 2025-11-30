#include <DoublyLinkedListMeth.hpp>

int main(int argc, char const *argv[])
{
    Loan l = {
        "IQNSD",
        LNT_CAR,
        LNS_ACTIVE,
        100,
        0.5,
        50,
        20,
        {1,1,2025},
        {1,1,2026}
    };
    DList d = createList();
    insert(&d,l,d.size+1);
    //displayList(d);
    string repr = DLToString(d);
    std::cout << "DLIST REPR: " << repr << endl;
    DList lm = stringToDL(repr);
    displayList(lm);
    destroyList(&lm);
    destroyList(&d);
    return 0;
}
