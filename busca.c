#include "main.h"
#include "busca.h"

#include <stdbool.h>

bool busca_registro(char key[], int tam_reg)
{
    FILE *busca;
    busca = fopen("dadaos.dat", "r+b");

    bool achou = false;
    char buffer[COMP_REG + 1], aux[COMP_REG + 1];
    char *key_buffer;
    ;
    int comp_reg, var, posicao_de_leitura, teste; //posicao_de_leitura vai ser usada depois

    printf("\nBusca pelo registro de chave '%s'\n", key);

    fseek(busca, sizeof(cab), SEEK_SET);
    comp_reg = leia(buffer, COMP_REG + 1, busca);

    while (achou == false && comp_reg > 0)
    {
        key = strtok(buffer, "|");
        if (strcmp(key, key) == 1)
        {
            achou = true;
        }
        else
        {
            comp_reg = leia(buffer, COMP_REG + 1, busca);
        }
    }

    if (achou)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int leia(char buffer[], int size, FILE *entrada)
{
    short num;
    fread(&num, sizeof(short), 1, entrada);

    if (feof(entrada) != 0)
        return 0;
    if (num < size)
    {
        fread(buffer, sizeof(char), num, entrada);
        buffer[num] = '\0';
        return num;
    }
    else
        return 0;
}

void le_mostra(FILE *entrada)
{
    char buffer[COMP_REG + 1];
    char *campo;

    fread(buffer, COMP_REG, 1, entrada);

    printf("\nConteudo do registro\n");
    campo = strtok(buffer, "|");
    while (campo != NULL)
    {
        printf("%s\n", campo);
        campo = strtok(NULL, "|");
    }
}