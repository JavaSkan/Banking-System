g++ -g -std=c++17 src\*.cpp src\app_res.o -Iinclude -Isdk/include -lole32 -luuid -lversion -lshlwapi -mwindows -o BankingSystem 
pause