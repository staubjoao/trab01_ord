#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <windows.h>

#include "main.h"
#include "importacao.h"
#include "busca.h"
#include "remocao.h"
#include "insercao.h"

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
        FILE *fpb;
        fpb = fopen("dados.dat", "r+b");
        imprime_ped(fpb);
        fclose(fpb);
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
    FILE *fpb;

    entrada = fopen(argv, "r");
    fpb = fopen("dados.dat", "r+b");

    rewind(fpb);
    fread(&cab, sizeof(cab), 1, fpb);

    int byte_offset, cont_seek, key;
    char op, buffer[COMP_REG + 1], linha[COMP_REG + 3];

    while (!feof(entrada))
    {
        le_linha(linha, entrada);
        op = linha[0];
        switch (op)
        {
        //tá feito(?)
        case 'b':
            key = retorna_key(linha);
            cont_seek = 0;
            byte_offset = 0;
            printf("Busca pelo registro de chave %d\n", key);
            if (busca_registro(buffer, key, fpb, &byte_offset, &cont_seek))
            {
                printf("%s (RRN = %d - byte-offset %d)\n\n", buffer, cont_seek, byte_offset);
            }
            else
            {
                printf("Erro: registro nao encontrado!\n\n");
            }
            break;
        case 'i':
            buffer[0] = '\0';
            cont_seek = 0;
            byte_offset = 0;
            retorna_registro(buffer, linha);
            key = retorna_key(linha);
            printf("Insercao do registro de chave '%d'\n", key);
            if (insere_registro(fpb, buffer, &byte_offset, &cont_seek))
            {
                printf("Local: fim do arquivo\n\n");
            }
            else
            {
                printf("Local: RRN = %d (byte-offset %d) [reutilizado]\n\n", cont_seek, byte_offset);
            }
            break;
        //tá feito(?)
        case 'r':
            key = retorna_key(linha);
            cont_seek = 0;
            byte_offset = 0;
            buffer[0] = '\0';
            printf("Remocao do registro de chave '%d'\n", key);
            if (busca_registro(buffer, key, fpb, &byte_offset, &cont_seek))
            {
                remove_registro(fpb, byte_offset, &cont_seek);
                printf("Registro removido!\n");
                printf("Posicao: RRN = %d (byte-offset %d)\n\n", cont_seek, byte_offset);
            }
            else
            {
                printf("Erro: registro nao encontrado!\n\n");
            }
            break;
        default:
            break;
        }
        linha[0] = '\0';
    }

    fclose(entrada);
    fclose(fpb);
}

void le_linha(char linha[], FILE *entrada) //tirar len
{
    int i = 0;
    char c = fgetc(entrada);
    if (c != EOF)
    {
        while (c != '\n' || feof(entrada))
        {
            linha[i] = c;
            i++;
            c = fgetc(entrada);
        }
        linha[i] = '\0';
    }
}

int retorna_key(char linha[])
{
    char key_str[7];
    int i, j = 2;
    for (i = 0; i < 6; i++)
    {
        key_str[i] = linha[j];
        j++;
    }
    key_str[j] = '\0';
    j = 2;
    return atoi(key_str);
}

void retorna_registro(char buffer[], char linha[])
{
    int i = 0, j = 2;

    while (linha[i] != '\0')
    {
        buffer[i] = linha[j];
        i++;
        j++;
    }
}

void imprime_ped(FILE *fp)
{
    int i = 0, ped, byte_offset;
    rewind(fp);
    fread(&cab, sizeof(cab), 1, fp);
    ped = cab.ped;

    printf("\nped: %d\n", ped);
    while (ped != -1)
    {
        byte_offset = ped * COMP_REG + sizeof(cab) + sizeof(char);
        fseek(fp, byte_offset, SEEK_SET);
        fread(&cab.ped, sizeof(cab), 1, fp);
        ped = cab.ped;
        if (ped != -1)
            printf("ped: %d\n", ped);
        i++;
    }
    printf("Quantidade de espaçoes na PED: %d", i);
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
