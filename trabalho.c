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
    int i, byte_offset, cont = 1;

    entrada = fopen(argv, "r");
    saida = fopen("dados.dat", "w+b");

    while (cont > 0)
    {
        buffer[0] = '\0';
        for(i = 0; i < 4; i++)
        {
            cont = le_campos(campo, COMP_REG, entrada);
            if(cont != 0)
            {
                strcat(buffer, campo);
                strcat(buffer, "|");
            }
        }
        i = 0;
        
        byte_offset = cab.cont_reg * COMP_REG + sizeof(cab);
        fseek(saida, (long) byte_offset, SEEK_SET);
        fwrite(buffer, COMP_REG, 1, saida);
        cab.cont_reg++;
        printf("%s\n", buffer);
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

