#include "main.h"
#include "importacao.h"

#include <stdio.h>
#include <string.h>

void importacao(char argv[])
{
    FILE *entrada;
    FILE *saida;
    char buffer[COMP_REG + 1];
    int byte_offset, tam_campo;

    entrada = fopen(argv, "r");
    saida = fopen("dados.dat", "w+b");

    do
    {
        buffer[0] = '\0';
        tam_campo = concat_buffer(buffer, entrada);

        if (tam_campo > 0)
        {
            byte_offset = cab.cont_reg * COMP_REG + sizeof(cab);
            fseek(saida, (long)byte_offset, SEEK_SET);
            fwrite(buffer, COMP_REG, 1, saida);
            cab.cont_reg++;
        }
    } while (tam_campo > 0);

    rewind(saida);
    cab.ped = -1;
    fwrite(&cab, sizeof(cab), 1, saida);

    fclose(entrada);
    fclose(saida);
}

int concat_buffer(char buffer[], FILE *entrada)
{
    char campo[COMP_REG], l[2];
    int i, j;

    l[0] = DELIM_STR;
    l[1] = '\0';
    for (i = 0; i < 4; i++)
    {
        j = le_campos(campo, COMP_REG, entrada);
        if (j > 0)
        {
            strcat(buffer, campo);
            strcat(buffer, l);
        }
    }
    return j;
}

int le_campos(char campo[], int size, FILE *entrada)
{
    int i = 0;
    char c = fgetc(entrada);

    while (c != EOF && c != DELIM_STR)
    {
        if (i <= size - 1)
        {
            campo[i++] = c;
        }
        c = fgetc(entrada);
    }

    campo[i] = '\0';
    return i;
}