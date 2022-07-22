#include <iostream>
#include <windows.h>

using namespace std;

typedef struct Date
{
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

typedef struct Address
{
    char street[30];
    int number;
    char district[20];
    char city[20];
    char state[2];
    char zipCode[10];
};

typedef struct Info
{
    int registration;
    char cpf[14];
    char name[50];
    char role[30];
    char telephone[15];
    Date birthDate;
    Address address;
};

typedef struct No
{
    Info *info;
    No *left;
    No *right;
};

No *treeByCPF = NULL;
No *treeByName = NULL;

No *root = NULL;

void MainMenu(); // Menu principal do programa para a escolha das opcoes
int SearchMenu();
void Register();
int add(Info *empInfo);


void MainMenu(){

    system("color 03");
    cout << "  \n        ��������������������������������";
    cout << "  \n        �                              �";
    cout << "  \n        �          SISTEMA RH          �";
    cout << "  \n        �                              �";
    cout << "  \n        ��������������������������������";
    cout << "  \n        �                              �";
    cout << "  \n        � 1 - Cadastrar Funcionário    �";
    cout << "  \n        �                              �";
    cout << "  \n        � 2 - Buscar Funcionário       �";
    cout << "  \n        �                              �";
    cout << "  \n        � 3 - Remover Funcionário      �";
    cout << "  \n        �                              �";
    cout << "  \n        � 4 - Imprimir Dados           �";
    cout << "  \n        �                              �";
    cout << "  \n        � 5 - Sair                     �";
    cout << "  \n        �                              �";
    cout << "  \n        ��������������������������������\n\n";
}
int SearchMenu(){

}

void Register(){
    Info empInfo;

    cout << "*******************************************\n";
    cout << "*         CADASTRO DE FUNCIONÁRIO         *\n";
    cout << "*******************************************\n\n";

    cout << "Informe a matricula: ";
    cin >> empInfo.registration;
    
    cout << "\nInforme o cpf: ";
    cin >> empInfo.cpf;
    
    cout << "\nInforme o nome: ";
    cin >> empInfo.name;

    cout << "\nInforme o cargo: ";
    cin >> empInfo.role;

    cout << "\nInforme o telefone: ";
    cin >> empInfo.telephone;

    cout << "\nInforme a data de nascimento" << endl;
    cout << "Dia: ";
    cin >> empInfo.birthDate.day;
    cout << "Mês: ";
    cin >> empInfo.birthDate.month;
    cout << "Ano: ";
    cin >> empInfo.birthDate.year;

    cout << "\nInforme o endereco" << endl;
    cout << "Rua: ";
    cin >> empInfo.address.street;
    cout << "Número: ";
    cin >> empInfo.address.number;
    cout << "Bairro: ";
    cin >> empInfo.address.district;
    cout << "Cidade: ";
    cin >> empInfo.address.city;
    cout << "Estado (somente a sigla): ";
    cin >> empInfo.address.state;
    cout << "Cep: ";
    cin >> empInfo.address.zipCode;

    if (add(&empInfo) == 1){
        cout << "\nFuncionario cadastrado!" << endl;
    } else {
        cout << "\nNão foi possivel adicionar!" << endl;
    }

}

int add(Info *empInfo){
    
    No *newNo = new No;
    newNo->info = empInfo;
    newNo->left = NULL;
    newNo->right = NULL;

    if (root == NULL)
    {
        root = newNo;

        return 1;
    }

    No *current = root;
    No *previous = NULL;

    while (current != NULL)
    {
        previous = current;
        if (empInfo->registration < current->info->registration)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if (empInfo->registration < previous->info->registration)
    {
        previous->left = newNo;
    }
    else if (empInfo->registration > previous->info->registration)
    {
        previous->right = newNo;
    }
    else
    {
        return -1;
    }
    return 1;
}