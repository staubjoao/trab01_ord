#include "main.h"
#include "remocao.h"

#include <stdio.h>

void remove_registro(FILE *fp, int byte_offset, int cont_seek)
{
    char ped = '*';

    fseek(fp, byte_offset, SEEK_SET);
    fwrite(&ped, sizeof(char), 1, fp);
    fwrite(&cab.ped, sizeof(int), 1, fp);
    cab.ped = cont_seek;
    rewind(fp);
    fwrite(&cab, sizeof(cab), 1, fp);
}