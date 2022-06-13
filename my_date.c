#include "my_date.h"
#include <stdio.h>

// Nesse arquivo são definidos funções para facilitar a escrita e leitura do código principal.

void imprime_data(data d)
{
    printf("%02d/%02d/%4d", d.dia, d.mes, d.ano);
}

void imprime_horario(horario h)
{
    printf("%02d:%02d", h.horas, h.minutos);
}

void imprime_data_horario(data d, horario h)
{
    imprime_data(d);
    printf(" - ");
    imprime_horario(h);
}

void le_data(const char * msg, data * d)
{
    printf("%s (dd/mm/aaaa): ", msg);
    scanf("%d/%d/%d", &d->dia, &d->mes, &d->ano);
}

void le_horario(const char * msg, horario * h)
{
    printf("%s (hh:mm): ", msg);
    scanf("%d:%d", &h->horas, &h->minutos);
}

void le_data_horario(const char * msg, data * d, horario * h)
{
    printf("%s (dd/mm/aaaa hh:mm): ", msg);
    scanf("%d/%d/%d", &d->dia, &d->mes, &d->ano);
    scanf("%d:%d", &h->horas, &h->minutos);
}

int compara_data(data d1, data d2)
{
    return data_to_aaaammdd(d1) - data_to_aaaammdd(d2);
}

int compara_horario(horario h1, horario h2)
{
    return horario_to_minutos(h1) - horario_to_minutos(h2);
}

int compara_data_horario(data d1, horario h1, data d2, horario h2)
{
    int dt = compara_data(d1, d2);
    if (dt != 0) {
        return dt;
    }
    return compara_horario(h1, h2);
}