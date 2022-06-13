#ifndef _MEDICO_H
#define _MEDICO_H

// É definida uma estrutura medico, contendo um código que irá representar o medico, o nome e especialidade do médico.
typedef struct {
    int cod_medico;
    char nome[41];
    char especialidade[31];
} medico;

/* função para cadastrar um novo medico no arquivo medico.dat*/
void cadastrar_medico();

/* função para listar todos os médicos cadastrados no arquivo medico.dat*/
void listar_medicos();

#endif