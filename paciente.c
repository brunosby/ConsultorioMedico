#include "paciente.h"
#include <stdio.h>
#define ARQ_PACIENTE "paciente.dat"

void cadastrar_paciente()
{   
    paciente pacientes;
    FILE * arq;

    /*
    Será aberto o arquivo paciente.dat para escrita no final do arquivo, caso não for possível a abertura será mostrado uma menságem de erro
    no vídeo e retornará para o main.
    */
    if ((arq = fopen(ARQ_PACIENTE, "ab")) == NULL){
        fprintf(stderr, "\nErro na abertura do arquivo %s!\n", ARQ_PACIENTE);
        return;
    }
    /*
    O ponteiro é direcionado para o final do arquivo paciente.dat, sendo informado a posição em byte e dividido pelo tamanho da estrutura 
    paciente em bytes para obter a quantidade de paciente já cadastrado, e somando o valor 1 para gerar um código não repetitivo.
    Após isso é informado as informações do paciente e armazenado na estrutura, apenas no sexo será realizado um teste para verificar se a letra
    informada é M ou F que representa o masculino e feminino, caso não for nenhum dos casos será feito um pedido para inserir uma letra válida.
    Ao informar todas as informações do paciente, será escrito as informações, armazenados na estrutura, no final do arquivo paciente.dat 
    e será fechando o arquivo.
    */
    fseek(arq, 0, SEEK_END);
    pacientes.cod_paciente = ftell(arq) / sizeof(paciente) + 1;
    printf("\nNovo Paciente\n");
    printf("Codigo do Paciente: %d\n", pacientes.cod_paciente);
    printf("Nome do Paciente: ");
    scanf(" %40[^\n]", pacientes.nome);
    printf("Sexo do Paciente (M|F): ");
    scanf(" %c", &pacientes.sexo);
    pacientes.sexo = toupper(pacientes.sexo);
    while(pacientes.sexo != 'M' && pacientes.sexo != 'F'){
        printf("Erro: sexo invalido!\n");
        printf("Sexo do Paciente (M|F): ");
        scanf(" %c", &pacientes.sexo);
        pacientes.sexo = toupper(pacientes.sexo);
    }
    printf("Idade do Paciente: ");
    scanf(" %d", &pacientes.idade);
    fwrite(&pacientes, sizeof(paciente), 1, arq);
    fclose(arq);
    printf("\nPaciente cadastrado com sucesso!\n");
}


void listar_pacientes()
{
    paciente pacientes;
    FILE * arq;

    // O mesmo esquema realizado na função cadastrar_paciente é realizado para abrir o arquivo paciente.dat para a leitura.
    if((arq = fopen(ARQ_PACIENTE, "rb")) == NULL){
        fprintf(stderr, "\nNao ha nenhum paciente cadastrado!\n");
        return;
    }
    /*
    Será percorrido os dados dos arquivos paciente.dat para imprimir todos os pacientes cadastrados no arquivo, após a impressão o arquivo
    será fechado.
    */
    printf("\n\n\tListar Pacientes\n");
    printf("------------------------------------------\n");
    printf("#Codigo  Nome do Paciente   Sexo   Idade\n");
    printf("------------------------------------------\n");
    while(fread(&pacientes, sizeof(paciente), 1, arq) > 0){
        printf("%06d   %-20.20s %c    %03d\n", pacientes.cod_paciente, pacientes.nome, pacientes.sexo, pacientes.idade);
    }
    printf("------------------------------------------\n");
    fclose(arq);
}
