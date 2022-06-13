#ifndef _PACIENTE_H
#define _PACIENTE_H

//ctype será utilizado para transformar a letra que representará o sexo do paciente, em maiúscula.
#include <ctype.h>

// É definida uma estrutura paciente contendo o código que irá representar o paciente, nome, sexo, idade, sendo as informações do paciente.
typedef struct {
    int cod_paciente;
    char nome[41];
    char sexo;
    int idade;
} paciente;

/* função para cadastrar um paciente no arquivo paciente.dat*/
void cadastrar_paciente();

/* função para listar todos os pacientes cadastrados no arquivo paciente.dat*/
void listar_pacientes();

#endif