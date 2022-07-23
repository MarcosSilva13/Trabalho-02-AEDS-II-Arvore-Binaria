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

No *root = NULL;

void MainMenu(); // Menu principal do programa para a escolha das opcoes

void SearchMenu(); // Função para escolha da opção de pesquisa, se é por cpf ou por nome

void SearchHeader(int option); // Função para exibir os cabeçalhos do tipo de pesquisa

void Search(int option); // Função para o controle da pesquisa, indicando qual operação será executada

No *SearchByCpf(No *treeByCPF, char cpf[]); // Função que percorre a arvore procurando pelo cpf do funcionário

No *SearchByName(No *treeByName, char name[]); // Função que percorre a arvore procurando pelo nome do funcionário

void Register(); // Função para cadastrar os dados do funcionário da struct

int Add(Info empInfo); // Função que insere na árvore binária

void GetDataEmployee(No *node); // Função que percorre os dados do funcionário

void PrintData(No *node); // Função que imprimi os dados encontrados do funcionário

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

        // condição caso seja digitado um valor menor que 1 ou maior que 3
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

void SearchHeader(int option)
{
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

void Search(int option)
{
    char cpf[14];          // variável para guardar o cpf do funcionário para a buscar
    char name[50];         // variável para guardar o nome do funcionário para buscar
    No *result = NULL;     // ponteiro para receber a referência da função SearchByCpf e SearchByName
    No *treeByCpf = root;  // ponteiro para receber a referência da raiz e ser usado na função SearchByCpf
    No *treeByName = root; // ponteiro para receber a referência da raiz e ser usado na função SearchByName

    switch (option)
    {
    case 1:
        SearchHeader(1); // função do cabeçalho
        cout << "Informe o cpf: ";
        cin.ignore();
        cin.get(cpf, 14);                     // lendo o valor do cpf para busca
        result = SearchByCpf(treeByCpf, cpf); // guardando a referência do resultado da busca

        if (result != NULL)
        {
            cout << "\n\t ***Funcionário Encontrado***" << endl;
            PrintData(result); // passando a referencia para a função para exibir os dados encontrados
            system("pause");
            system("cls");
        }
        else
        {
            cout << "\nFuncionário não encontrado!" << endl
                 << endl;
            system("pause");
            system("cls");
        }
        break;
    case 2:
        SearchHeader(2); // função do cabeçalho
        cout << "Informe o nome: ";
        cin.ignore();
        cin.get(name, 50);                       // lendo o valor do nome para busca
        result = SearchByName(treeByName, name); // guardando a referência do resultado da busca

        if (result != NULL)
        {
            cout << "\n\t ***Funcionário Encontrado***" << endl;
            PrintData(result); // passando a referencia para a função para exibir os dados encontrados
            system("pause");
            system("cls");
        }
        else
        {
            cout << "\nFuncionário não encontrado!" << endl
                 << endl;
            system("pause");
            system("cls");
        }
        break;
    default:
        cout << "Algum erro ocorreu" << endl
             << endl;
        break;
    }
}

No *SearchByCpf(No *treeByCPF, char cpf[])
{
    No *current = treeByCPF;
    while (current != NULL)
    {
        if (strcmp(cpf, current->info.cpf) == 0) // compara os valores do cpf, se for 0 são iguais
        {
            return current; // retorna a referência
        }
        else if (strcmp(cpf, current->info.cpf) < 0) // compara os valores do cpf, se for menor que 0, a primeira
                                                     // string é menor que a segunda
        {
            return SearchByCpf(treeByCPF->left, cpf); // chama a função recursivamente indo para a esquerda da árvore
        }
        else if (strcmp(cpf, current->info.cpf) > 0) // compara os valores do cpf, se for maior que 0, a primeira
                                                     // string é maior que a segunda
        {
            return SearchByCpf(treeByCPF->right, cpf); // chama a função recursivamente indo para a direita da árvore
        }
    }
    return NULL; // retorna null se não encontrar nada
}

No *SearchByName(No *treeByName, char name[])
{
    No *current = treeByName;
    while (current != NULL)
    {
        if (strcmp(name, current->info.name) == 0) // compara os valores do nome, se for 0 são iguais
        {
            return current; // retorna a referência
        }
        else if (strcmp(name, current->info.name) < 0) // compara os valores do nome, se for menor que 0, a primeira
                                                       // string é menor que a segunda
        {
            return SearchByName(treeByName->left, name); // chama a função recursivamente indo para a esquerda da árvore
        }
        else if (strcmp(name, current->info.name) > 0) // compara os valores do nome, se for maior que 0, a primeira
                                                       // string é maior que a segunda
        {
            return SearchByName(treeByName->right, name); // chama a função recursivamente indo para a direita da árvore
        }
    }
    return NULL; // retorna null se não encontrar nada
}

void Register()
{
    Info empInfo; // variável da struct Info

    cout << "*******************************************\n";
    cout << "*         CADASTRO DE FUNCIONÁRIO         *\n";
    cout << "*******************************************\n\n";

    cout << "Informe a matricula: ";
    cin >> empInfo.registration; // lendo a matricula

    cout << "\nInforme o cpf: ";
    cin.ignore();
    cin.get(empInfo.cpf, 14); // lendo o cpf

    cout << "\nInforme o nome: ";
    cin.ignore();
    cin.get(empInfo.name, 50); // lendo o nome

    cout << "\nInforme o cargo: ";
    cin.ignore();
    cin.get(empInfo.role, 30); // lendo o cargo

    cout << "\nInforme o telefone: ";
    cin.ignore();
    cin.get(empInfo.telephone, 15); // lendo o telefone

    cout << "\nInforme a data de nascimento" << endl; // leitura da data de nascimento
    cout << "Dia: ";
    cin >> empInfo.birthDate.day; // lendo o dia
    cout << "Mês: ";
    cin >> empInfo.birthDate.month; // lendo o mês
    cout << "Ano: ";
    cin >> empInfo.birthDate.year; // lendo o ano

    cout << "\nInforme o endereco" << endl; // leitura do endereço
    cout << "Rua: ";
    cin.ignore();
    cin.get(empInfo.address.street, 30); // lendo a rua

    cout << "Número: ";
    cin >> empInfo.address.number; // lendo o número

    cout << "Bairro: ";
    cin.ignore();
    cin.get(empInfo.address.district, 20); // lendo o bairro

    cout << "Cidade: ";
    cin.ignore();
    cin.get(empInfo.address.city, 20); // lendo a cidade

    cout << "Estado (somente a sigla): ";
    cin.ignore();
    cin.get(empInfo.address.state, 3); // lendo o estado

    cout << "Cep: ";
    cin.ignore();
    cin.get(empInfo.address.zipCode, 10); // lendo o cep

    // retornando mensagem se foi possivel adicionar o funcionário na árvore ou não
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
    No *newNode = new No;
    newNode->info = empInfo;
    newNode->left = NULL;
    newNode->right = NULL;

    if (root == NULL)
    {
        root = newNode;

        return 1;
    }

    No *current = root;
    No *previous = NULL;

    // inserindo na arvore comparando pelo número da matricula
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
        previous->left = newNode;
    }
    else if (empInfo.registration > previous->info.registration)
    {
        previous->right = newNode;
    }
    else
    {
        return -1;
    }
    return 1;
}

void GetDataEmployee(No *node)
{
    /*cout << "*******************************************\n";
    cout << "*           DADOS DO FUNCIONÁRIO          *\n";
    cout << "*                 EM ORDEM                *\n";
    cout << "*******************************************\n\n";*/

    if (node != NULL)
    {
        GetDataEmployee(node->left);
        PrintData(node);
        GetDataEmployee(node->right);
    }
}

void PrintData(No *node)
{
    cout << "-------------------------------------------" << endl;
    cout << "Matricula: " << node->info.registration << endl;
    cout << "Nome: " << node->info.name << endl;
    cout << "Cpf: " << node->info.cpf << endl;
    cout << "Cargo: " << node->info.role << endl;
    cout << "Telefone: " << node->info.telephone << endl;
    cout << "Data de nascimento: " << node->info.birthDate.day << "/" << node->info.birthDate.month << "/"
         << node->info.birthDate.year << endl;
    cout << "Endereço" << endl;
    cout << "Rua: " << node->info.address.street << endl;
    cout << "Número: " << node->info.address.number << endl;
    cout << "Bairro: " << node->info.address.district << endl;
    cout << "Cidade: " << node->info.address.city << endl;
    cout << "Estado: " << node->info.address.state << endl;
    cout << "Cep: " << node->info.address.zipCode << endl;
    cout << "-------------------------------------------" << endl
         << endl;
}