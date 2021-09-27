#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

#define DELIM_STR '|'
#define COMP_REG 64

void leia_op(char argv[]);
void le_linha(char linha[], FILE *entrada);
void imprime_ped(FILE *fp);
void retorna_registro(char buffer[], char linha[]);
int checkIf_file_exists(const char *filename);

struct
{
    int cont_reg;
    int ped;
} cab;

#endif