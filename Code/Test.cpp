#include <iostream>
#define _ON_WIN (_WIN32 || _WIN64)
#if _ON_WIN
#include <Windows.h>
#else
// linux code goes here
#include <unistd.h>
#endif

void spin() {
#if _ON_WIN
    ::Sleep(1000);
#else
    ::sleep(1);
#endif
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: cpu <string>" << std::endl;
        return -1;
    }
    char* str = argv[1];
    while (1) {
        spin();
        std::cout << str << std::endl;
    }
}