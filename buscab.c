//sem uso, só salvando o código msm

struct
{
    int *key;
    int *ped;
} vet;

void cria_vet(FILE *busca)
{
    int *key = malloc(cab.cont_reg * sizeof(int));
    int *ped = malloc(cab.cont_reg * sizeof(int));
    int i, byte_offset;
    char l[2], buffer[COMP_REG + 1];

    l[0] = DELIM_STR;
    l[1] = '\0';

    rewind(busca);

    for (i = 0; i < cab.cont_reg; i++)
    {
        byte_offset = i * COMP_REG + sizeof(cab);
        fseek(busca, byte_offset, SEEK_SET);
        fread(buffer, COMP_REG, 1, busca);
        strtok(buffer, l);
        key[i] = atoi(buffer);
        ped[i] = i;
    }

    vet.key = key;
    vet.ped = ped;
    free(key);
    free(ped);
}

int busca_binaria(int key, int comeco, int fim)
{
    int meio;
    if (comeco <= fim)
    {
        meio = (comeco + fim) / 2;
        if (key == vet.key[meio])
            return meio;
        else
        {
            if (key < vet.key[meio])
                return busca_binaria(key, comeco, meio - 1);
            else
                return busca_binaria(key, meio + 1, fim);
        }
    }
    return -1;
}

void merge(int comeco, int meio, int fim)
{
    int *vet_aux_ped, *vet_aux_key, p1, p2, tam, i, j, k;
    int fim1 = 0, fim2 = 0;
    tam = fim - comeco + 1;
    p1 = comeco;
    p2 = meio + 1;
    vet_aux_key = (int *)malloc(tam * sizeof(int));
    vet_aux_ped = (int *)malloc(tam * sizeof(int));

    if (vet_aux_key != NULL)
    {
        for (i = 0; i < tam; i++)
        {
            if (!fim1 && !fim2)
            {
                if (vet.key[p1] < vet.key[p2])
                {
                    vet_aux_ped[i] = vet.ped[p1];
                    vet_aux_key[i] = vet.key[p1++];
                }
                else
                {
                    vet_aux_ped[i] = vet.ped[p2];
                    vet_aux_key[i] = vet.key[p2++];
                }
                if (p1 > meio)
                    fim1 = 1;
                if (p2 > fim)
                    fim2 = 1;
            }
            else
            {
                if (!fim1)
                {
                    vet_aux_ped[i] = vet.ped[p1];
                    vet_aux_key[i] = vet.key[p1++];
                }
                else
                {
                    vet_aux_ped[i] = vet.ped[p2];
                    vet_aux_key[i] = vet.key[p2++];
                }
            }
        }
        for (j = 0, k = comeco; j < tam; j++, k++)
        {
            vet.key[k] = vet_aux_key[j];
            vet.ped[k] = vet_aux_ped[j];
        }
    }
    free(vet_aux_key);
    free(vet_aux_ped);
}

void ordena_vet(int comeco, int fim)
{
    int meio;
    if (comeco < fim)
    {
        meio = floor((fim + comeco) / 2);
        ordena_vet(comeco, meio);
        ordena_vet(meio + 1, fim);
        merge(comeco, meio, fim);
    }
}