#ifndef BUSCA_H
#define BUSCA_H

#include <stdio.h>
#include <stdbool.h>

bool busca(int key);
bool busca_registro(int key, int tam_reg, FILE *busca);
void mostrar(FILE *arq, int byte_offset);

#endif