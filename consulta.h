#ifndef _CONSULTA_H
#define _CONSULTA_H

//stdbool será utilizado para retornar a resposta da função valida_data_horario
#include "my_date.h"
#include "paciente.h"
#include "medico.h"
#include <stdbool.h>

// É definido uma esstrutura que será conter informações de um consulta, será utilziado para guardar informações para salvar dentro do arquivo.
typedef struct {
    int num_prontuario;
    data data_consulta;
    horario hora_consulta;
    int cod_medico;
    int cod_paciente;
} consulta;


/* função para cadastrar uma consulta no arquivo consulta.dat*/
void cadastrar_consulta();

/* função para mostrar as consultas de um medico numa data/horario e caso desejar, gerar um arquivo texto*/
void listar_consultas();

/* função que valida a data e o horário de todas as consulta cadastradas para um mesmo médico*/
static bool valida_data_horario(consulta);

#endif