#include <iostream>
#include <windows.h>
#include "Funcoes.cpp"

using namespace std;
 
int main() {
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);
    
    //MainMenu();
    Register();

    return 0;
}