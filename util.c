#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "main.h"
#include "util.h"
#include "busca.h"
#include "remocao.h"
#include "insercao.h"

void leia_op(char argv[])
{
    FILE *entrada;
    FILE *fpb;

    entrada = fopen(argv, "r");
    fpb = fopen("dados.dat", "r+b");

    rewind(fpb);
    fread(&cab, sizeof(cab), 1, fpb);

    int byte_offset, cont_seek, key, i;
    char op, buffer[COMP_REG + 1], linha[COMP_REG + 3];

    while (!feof(entrada))
    {
        le_linha(linha, entrada);
        op = linha[0];
        switch (op)
        {
        case 'b':
            key = retorna_key(linha);
            cont_seek = 0;
            byte_offset = 0;
            printf("Busca pelo registro de chave %d\n", key);
            if (busca_registro(buffer, key, fpb, &byte_offset, &cont_seek))
                printf("%s (RRN = %d - byte-offset %d)\n\n", buffer, cont_seek, byte_offset);
            else
                printf("Erro: registro nao encontrado!\n\n");
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

int confere_arquivo(char *f)
{
    struct stat buffer;
    int exist = stat(f, &buffer);
    if (exist == 0)
        return 1;
    else
        return 0;
}