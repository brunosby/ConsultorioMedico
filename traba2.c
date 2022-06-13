#include <stdio.h>
#include "medico.h"
#include "paciente.h"
#include "consulta.h"

int main()
{
    int op;
    /*
    Será escolhido algumas das opções abaixo através do valor na variável op inserida, caso o valor inserido seja 1 será executado
    a função cadastrar_medico, caso o valor inserido seja 2 será executado a função listar_medicos e assim por diante. Para finalizar o programa
    será necessário degitar o valor 0.
    Caso seja inserido um valor negativo ou maior que 6, será considerado um erro e será necessário digitar novamente até
    o valor ser uma das opções de 0 a 6.
    */
    do {
        printf("\nCONSULTORIO MEDICO\n");
        printf("<1> Cadastrar um medico\n");
        printf("<2> Listar todos os medicos\n");
        printf("<3> Cadastrar um paciente\n");
        printf("<4> Listar todos os pacientes\n");
        printf("<5> Cadastrar uma consulta\n");
        printf("<6> Listar as consultas de um medico\n");
        printf("<0> Sair do programa\n");
        printf("Opcao: ");
        scanf("%d", &op);
        switch (op) {
            case 1:
                cadastrar_medico();
                break;
            case 2:
                listar_medicos();
                break;
            case 3:
                cadastrar_paciente();
                break;
            case 4:
                listar_pacientes();
                break;
            case 5:
                cadastrar_consulta();
                break;
            case 6:
                listar_consultas();
                break;
            case 0:
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (op != 0);
    return 0;
}