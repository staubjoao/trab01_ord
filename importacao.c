#include "main.h"
#include "importacao.h"

#include <stdio.h>
#include <string.h>

void importacao(char argv[])
{
    FILE *entrada;
    FILE *saida;
    char buffer[COMP_REG + 1];
    int i, byte_offset, cont;

    entrada = fopen(argv, "r");
    saida = fopen("dados.dat", "w+b");

    do
    {
        buffer[0] = '\0';
        cont = concat_buffer(buffer, entrada);

        if (cont > 0)
        {
            byte_offset = cab.cont_reg * COMP_REG + sizeof(cab);
            fseek(saida, (long)byte_offset, SEEK_SET);
            fwrite(buffer, COMP_REG, 1, saida);
            cab.cont_reg++;
            i = 0;
        }

    } while (cont > 0);

    rewind(saida);
    fwrite(&cab, sizeof(cab), 1, saida);

    fclose(entrada);
    fclose(saida);
}

int concat_buffer(char buffer[], FILE *entrada)
{
    char campo[COMP_REG], l[2];
    int i, cont;

    l[0] = DELIM_STR;
    l[1] = '\0';
    for (i = 0; i < 4; i++)
    {
        cont = le_campos(campo, COMP_REG, entrada);
        if (cont > 0)
        {
            strcat(buffer, campo);
            strcat(buffer, l);
        }
    }
    return cont;
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