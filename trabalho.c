#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIM_STR "|"
#define COMP_REG 64

struct
{
    int cont_reg;
} cab;

void importacao(char argv[]);
int le_campos(char buffer[], int size, FILE *entrada);

int main(int argc, char *argv[])
{

    if (argc == 3 && strcmp(argv[1], "-i") == 0)
    {

        printf("Modo de importacao ativado ... nome do arquivo = %s\n", argv[2]);
        importacao(argv[2]);
    }
    else if (argc == 3 && strcmp(argv[1], "-e") == 0)
    {

        printf("Modo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);
        // executa_operacoes(argv[2]);
    }
    else if (argc == 2 && strcmp(argv[1], "-p") == 0)
    {

        printf("Modo de impressao da PED ativado ...\n");
        // imprime_ped();
    }
    else
    {
        fprintf(stderr, "Argumentos incorretos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s (-i|-e) nome_arquivo\n", argv[0]);
        fprintf(stderr, "$ %s -p\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}

void importacao(char argv[])
{
    FILE *entrada;
    FILE *saida;
    char campo[COMP_REG + 1];
    char buffer[COMP_REG + 1];
    int cont = 0;

    entrada = fopen(argv, "r");

    while (le_campos(campo, COMP_REG, entrada) > 0)
    {
        strcpy(buffer, campo);
        strcpy(buffer, "|");
        cont++;
        
        printf("campo #%i: %s\n", cont, campo);
    }

    fclose(entrada);
    fclose(saida);
}

int le_campos(char campo[], int size, FILE *entrada)
{
    int i = 0;
    char c = fgetc(entrada);

    while (c != EOF && c != '|')
    {
        if (i <= size - 1)
        {
            campo[i] = c;
            i++;
        }
        c = fgetc(entrada);
    }
    campo[i] = '\0';
    return i;
}

void campos()
{

}