#include <LoansMeth.hpp>

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
    string repr = loanToString(l);
    std::cout << repr << endl;
    Loan lm = stringToLoan(repr);
    displayLoan(lm);
    return 0;
}
