#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <windows.h>

#define DELIM_STR '|'
#define COMP_REG 64

struct
{
    int cont_reg;
} cab;

void importacao(char argv[]);
int le_campos(char buffer[], int size, FILE *entrada);
int checkIf_file_exists(const char *filename);
void leia_op(char argv[]);
void imprimePed();

int main(int argc, char *argv[])
{
    SetConsoleOutputCP(65001);
    if (argc == 3 && strcmp(argv[1], "-i") == 0)
    {

        printf("Modo de importacao ativado ... nome do arquivo = %s\n", argv[2]);
        importacao(argv[2]);
    }
    else if (argc == 3 && strcmp(argv[1], "-e") == 0)
    {
        printf("Modo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);
        if (checkIf_file_exists(argv[2]) == 0)
        {
            printf("O arquivo não exite!");
            return 0;
        }
        else
            leia_op(argv[2]);
    }
    else if (argc == 2 && strcmp(argv[1], "-p") == 0)
    {

        printf("Modo de impressao da PED ativado ...\n");
        if (checkIf_file_exists(argv[2]) == 0)
        {
            printf("O arquivo não exite!");
            return 0;
        }
        else
            imprimePed();
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
    char campo[COMP_REG];
    char buffer[COMP_REG + 1], l[2];
    int i, byte_offset, cont;

    entrada = fopen(argv, "r");
    saida = fopen("dados.dat", "w+b");

    l[0] = DELIM_STR;
    l[1] = '\0';
    do
    {
        buffer[0] = '\0';
        for (i = 0; i < 4; i++)
        {
            cont = le_campos(campo, COMP_REG, entrada);
            if (cont > 0)
            {
                strcat(buffer, campo);
                strcat(buffer, l);
            }
        }

        if (cont > 0)
        {
            byte_offset = cab.cont_reg * COMP_REG + sizeof(cab);
            fseek(saida, (long)byte_offset, SEEK_SET);
            fwrite(buffer, COMP_REG, 1, saida);
            cab.cont_reg++;
            i = 0;
        }

    } while (cont > 0);

    fclose(entrada);
    fclose(saida);
}

int le_campos(char campo[], int size, FILE *entrada)
{
    int i = 0;
    char c = fgetc(entrada);

    while (c != EOF && c != DELIM_STR)
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

int checkIf_file_exists(const char *filename)
{
    struct stat buffer;
    int exist = stat(filename, &buffer);
    if (exist == 0)
        return 1;
    else
        return 0;
}

void leia_op(char argv[])
{
    FILE *entrada;

    entrada = fopen(argv, "r");

    int len = COMP_REG + 3;
    char linha[len];

    while(!feof(entrada))
    {
        le_linha(linha, len, entrada);
        printf("%s\n", linha);
    }
}

int le_linha(char linha[], int len, FILE *entrada)
{
    int i = 0;
    char c = fgetc(entrada);
    if(c != EOF)
    {
        while (c != '\n')
        {
            linha[i] = c;
            i++;
            c = fgetc(entrada);
        }
        linha[i] = '\0';
        return i;
    }else
        return 0;
}


void imprimePed()
{
}
