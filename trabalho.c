#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <windows.h>
#include <stdbool.h>

#define DELIM_STR '|'
#define COMP_REG 64

struct
{
    int cont_reg;
} cab;

void importacao(char argv[]);
int le_campos(char buffer[], int size, FILE *entrada);
void leia_op(char argv[]);
// void busca(char key[]);
int leia_reg(char buffer[], int tam, FILE *entrada);
int le_linha(char linha[], int len, FILE *entrada);
void imprimePed();
int checkIf_file_exists(const char *filename);
void le_mostra(FILE *arq);
bool busca_registro(char key[], int tam_reg);

int main(int argc, char *argv[])
{
    SetConsoleOutputCP(65001);
    if (argc == 3 && strcmp(argv[1], "-i") == 0)
    {

        printf("Modo de importacao ativado ... nome do arquivo = %s\n", argv[2]);
        importacao(argv[2]);
    }
    else if (argc == 3 && strcmp(argv[1], "-e") == 0)
    {
        printf("Modo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);
        if (checkIf_file_exists(argv[2]) == 0)
        {
            printf("O arquivo não exite!");
            return 0;
        }
        else
            leia_op(argv[2]);
    }
    else if (argc == 2 && strcmp(argv[1], "-p") == 0)
    {

        printf("Modo de impressao da PED ativado ...\n");
        if (checkIf_file_exists(argv[2]) == 0)
        {
            printf("O arquivo não exite!");
            return 0;
        }
        else
            imprimePed();
    }
    else
    {
        fprintf(stderr, "Argumentos incorretos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s (-i|-e) nome_arquivo\n", argv[0]);
        fprintf(stderr, "$ %s -p\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}

void importacao(char argv[])
{
    FILE *entrada;
    FILE *saida;
    char campo[COMP_REG];
    char buffer[COMP_REG + 1], l[2];
    int i, byte_offset, cont;

    entrada = fopen(argv, "r");
    saida = fopen("dados.dat", "w+b");

    l[0] = DELIM_STR;
    l[1] = '\0';
    do
    {
        buffer[0] = '\0';
        for (i = 0; i < 4; i++)
        {
            cont = le_campos(campo, COMP_REG, entrada);
            if (cont > 0)
            {
                strcat(buffer, campo);
                strcat(buffer, l);
            }
        }

        if (cont > 0)
        {
            byte_offset = cab.cont_reg * COMP_REG + sizeof(cab);
            fseek(saida, (long)byte_offset, SEEK_SET);
            fwrite(buffer, COMP_REG, 1, saida);
            cab.cont_reg++;
            i = 0;
        }

    } while (cont > 0);

    rewind(saida);
    fwrite(&cab, sizeof(cab), 1, saida);

    fclose(entrada);
    fclose(saida);
}

int le_campos(char campo[], int size, FILE *entrada)
{
    int i = 0;
    char c = fgetc(entrada);

    while (c != EOF && c != DELIM_STR)
    {
        if (i <= size - 1)
        {
            campo[i] = c;
            i++;
        }
        c = fgetc(entrada);
    }

    campo[i] = '\0';
    return i;
}

void leia_op(char argv[])
{
    FILE *entrada;

    entrada = fopen(argv, "r");

    int i, j = 2, len = COMP_REG + 3, num;
    char linha[len], num_str[6];

    //fazer o seek ler o registro fazer seek para o proximo...
    while (!feof(entrada))
    {
        le_linha(linha, len, entrada);
        switch (linha[0])
        {
        case 'b':
            for (i = 0; i < 6; i++)
            {
                num_str[i] = linha[j];
                j++;
            }
            j = 2;
            num = atoi(num_str);
            itoa(num, num_str, 10);
            busca_registro(num_str, COMP_REG);
            break;
        case 'i':
            break;
        case 'r':
            break;
        }
        linha[0] = '\0';
    }

    fclose(entrada);
}

bool busca_registro(char key[], int tam_reg)
{
    FILE *busca;
    busca = fopen("dadaos.dat", "r+b");

    bool achou = false;
    char buffer[COMP_REG + 1], aux[COMP_REG + 1];
    char *key_buffer;
    ;
    int comp_reg, var, posicao_de_leitura;//posicao_de_leitura vai ser usada depois

    printf("\nBusca pelo registro de chave '%s'\n", key);

    fseek(busca, sizeof(cab), SEEK_SET);
    fread(&var, sizeof(short), 1, busca);
    printf("%d", var);
    while (achou == false)
    {
        posicao_de_leitura = ftell(busca);
        fread(buffer, sizeof(char), tam_reg, busca);
            printf("%s\n", buffer);
        buffer[var] = '\0';

        if (buffer[0] != '*')
        {
            strcpy(aux, buffer);
            key_buffer = strtok(aux, "|");

            if (strcmp(key, key_buffer))
            {
                achou = true;
            }
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

int leia_reg(char buffer[], int tam, FILE *entrada)
{
    int comp_reg;
    if (fread(&comp_reg, sizeof(int), 1, entrada) == 0)
    {
        return 0;
    }
    if (comp_reg < tam)
    {
        fread(buffer, sizeof(char), comp_reg, entrada);
        buffer[comp_reg] = '\0';
        return comp_reg;
    }
    else
    {
        printf("%d\n", comp_reg);
        return 0;
    }
}

// int leia_reg(char buffer[], int tam, FILE *entrada)
// {
//     rewind(entrada);

//     int comp_reg;
//     if (fread(&comp_reg, sizeof(int), 1, entrada) != 0)
//     {
//         printf("%d\n", comp_reg);
//         return 0;
//     }

//     if (comp_reg < tam)
//     {
//         printf("%d\n", comp_reg);
//         fread(buffer, sizeof(char), comp_reg, entrada);
//         buffer[comp_reg] = '\0';
//         return comp_reg;
//     }
//     else
//     {
//         return 0;
//     }
// }

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

int le_linha(char linha[], int len, FILE *entrada)
{
    int i = 0;
    char c = fgetc(entrada);
    if (c != EOF)
    {
        while (c != '\n')
        {
            linha[i] = c;
            i++;
            c = fgetc(entrada);
        }
        linha[i] = '\0';
        return i;
    }
    else
        return 0;
}

void imprimePed()
{
}

int checkIf_file_exists(const char *filename)
{
    struct stat buffer;
    int exist = stat(filename, &buffer);
    if (exist == 0)
        return 1;
    else
        return 0;
}