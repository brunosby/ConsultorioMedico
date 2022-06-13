#include "medico.h"
#include <stdio.h>
#define ARQ_MEDICO "medico.dat"

void cadastrar_medico()
{
    medico medicos;
    FILE * arq;
    /*
    O arquivo medico.dat será aberto para a escrita no final do arquivo. Caso a abertura do arquivo não for possível, será informado uma menságem
    de erro e será direcionado para o main.
    */
    if ((arq = fopen(ARQ_MEDICO, "ab")) == NULL){
        fprintf(stderr, "\nErro na abertura do arquivo %s!\n", ARQ_MEDICO);
        return;
    }
    /*
    O ponteiro será direcionado para o final do arquivo medico.dat, informando a posição final em bytes e dividido pelo tamanho da estrutura
    medico para obter a quantidade de médicos cadastrados no arquivo, assim somando o valor 1 para gerar um número de código não repetitivo.
    As informações inseridas será armazenado temporariamente na estrutura medico. Após a inserção dos dados necessários será escrito no final
    do arquivo medico.dat e assim sendo fechado o arquivo.
    */
    fseek(arq, 0, SEEK_END);
    medicos.cod_medico = ftell(arq) / sizeof(medico) + 1;
    printf("\nNovo Medico\n");
    printf("Codigo do Medico: %d\n", medicos.cod_medico);
    printf("Nome do Medico: ");
    scanf(" %40[^\n]", medicos.nome);
    printf("Especialidade do Medico: ");
    scanf(" %30[^\n]", medicos.especialidade);
    fwrite(&medicos, sizeof(medico), 1, arq);
    fclose(arq);
    printf("\nMedico cadastrado com sucesso!\n");
}


void listar_medicos()
{
    medico medicos;
    FILE * arq;
    // O mesmo esquema realizado para a abertura do arquivo utilizado na função cadastrar_medico é realizado, mas para a leitura do arquivo.
    if((arq = fopen(ARQ_MEDICO, "rb")) == NULL){
        fprintf(stderr, "\nNao ha nenhum medico cadastrado!\n");
        return;
    }
    /*
    Será percorrido todos os médicos já cadastrados para que seja impresso as informações no vídeo, após isso será fechado o arquivo.
    */
    printf("\n\n\tListar Medicos\n");
    printf("-------------------------------------------\n");
    printf("#Codigo  Nome do Medico       Especialidade\n");
    printf("-------------------------------------------\n");
    while(fread(&medicos, sizeof(medico), 1, arq) > 0){
        printf("%06d   %-20.20s %-20.20s\n", medicos.cod_medico, medicos.nome, medicos.especialidade);
    }
    printf("------------------------------------------\n");
    fclose(arq);
}
