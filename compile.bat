g++ -g -std=c++17 src\main.cpp src\CustomerInterface.cpp src\EmployeeInterface.cpp include\SinglyLinkedListMeth.tpp include\DoublyLinkedListMeth.cpp src\DataStructsFunctions.tpp src\Dates.cpp src\Loans.cpp -Iinclude -Isdk/include -lole32 -luuid -lversion -lshlwapi -mwindows -o BankingSystem.exe
pause
 