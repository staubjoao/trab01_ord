#ifndef BUSCA_H
#define BUSCA_H

#include <stdio.h>
#include <stdbool.h>

bool busca_registro(char buffer[], int key, FILE *busca, int *byte_offset, int *cont_seek);
void cria_vet(FILE *busca);
int busca_binaria(int key, int comeco, int fim);
void merge(int comeco, int meio, int fim);
void ordena_vet(int comeco, int fim);

#endif