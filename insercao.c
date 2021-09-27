#include "main.h"
#include "insercao.h"

#include <stdio.h>

bool insere_registro(FILE *fp, char buffer[], int *byte_offset, int *cont_seek)
{
    int byte_offset_local, ped;
    rewind(fp);
    fread(&cab, sizeof(cab), 1, fp);

    if (cab.ped != -1)
    {
        *cont_seek = cab.ped;
        byte_offset_local = cab.ped * COMP_REG + sizeof(cab) + sizeof(char);
        fseek(fp, byte_offset_local, SEEK_SET);
        fread(&ped, sizeof(int), 1, fp);
        byte_offset_local = cab.ped * COMP_REG + sizeof(cab);
        fseek(fp, byte_offset_local, SEEK_SET);
        fwrite(buffer, COMP_REG, 1, fp);
        cab.ped = ped;
        rewind(fp);
        fwrite(&cab, sizeof(cab), 1, fp);
        *byte_offset = byte_offset_local;
        return false;
    }
    else
    {
        byte_offset_local = cab.cont_reg * COMP_REG + sizeof(cab);
        fseek(fp, byte_offset_local, SEEK_SET);
        fwrite(buffer, COMP_REG, 1, fp);
        cab.cont_reg++;
        rewind(fp);
        fwrite(&cab, sizeof(cab), 1, fp);
        return true;
    }
}