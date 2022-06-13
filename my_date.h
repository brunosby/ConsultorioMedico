#ifndef _MY_DATE_H
#define _MY_DATE_H

// É definido 2 estruturas representado as datas e horários.
typedef struct {
    int dia;
    int mes;
    int ano;
} data;

typedef struct {
    int horas;
    int minutos;
} horario;

/* funções para impressão de data e horário */
void imprime_data(data);
void imprime_horario(horario);
void imprime_data_horario(data, horario);

/* funções para a entrada de data e horário */
void le_data(const char *, data *);
void le_horario(const char *, horario *);
void le_data_horario(const char *, data *, horario *);

/* funções de comparação de data e horário */
int compara_data(data, data);
int compara_horario(horario, horario);
int compara_data_horario(data, horario, data, horario);

/* macros auxiliares */
/* transforma a data em um número no formato aaaammdd 
 * 27/05/2021 = 2021 * 10000 + 5 * 100 + 27 = 20210000 + 500 + 27 = 20210527 */
#define data_to_aaaammdd(dt) (dt.ano * 10000 + dt.mes * 100 + dt.dia)
/* transforma o horario em minutos
 * 9:30 = 9 * 60 + 30 = 540 + 30 = 570 */
#define horario_to_minutos(h) (h.horas * 100 + h.minutos)

#endif