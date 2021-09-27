#ifndef REMOCAO_H
#define REMOCAO_H

#include <stdio.h>
#include <stdbool.h>

void remove_registro(FILE *fp, int byte_offset, int *cont_seek);

#endif