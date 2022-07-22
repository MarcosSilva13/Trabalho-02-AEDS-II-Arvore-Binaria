#include <iostream>
#include <windows.h>
#include "Funcoes.cpp"

using namespace std;

int main()
{
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    int option = 0; // variavel para escolha da opção do menu

    do
    {
        MainMenu();

        cout << "Escolha uma opção: ";
        cin >> option;

        system("cls");

        switch (option)
        {
        case 1:
            Register();
            break;
        }

        if (option < 1 || option > 5)
        {
            system("cls");
            cout << "Opção inválida!" << endl;
            Sleep(1500);
            system("cls");
        }

    } while (option != 5);

    return 0;
}