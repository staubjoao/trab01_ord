#include "main.h"
#include "busca.h"

#include <stdbool.h>
#include <string.h>

bool busca(int key)
{
    FILE *busca;
    busca = fopen("dados.dat", "r+b");

    int byte_offset, rrn, *tam_reg;
    rrn = 0;

    fread(&cab.cont_reg, sizeof(cab), 1, busca);
    return busca_registro(key, COMP_REG + 1, busca);
}

bool busca_registro(int key, int tam_reg, FILE *busca)
{
    bool achou = false;
    char buffer[COMP_REG + 1], aux[COMP_REG + 1], l[2];
    char *key_buffer;
    int byte_offset, key_busca;

    l[0] = DELIM_STR;
    l[1] = '\0';

    cont_seek = 0;
    while (!achou && cont_seek <= cab.cont_reg)
    {
        byte_offset = cont_seek * COMP_REG + sizeof(cab);
        fread(buffer, COMP_REG, 1, busca);
        strcpy(aux, buffer);
        strtok(buffer, l);
        key_busca = atoi(buffer);
        if (key_busca == key)
        {
            printf("valor: %s %d %d\n", aux, byte_offset, cont_seek);
            achou = true;
            mostrar(busca, byte_offset);
        }
        else
        {
            cont_seek++;
        }
    }

    if (achou)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void mostrar(FILE *arq, int byte_offset)
{
    char buffer[COMP_REG + 1];
    char *campo;

    fseek(arq, (long)byte_offset, SEEK_SET);
    fread(buffer, COMP_REG, 1, arq);

    printf("Conteudo do registro\n");
    campo = strtok(buffer, "|");
    while (campo != NULL)
    {
        printf("\t%s\n", campo);
        campo = strtok(NULL, "|");
    }
}