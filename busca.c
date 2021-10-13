#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "busca.h"

bool busca_registro(char buffer[], int key, FILE *busca, int *byte_offset, int *cont_seek)
{
    bool achou = false;
    char aux[COMP_REG + 1], l[2];
    int key_busca, i;

    l[0] = DELIM_STR;
    l[1] = '\0';
    while (!achou && *cont_seek <= cab.cont_reg)
    {
        *byte_offset = *cont_seek * COMP_REG + sizeof(cab);
        fseek(busca, *byte_offset, SEEK_SET);
        fread(buffer, COMP_REG, 1, busca);
        strcpy(aux, buffer);
        strtok(aux, l);
        key_busca = atoi(aux);
        if (key_busca == key)
            achou = true;
        else
            *cont_seek = *cont_seek + 1;
    }

    if (achou)
        return true;
    else
        return false;
}
