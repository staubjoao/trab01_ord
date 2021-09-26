
#ifndef IMPORTACAO_H
#define IMPORTACAO_H

#include <stdio.h>

void importacao(char argv[]);
int le_campos(char campo[], int size, FILE *entrada);
int concat_buffer(char buffer[], FILE *entrada);

#endif