#include "consulta.h"
#include <stdio.h>
/*
Será definido o nome do arquivo como ARQ_NOME.
Sendo NOME = nome que se refere aos dados armazenados.
*/
#define ARQ_CONSULTA "consulta.dat"
#define ARQ_MEDICO "medico.dat"
#define ARQ_PACIENTE "paciente.dat"

void cadastrar_consulta()
{
    int cod_medico, cod_paciente, num_medico, num_paciente, sair;
    consulta consultas;
    medico medicos;
    paciente pacientes;

    /*
    São abertos todos os arquivos que são utilizados posteriormente, caso houver algum erro na abertura do arquivo será mostrado uma mensagem
    de erro na tela e será direcioando para a main. Caso já houver algum arquivo aberto será fechado.
    */
    FILE * medicod, * paciented, * arq;
    if((medicod = fopen(ARQ_MEDICO, "rb")) == NULL){
        fprintf(stderr,"\nNao ha nenhum Medico cadastrado!\n");
        return;
    }
    if((paciented = fopen(ARQ_PACIENTE, "rb")) == NULL){
        fprintf(stderr, "\nNao ha nenhum Paciente cadastrado!\n");
        fclose(medicod);
        return;
    }
    if((arq = fopen(ARQ_CONSULTA, "ab")) == NULL){
        fprintf(stderr, "\nErro na abertura do arquico %s", ARQ_CONSULTA);
        fclose(medicod);
        fclose(paciented);
        return;
    }
    /*
    O ponteiro do tipo file é posicionado para o final do arquivo consulta.dat. A variavel num_prontuario que está dentro da estrutura consultas
    receberá o valor da posição do ponteiro em bytes e será dividido pelo tamanho da estrutura consulta e bytes, assim terá os números de dados
    armazenados, somando 1 será possível criar um número de prontuário o novo cadastro realizado.
    */
    fseek(arq, 0, SEEK_END);
    consultas.num_prontuario = ftell(arq) / sizeof(consulta) + 1;
    printf("\nNova Consulta\n");
    printf("Numero do Prontuario: %d\n", consultas.num_prontuario);

    /*
    Escolhe o médico que irá consultar, o mesmo esquema realizado para gerar o numero de prontuario da consulta será feito para o arquivo
    medico.dat para conseguir saber quantos médicos estão cadastrados, assim será escolhido através da variável cod_medico.
    Caso não existir será necessário digitar novamente, ou -1 para cancelar e retornar para main.
    */
    fseek(medicod, 0, SEEK_END);
    num_medico = ftell(medicod) / sizeof(medico);
    printf("Insira o codigo do Medico (1 a %d): ", num_medico);
    scanf("%d", &cod_medico);
    while(cod_medico < 1 || cod_medico > num_medico){
        printf("Erro: codigo inválido!\n");
        printf("Insira o codigo do Medico (1 a %d ou -1 para cancelar): ", num_medico);
        scanf("%d", &cod_medico);
        if(cod_medico == -1){
            return;
        }
    }
    /*
    Procura o nome do médico através do cod_medico inserido anteriormente, nesse momento os dados desse médico é inserido na estrutura
    médico para isso ser possível.
    */
    fseek(medicod, (cod_medico - 1) * sizeof(medico), SEEK_SET);
    fread(&medicos, sizeof(medico), 1, medicod);
    consultas.cod_medico = cod_medico;
    printf(" Nome do Medico: %s\n", medicos.nome);

    //escolhe o paciente que irá ser conultado, da mesma forma que o médico.
    fseek(paciented, 0, SEEK_END);
    num_paciente = ftell(paciented) / sizeof(paciente);
    printf("Insira o codigo do Paciente (1 a %d): ", num_paciente);
    scanf("%d", &cod_paciente);
    while(cod_paciente < 1 || cod_paciente > num_paciente){
        printf("Erro: codigo inválido!\n");
        printf("Insira o codigo do Paciente (1 a %d ou -1 para cancelar): ", num_paciente);
        scanf("%d", &cod_paciente);
        if(cod_paciente == -1){
            return;
        }
    }

    //O mesmo que foi realizado com o médico está sendo executado para o paciente
    fseek(paciented, (cod_paciente - 1) * sizeof(paciente), SEEK_SET);
    fread(&pacientes, sizeof(paciente), 1, paciented);
    consultas.cod_paciente = cod_paciente;
    printf("Nome do paciente: %s\n", pacientes.nome);

    /*
    Escolhe a data e horario da conulta com a função le_data_horario e é armazenado na estrutura consulta.
    Após a inserção dos horários, é testado se tem algum cadastro realizado com os mesmos horários para o mesmo médico através da função
    valida horario. Caso houver algum cadastro será possível escolehr se deseja proceguir, digitando número qualquer, ou sair do programa,
    digitando -1.
    Após o cadastro, as informações são salvas no arquivos consulta.dat, e são fechados os arquivos para finalizar o cadastro.
    */
            le_data_horario("Informe a data e horario da consulta", 
                                 &consultas.data_consulta, 
                                 &consultas.hora_consulta);
                while (!valida_data_horario(consultas)) {
                    printf("Erro: ja' existe uma consulta para este medico ou paciente neste horario!\n");
                    printf("Digite -1 p/ encerrar: ");
                    scanf("%d", &sair);
                    if (sair == -1) {
                        return;
                    }                    
                    le_data_horario("Informe a data e horario da consulta", &consultas.data_consulta, &consultas.hora_consulta);
                }

                fwrite(&consultas, sizeof(consulta), 1, arq);
                fclose(arq);
                fclose(medicod);
                fclose(paciented);
                printf("\nConsulta cadastrada com sucesso!\n");

}

void listar_consultas()
{
    FILE * medicod, * paciented, * arq, *textod;
    consulta consultas;
    data dt;
    medico medicos;
    paciente pacientes;
    int cod_medico, n_medicos, escolha;

    //O mesmo método para abrir os arquivos utilizados em cadastrar_consulta é realizado.
    if ((arq = fopen(ARQ_CONSULTA, "rb")) != NULL){
        
        if((medicod = fopen(ARQ_MEDICO, "rb")) == NULL){ 
            fprintf(stderr, "\nErro na abertura do arquivo %s\n", ARQ_MEDICO);
            fclose(arq);
            return;
        }
    
        if((paciented = fopen(ARQ_PACIENTE, "rb")) == NULL){ 
            fprintf(stderr, "\nErro na abertura do arquivo\n");
            fclose(arq);
            fclose(medicod);
            return;
        }

        // O mesmo método para obter a quantidade de médicos cadastrados é realizado. 
        fseek(medicod, 0, SEEK_END); 
        n_medicos = ftell(medicod)/sizeof(medico);

        /*
        É inserido o cod_medico para listar as consultas de determinado médico já cadastrado. Caso esse código não exista será possível escolher
        entre cancelar o processo digitando -1, ou continuar digitando um código válido.
        */
        printf("\nConsultas de um medico\n");
        printf("Codigo do medico (1 a %d): ", n_medicos);
        scanf("%d", &cod_medico);
        while (cod_medico < 1 || cod_medico > n_medicos) {
            printf("Erro: codigo invalido!\n");
            printf("Codigo do medico (1 a %d ou -1 p/ cancelar): ", n_medicos);
            scanf("%d", &cod_medico);
            if (cod_medico == -1) {
                return;
            }
        }
        /*
        Será inserido as datas de consultas para que seja possível listar apenas as consultas que tem na data inserida.
        O arquivo consulta.dat será percorrido, para cada consulta será testado se o código do médico é o mesmo que foi inserido anteriormente
        e se a data inserida é a mesma que a data cadastrada, através da função compara_data.
        Caso sejam os mesmos, será listado.
        */
        fseek(medicod, (cod_medico - 1) * sizeof(medico), SEEK_SET);
        fread(&medicos, sizeof(medico), 1, medicod);
        printf("Nome do medico: %s\n", medicos.nome);
        le_data("Data das consultas", &dt);
        printf("\nConsultas de %s no dia ", medicos.nome);
        imprime_data(dt);
        printf("\n-----------------------------------\n");
        printf("#Pront. Paciente            Horario\n");
        printf("-----------------------------------\n");
        while (fread(&consultas, sizeof(consulta), 1, arq) > 0) {
            if (consultas.cod_medico == cod_medico 
                && compara_data(consultas.data_consulta, dt) == 0) {
                    fseek(paciented, (consultas.cod_paciente - 1) * sizeof(paciente), SEEK_SET);
                    fread(&pacientes, sizeof(paciente), 1, paciented);
                    printf("%06d  %-20.20s ", consultas.num_prontuario,
                    pacientes.nome);
                    imprime_horario(consultas.hora_consulta);
                    printf("\n");
                }
        }  
        printf("-----------------------------------\n");
        /*
        O usuário irá escolher se deseja produzir um arquivo do tipo texto com as consultas mostradas.
        */
        printf("Deseja gerar um arquivo com essas informacoes ? (1-sim, 0-nao): ");
        scanf(" %d", &escolha);
        while(escolha != 0 && escolha != 1){
            printf("Numero invalido, digite novamente (1-sim, 0-nao): ");
            scanf(" %d", &escolha);
        }
        /*
        O método para preencher as informações no arquivo do tipo texto são similares método utilizado para listar, a diferença é que a saída
        das informações será o arquivo consultas.txt e não um vídeo.
        Após a finalização será fechado todos os arquivos utilizados.
        */
        if(escolha == 1){
            if((textod = fopen("consultas.txt", "w")) == NULL){
                fprintf(stderr, "Nao foi possivel criar o arquivo!\n");
                return;
            }
            rewind(arq);
            fprintf(textod, "------------------------------------\n");
            fprintf(textod, "#Pront. Paciente            Horario\n");
            fprintf(textod, "------------------------------------\n");
            while (fread(&consultas, sizeof(consulta), 1, arq) > 0) {
            if (consultas.cod_medico == cod_medico 
                && compara_data(consultas.data_consulta, dt) == 0) {
                    fseek(paciented, (consultas.cod_paciente - 1) * sizeof(paciente), SEEK_SET);
                    fread(&pacientes, sizeof(paciente), 1, paciented);
                    fprintf(textod, "%06d  %-20.20s ", consultas.num_prontuario,
                    pacientes.nome);
                    fprintf(textod, "%02d:%02d\n", consultas.hora_consulta.horas, consultas.hora_consulta.minutos);
                    printf("\n");
                }
            }
            fprintf(textod, "------------------------------------\n");
            printf("Arquivo preenchido com sucesso !\n");
            fclose(textod);
        }
        fclose(arq);
        fclose(medicod);
        fclose(paciented);
    } else {
        printf("\nErro: nao ha' nenhuma consulta cadastrada!\n");
    } 
}            
 

static bool valida_data_horario(consulta c)
{
    FILE * arq;
    consulta consultas;

    /*
    Será percorrido todas as consultas cadastradas no arquivo consulta.dat para validar se já existe consultas nas mesmas datas e horários
    para o mesmo médico, caso existir será retornado falso, caso contrário será retornado verdadeiro.
    */
    if((arq = fopen(ARQ_CONSULTA, "rb")) != NULL){ 
        while ((fread(&consultas, sizeof(consulta), 1, arq)) > 0) {
            if ((consultas.cod_medico == c.cod_medico || consultas.cod_paciente == c.cod_paciente) 
                && compara_data_horario(consultas.data_consulta, consultas.hora_consulta,
                                        c.data_consulta, c.hora_consulta) == 0) {
                fclose(arq);
                return false;
            }
        }
        fclose(arq);
        return true;
    }
    
    else{
        fprintf(stderr, "\nErro na abertura do arquivo\n");
    }

   
} 