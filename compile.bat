g++ -g -std=c++17 src\main.cpp src\CustomerInterface.cpp src\EmployeeInterface.cpp src\DoublyLinkedListMeth.cpp src\Dates.cpp src\Loans.cpp src\app_res.o -Iinclude -Isdk/include -lole32 -luuid -lversion -lshlwapi -mwindows -o BankingSystem.exe 

pause