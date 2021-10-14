#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

void leia_op(char argv[]);
void le_linha(char linha[], FILE *entrada);
int retorna_key(char linha[]);
void imprime_ped(FILE *fp);
void retorna_registro(char buffer[], char linha[]);
int confere_arquivo(char *f);

#endif