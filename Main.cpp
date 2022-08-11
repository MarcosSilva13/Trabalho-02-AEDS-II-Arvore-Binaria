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
        MainMenu(); // função do menu principal

        cout << "Escolha uma opção: ";
        cin >> option; // lendo a escolha

        system("cls");

        switch (option)
        {
        case 1:
            Register(); // função de cadastro
            break;
        case 2:
            SearchMenu(); // função de pesquisa
            system("cls");
            break;
        case 3:
            RemoveEmployee(); // função de remoção de funcionário
            system("cls");
            break;
        case 4:
            PrintMenu(); // função de exibição dos dados
            system("cls");
            break;
        }
        
        if (option < 1 || option > 5) // condição caso seja digitado um valor inválido
        {
            system("cls");
            cout << "Opção inválida!" << endl;
            Sleep(1500);
            system("cls");
        }

    } while (option != 5);

    return 0;
}