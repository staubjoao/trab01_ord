#ifndef BUSCA_H
#define BUSCA_H

#include <stdio.h>
#include <stdbool.h>

bool busca_registro(char buffer[], int key, FILE *busca, int *byte_offset, int *cont_seek);

#endif