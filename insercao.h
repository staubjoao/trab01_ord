#ifndef INSERCAO_H
#define INSERCAO_H

#include <stdio.h>
#include <stdbool.h>

bool insere_registro(FILE *fp, char buffer[], int *byte_offset, int *cont_seek);

#endif