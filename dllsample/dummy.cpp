#include <Windows.h>
#include <stdio.h>

//-------------------------------------------------------------------------
#include <iostream>
#include <string>
int main()
{
    std::string s = "";
    std::cout << "Dummy program started...\n";
    while (s != "quit") {
        std::cin >> s;
        std::cout << " ---> " << s << std::endl;

        ::Beep(200, 100);
    }
    std::cout << "Dummy program ended...\n";
    return 0;
}