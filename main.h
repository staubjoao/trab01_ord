#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

#define DELIM_STR '|'
#define COMP_REG 64

struct
{
    int cont_reg;
    int ped;
} cab;

struct
{
    int *vet_key;
    int *vet_ped;
} vet;

#endif