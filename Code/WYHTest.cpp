#include <iostream>
#define _ON_WIN (_WIN32 || _WIN64)

#if _ON_WIN
#include <Windows.h>
#else
// linux code goes here
#include <unistd.h>
#endif

int i;
void spin() {
#if _ON_WIN
    ::Sleep(1000);
#else
    ::sleep(1);
#endif
}

int main() {
    int* pi = &i;
    std::cout << std::hex << "(" << ::GetCurrentProcessId() << "): "
              << "address of p: " << pi << std::endl;
    while (true) {
        spin();
        *pi = *pi + 1;
        std::cout << std::hex << "(" << ::GetCurrentProcessId() << "): "
                  << std::dec << *pi << std::endl;
    }
}