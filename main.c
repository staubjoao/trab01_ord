#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <windows.h>

#include "main.h"
#include "importacao.h"

void leia_op(char argv[]);
int le_linha(char linha[], int len, FILE *entrada);
int checkIf_file_exists(const char *filename);

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

void leia_op(char argv[])
{
    FILE *entrada;

    entrada = fopen(argv, "r");

    int i, j = 2, len = COMP_REG + 3, num;
    char linha[len], num_str[6];

    while (!feof(entrada))
    {
        le_linha(linha, len, entrada);
        switch (linha[0])
        {
        case 'b':
            for (i = 0; i < 6; i++)
            {
                num_str[i] = linha[j];
                j++;
            }
            j = 2;
            num = atoi(num_str);
            itoa(num, num_str, 10);
            busca_registro(num_str, COMP_REG);
            break;
        case 'i':
            break;
        case 'r':
            break;
        }
        linha[0] = '\0';
    }

    fclose(entrada);
}



int le_linha(char linha[], int len, FILE *entrada)
{
    int i = 0;
    char c = fgetc(entrada);
    if (c != EOF)
    {
        while (c != '\n')
        {
            linha[i] = c;
            i++;
            c = fgetc(entrada);
        }
        linha[i] = '\0';
        return i;
    }
    else
        return 0;
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