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
    char street[31];
    int number;
    char district[21];
    char city[21];
    char state[3];
    char zipCode[10];
};

typedef struct Info
{
    int registration;
    char cpf[15];
    char name[51];
    char role[31];
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

No *root = NULL; // Nó raiz
No *treebycpf = NULL;
No *treebyname = NULL;

void MainMenu(); // Menu principal do programa para a escolha das opcoes

void SearchMenu(); // Função para escolha da opção de pesquisa, se é por cpf ou por nome

void SearchHeader(int option); // Função para exibir os cabeçalhos do tipo de pesquisa

void SearchEmployee(int option); // Função para o controle da pesquisa, indicando qual operação será executada

No *SearchEmployeeCpf(No *treeByCpf, char cpf[]); // Função que percorre a arvore procurando pelo cpf do funcionário

No *SearchEmployeeName(No *treeByName, char name[]); // Função que percorre a arvore procurando pelo nome do funcionário

void Register(); // Função para cadastrar os dados do funcionário da struct

int AddEmployeeByCpf(Info empInfo); // Função que insere o funcionário na árvore binária pela ordem do cpf

void RemoveEmployee(); // Função que le qual funcionário será removido

int Remove(int registration); // Função que remove da árvore binária

void PrintMenu(); // Função do menu do tipo de impressão dos dados

void PrintHeader(int option); // Função para exibir os cabeçalhos do tipo de impressão

void PrintOrder(int option); // Função para controle de qual ordem será imprimido os dados dos funcionários

void InOrder(No *node); // Função para imprimir os dados em ordem

void PreOrder(No *node); // Função para imprimir os dados em Pre ordem

void PostOrder(No *node); // Função para imprimir os dados em Pós ordem

void PrintData(No *node); // Função que imprimi os dados encontrados do funcionário

// implementação das funções
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

        if (option < 1 || option > 3) // condição caso seja digitado um valor inválido
        {
            system("cls");
            cout << "Opção inválida!" << endl;
            Sleep(1500);
            system("cls");
        }
        else if (option == 1 || option == 2)
        {
            SearchEmployee(option); // passando a opção escolhida para a função Search
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
        break;
    }
}

void SearchEmployee(int option)
{
    char cpf[15];      // variável para guardar o cpf do funcionário para a buscar
    char name[51];     // variável para guardar o nome do funcionário para buscar
    No *result = NULL; // ponteiro para receber a referência da função SearchEmployeeCpf e SearchEmployeeName

    switch (option)
    {
    case 1:
        SearchHeader(1); // função do cabeçalho da pesquisa
        cout << "Informe o cpf: ";
        cin.ignore();
        cin.get(cpf, 15);                           // lendo o valor do cpf para busca
        result = SearchEmployeeCpf(treebycpf, cpf); // guardando a referência do resultado da busca

        if (result != NULL) // condição para verificar se encontrou o funcionário
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
        SearchHeader(2); // função do cabeçalho da pesquisa
        cout << "Informe o nome: ";
        cin.ignore();
        cin.get(name, 51);                             // lendo o valor do nome para busca
        result = SearchEmployeeName(treebyname, name); // guardando a referência do resultado da busca

        if (result != NULL) // condição para verificar se encontrou o funcionário
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
        break;
    }
}

No *SearchEmployeeCpf(No *treeByCpf, char cpf[])
{
    if (treeByCpf != NULL)
    {
        if (strcmp(cpf, treeByCpf->info.cpf) == 0) // compara os valores do cpf, se for 0 são iguais
        {
            return treeByCpf; // retorna a referência
        }
        else if (strcmp(cpf, treeByCpf->info.cpf) < 0) // compara os valores do cpf, se for menor que 0, a primeira
                                                       // string é menor que a segunda
        {
            return SearchEmployeeCpf(treeByCpf->left, cpf); // chama a função recursivamente indo para a esquerda da árvore
        }
        else if (strcmp(cpf, treeByCpf->info.cpf) > 0) // compara os valores do cpf, se for maior que 0, a primeira
                                                       // string é maior que a segunda
        {
            return SearchEmployeeCpf(treeByCpf->right, cpf); // chama a função recursivamente indo para a direita da árvore
        }
    }
    return NULL; // retorna null se não encontrar nada
}

No *SearchEmployeeName(No *treeByName, char name[])
{
    while (treeByName != NULL)
    {
        if (strcmp(name, treeByName->info.name) == 0) // compara os valores do nome, se for 0 são iguais
        {
            return treeByName; // retorna a referência
        }
        else if (strcmp(name, treeByName->info.name) < 0) // compara os valores do nome, se for menor que 0, a primeira
                                                          // string é menor que a segunda
        {
            return SearchEmployeeName(treeByName->left, name); // chama a função recursivamente indo para a esquerda da árvore
        }
        else if (strcmp(name, treeByName->info.name) > 0) // compara os valores do nome, se for maior que 0, a primeira
                                                          // string é maior que a segunda
        {
            return SearchEmployeeName(treeByName->right, name); // chama a função recursivamente indo para a direita da árvore
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
    cin.get(empInfo.cpf, 15); // lendo o cpf

    cout << "\nInforme o nome: ";
    cin.ignore();
    cin.get(empInfo.name, 51); // lendo o nome

    cout << "\nInforme o cargo: ";
    cin.ignore();
    cin.get(empInfo.role, 31); // lendo o cargo

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
    cin.get(empInfo.address.street, 31); // lendo a rua

    cout << "Número: ";
    cin >> empInfo.address.number; // lendo o número

    cout << "Bairro: ";
    cin.ignore();
    cin.get(empInfo.address.district, 21); // lendo o bairro

    cout << "Cidade: ";
    cin.ignore();
    cin.get(empInfo.address.city, 21); // lendo a cidade

    cout << "Estado (somente a sigla): ";
    cin.ignore();
    cin.get(empInfo.address.state, 3); // lendo o estado

    cout << "Cep: ";
    cin.ignore();
    cin.get(empInfo.address.zipCode, 10); // lendo o cep

    // retornando mensagem se foi possivel adicionar o funcionário na árvore ou não
    if (AddEmployeeByCpf(empInfo) == 1)
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

int AddEmployeeByCpf(Info empInfo)
{
    No *newNode = new No;
    newNode->info = empInfo;
    newNode->left = NULL;
    newNode->right = NULL;

    if (treebycpf == NULL)
    {
        treebycpf = newNode;

        return 1;
    }

    No *current = treebycpf;
    No *previous = NULL;

    // inserindo na arvore comparando pelo cpf do funcionário
    while (current != NULL)
    {
        previous = current;
        if (strcmp(empInfo.cpf, current->info.cpf) < 0) // compara os valores do cpf, se for menor que 0, a primeira
                                                        // string é menor que a segunda
        {
            current = current->left;
        }
        else if (strcmp(empInfo.cpf, current->info.cpf) > 0) // compara os valores do cpf, se for maior que 0, a primeira
                                                             // string é maior que a segunda
        {
            current = current->right;
        }
    }

    if (strcmp(empInfo.cpf, previous->info.cpf) < 0) // compara os valores do cpf, se for menor que 0, a primeira
                                                     // string é menor que a segunda
    {
        previous->left = newNode;
    }
    else if (strcmp(empInfo.cpf, previous->info.cpf) > 0) // compara os valores do cpf, se for maior que 0, a primeira
                                                          // string é maior que a segunda
    {
        previous->right = newNode;
    }
    else
    {
        return -1;
    }
    return 1;
}

// PARA REMOVER PODE SER PELO CPF, DEPOIS CRIA UMA FUNÇÃO QUE ASSIM QUE REMOVER PEGAR OS DADOS DO FUNCIONARIO
// E PASSAR O NOME PARA OUTRA FUNÇÃO QUE REMOVE PELO NOME
void RemoveEmployee()
{
    system("cls");

    int registration; // variável para guardar o valor da matricula do funcionário para remover

    cout << "******************************************\n";
    cout << "*           REMOVE FUNCIONÁRIO           *\n";
    cout << "******************************************\n\n";

    cout << "Informe o número de matricula: ";
    cin >> registration; // lendo a matricula

    // retornando mensagem se foi possivel remover o funcionário da árvore ou não
    if (Remove(registration) == 1)
    {
        cout << "\nFuncionário removido com sucesso!" << endl;
        Sleep(1500);
    }
    else
    {
        cout << "\nNão foi possivel remover." << endl;
        Sleep(1500);
    }
}

int Remove(int registration)
{
    No *current = root;
    No *previous = NULL;
    No *successor = NULL;
    No *successor_previous = NULL;
    int retorno = 0;

    // removendo o funcionário comparando pelo número de matricula
    while (current != NULL)
    {
        {
            if (registration == current->info.registration)
            {   
                // salvar em um ponteiro os dados e passar para a outra função do nome
                // e também comparar se deu retorno positivo, se der ai o retorno = 1 e boa
                retorno = 1;
                break;
            }
            else if (registration < current->info.registration)
            {
                previous = current;
                current = current->left;
            }
            else
            {
                previous = current;
                current = current->right;
            }
        }
    }
    if (current == NULL)
        return 0;
    if (current->left == NULL && current->right == NULL)
    {
        if (previous == NULL)
        {
            root = NULL;
        }
        else if (previous->left == current)
        {
            previous->left = NULL;
        }
        else
        {
            previous->right = NULL;
        }
        delete current;
    }
    else if (current->left == NULL)
    {
        successor = current->right;
        if (previous == NULL)
        {
            root = successor;
        }
        else if (previous->left == current)
        {
            previous->left = successor;
        }
        else
        {
            previous->right = successor;
        }
        delete current;
    }
    else if (current->right == NULL)
    {
        successor = current->left;
        if (previous == NULL)
        {
            root = successor;
        }
        else if (previous->left == current)
        {
            previous->left = successor;
        }
        else
        {
            previous->right = successor;
        }
        delete current;
    }
    else
    {
        successor_previous = current;
        successor = current->right;
        while (successor->left != NULL)
        {
            successor_previous = successor;
            successor = successor->left;
        }
        current->info.registration = successor->info.registration; // talvez pegar so a struct sem o .
        if (successor_previous == current)
        {
            successor_previous->right = successor->right;
        }
        else
            successor_previous->left = successor->right;
        delete successor;
    }
    return retorno;
}

void PrintMenu()
{
    int option = 0; // variavel para escolha da opção de imprimir os dados
    do
    {
        system("cls");

        cout << "********************************************\n";
        cout << "*        IMPRIMIR DADOS FUNCIONÁRIO        *\n";
        cout << "********************************************\n\n";
        cout << "1 - Em Ordem\n2 - Pré Ordem\n3 - Pós Ordem\n4 - Cancelar\n\nEscolha uma opção: ";
        cin >> option;

        if (option < 1 || option > 4) // condição caso seja digitado um valor inválido
        {
            system("cls");
            cout << "Opção inválida!" << endl;
            Sleep(1500);
            system("cls");
        }
        else if (option > 0 || option < 4)
        {
            PrintOrder(option); // passando a opção escolhida para a função PrintOrder
        }

    } while (option != 4);
}

void PrintHeader(int option)
{
    system("cls");

    switch (option)
    {
    case 1:
        cout << "*****************************************\n";
        cout << "*          IMPRIMINDO EM ORDEM          *\n";
        cout << "*****************************************\n\n";
        break;
    case 2:
        cout << "*********************************************\n";
        cout << "*          IMPRIMINDO EM PRE ORDEM          *\n";
        cout << "*********************************************\n\n";
        break;
    case 3:
        cout << "*********************************************\n";
        cout << "*          IMPRIMINDO EM PÓS ORDEM          *\n";
        cout << "*********************************************\n\n";
    default:
        break;
    }
}

void PrintOrder(int option)
{
    switch (option)
    {
    case 1:
        PrintHeader(1);     // função do cabeçalho para impressão dos dados
        InOrder(treebycpf); // Passando a raiz para imprimir em ordem
        system("pause");
        break;
    case 2:
        PrintHeader(2);      // função do cabeçalho para impressão dos dados
        PreOrder(treebycpf); // Passando a raiz para imprimir em pre ordem
        system("pause");
        break;
    case 3:
        PrintHeader(3);       // função do cabeçalho para impressão dos dados
        PostOrder(treebycpf); // Passando a raiz para imprimir em pós ordem
        system("pause");
        break;
    default:
        break;
    }
}

void InOrder(No *node)
{
    if (node != NULL)
    {
        InOrder(node->left);
        PrintData(node); // passando o nó para a função PrintData para exibição dos dados
        InOrder(node->right);
    }
}

void PreOrder(No *node)
{
    if (node != NULL)
    {
        PrintData(node); // passando o nó para a função PrintData para exibição dos dados
        PreOrder(node->left);
        PreOrder(node->right);
    }
}

void PostOrder(No *node)
{
    if (node != NULL)
    {
        PostOrder(node->left);
        PostOrder(node->right);
        PrintData(node); // passando o nó para a função PrintData para exibição dos dados
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