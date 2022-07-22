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
    char state[3];
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
    Info info;
    No *left;
    No *right;
};

No *treeByCPF = NULL;
No *treeByName = NULL;

No *root = NULL;

void MainMenu(); // Menu principal do programa para a escolha das opcoes

void SearchMenu(); // Função para escolha da opção de pesquisa, se é por cpf ou por nome

void SearchHeader(int option); // Função para exibir os cabeçalhos do tipo de pesquisa

void Search(int option); // Função para o controle da pesquisa, indicando qual operação será executada

No* SearchByCpf(No *treeByCPF, char cpf[]); // Função que percorre a arvore procurando pelo cpf do funcionário

void Register(); // Função para cadastrar os dados do funcionário da struct

int Add(Info empInfo); // Função que insere na árvore binária

void GetDataEmployee(No *no); // Função que percorre os dados do funcionário

void PrintData(No *no); // Função que imprimi os dados encontrados do funcionário

void MainMenu()
{

    system("color 0E");
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

void SearchMenu()
{
    int option = 0; // variavel para escolha da opção de buscar funcionário
    
    do
    {
        cout << "*******************************************\n";
        cout << "*            BUSCAR FUNCIONÁRIO           *\n";
        cout << "*******************************************\n\n";
        cout << "1 - Buscar por CPF\n2 - Buscar por Nome\n3 - Cancelar\n\nEscolha uma opção: ";
        cin >> option;

        if (option < 1 || option > 3)
        {
            system("cls");
            cout << "Opção inválida!" << endl;
            Sleep(1500);
            system("cls");
        }
        else 
        {
            Search(option); // passando a opção escolhida para a função Search
        }
    } while (option != 3);
}

void SearchHeader(int option){
    system("cls");

    switch (option)
    {
    case 1:
        cout << "*******************************************\n";
        cout << "*              BUSCA POR CPF              *\n";
        cout << "*******************************************\n\n";
        break;
    case 2:
        cout << "*******************************************\n";
        cout << "*             BUSCAR POR NOME             *\n";
        cout << "*******************************************\n\n";
        break;
    default:
        cout << "Opção inválida!" << endl;
        break;
    }
    
}

void Search(int option){
    char cpf[14]; // variável para guardar o cpf do funcionário para a buscar
    char name[50]; // variável para guardar o nome do funcionário para buscar
    No *result = NULL; // ponteiro para receber a referência da função SearchByCpf e SearchByName

    switch (option)
    {
        case 1: //arrumar em mais funções e comparar se for null para nao dar erro na hora de mostrar
            SearchHeader(1);
            cout << "Informe o cpf: ";
            cin.ignore();
            cin.get(cpf, 14);
            result = SearchByCpf(treeByCPF, cpf);
            if (result != NULL)
            {
                PrintData(result);
            } 
            else 
            {
                cout << "\nFuncionário não encontrado!" << endl << endl;
                system("pause");
                system("cls");
            }
            break;
        case 2:
            SearchHeader(2);
            break;
        default:
            cout << "Algum erro ocorreu" << endl << endl;
            break;
    }
}

void Register()
{
    Info empInfo;

    cout << "*******************************************\n";
    cout << "*         CADASTRO DE FUNCIONÁRIO         *\n";
    cout << "*******************************************\n\n";

    cout << "Informe a matricula: ";
    cin >> empInfo.registration;

    cout << "\nInforme o cpf: ";
    cin.ignore();
    cin.get(empInfo.cpf, 14);

    cout << "\nInforme o nome: ";
    cin.ignore();
    cin.get(empInfo.name, 50);

    cout << "\nInforme o cargo: ";
    cin.ignore();
    cin.get(empInfo.role, 30);

    cout << "\nInforme o telefone: ";
    cin.ignore();
    cin.get(empInfo.telephone, 15);

    cout << "\nInforme a data de nascimento" << endl;
    cout << "Dia: ";
    cin >> empInfo.birthDate.day;
    cout << "Mês: ";
    cin >> empInfo.birthDate.month;
    cout << "Ano: ";
    cin >> empInfo.birthDate.year;

    cout << "\nInforme o endereco" << endl;
    cout << "Rua: ";
    cin.ignore();
    cin.get(empInfo.address.street, 30);

    cout << "Número: ";
    cin >> empInfo.address.number;

    cout << "Bairro: ";
    cin.ignore();
    cin.get(empInfo.address.district, 20);

    cout << "Cidade: ";
    cin.ignore();
    cin.get(empInfo.address.city, 20);

    cout << "Estado (somente a sigla): ";
    cin.ignore();
    cin.get(empInfo.address.state, 3);

    cout << "Cep: ";
    cin.ignore();
    cin.get(empInfo.address.zipCode, 10);

    // retornando mensagem se foi possivel adicionar o funcionário na árvore
    if (Add(empInfo) == 1)
    {
        cout << "\nFuncionário cadastrado com sucesso!" << endl;
        Sleep(1500);
    }
    else
    {
        cout << "\nNão foi possivel adicionar!" << endl;
        Sleep(1500);
    }

    system("cls");
}

int Add(Info empInfo)
{

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
        if (empInfo.registration < current->info.registration)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if (empInfo.registration < previous->info.registration)
    {
        previous->left = newNo;
    }
    else if (empInfo.registration > previous->info.registration)
    {
        previous->right = newNo;
    }
    else
    {
        return -1;
    }
    return 1;
}

No* SearchByCpf(No *treeByCPF, char cpf[])
{
    No *current = treeByCPF;
    while (current != NULL)
    {
        if (strcmp(cpf, current->info.cpf) == 0)
        {
            return current;
        }
        else if (strcmp(cpf, current->info.cpf) < 0)
        {
            return SearchByCpf(root->left, cpf);
        }
        else if (strcmp(cpf, current->info.cpf) > 0)
        {
            return SearchByCpf(root->right, cpf);
        }
    }
    return NULL;
}

void GetDataEmployee(No *no)
{
    /*cout << "*******************************************\n";
    cout << "*           DADOS DO FUNCIONÁRIO          *\n";
    cout << "*                 EM ORDEM                *\n";
    cout << "*******************************************\n\n";*/

    if (no != NULL)
    {
        PrintData(no->left);
        GetDataEmployee(no);
        PrintData(no->right);
    }
}

void PrintData(No *no)
{
    cout << "-------------------------------------------" << endl;
    cout << "Matricula: " << no->info.registration << endl;
    cout << "Nome: " << no->info.name << endl;
    cout << "Cpf: " << no->info.cpf << endl;
    cout << "Cargo: " << no->info.role << endl;
    cout << "Telefone: " << no->info.telephone << endl;
    cout << "Data de nascimento: " << no->info.birthDate.day << "/" << no->info.birthDate.month << "/"
         << no->info.birthDate.year << endl;
    cout << "Endereço" << endl;
    cout << "Rua: " << no->info.address.street << endl;
    cout << "Número: " << no->info.address.number << endl;
    cout << "Bairro: " << no->info.address.district << endl;
    cout << "Cidade: " << no->info.address.city << endl;
    cout << "Estado: " << no->info.address.state << endl;
    cout << "Cep: " << no->info.address.zipCode << endl;
    cout << "-------------------------------------------" << endl
         << endl;
}