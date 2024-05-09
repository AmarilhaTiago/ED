#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/libhash.h"
#define MAX 11141


char *removeChar(char *str) {
    char *result = malloc(strlen(str) + 1);
    int i, j = 0;

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != '\\') {
            result[j] = str[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

void preenche_municipio(thash *h)
{
    tmunicipio *municipio;
    FILE *file;
    char *path_file = "./json/municipios.json";
    char line[70];

    file = fopen(path_file, "r");
    if (file == NULL)
    {
        printf("Erro na abertura do arquivo\n");
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, "{"))
        {
            municipio = (tmunicipio *)malloc(sizeof(tmunicipio));

            fgets(line, sizeof(line), file);
            sscanf(line, "    \"codigo_ibge\": %d,", &municipio->codigo_ibge);
            fgets(line, sizeof(line), file);
            sscanf(line, "%*s \"%[^\"],", municipio->nome);
            fgets(line, sizeof(line), file);
            sscanf(line, "    \"latitude\": %f,", &municipio->latitude);
            fgets(line, sizeof(line), file);
            sscanf(line, "    \"longitude\": %f,", &municipio->longitude);
            fgets(line, sizeof(line), file);
            sscanf(line, "    \"capital\": %d,", &municipio->capital);
            fgets(line, sizeof(line), file);
            sscanf(line, "    \"codigo_uf\": %d,", &municipio->codigo_uf);
            fgets(line, sizeof(line), file);
            sscanf(line, "    \"siafi_id\": %d,", &municipio->siafi_id);
            fgets(line, sizeof(line), file);
            sscanf(line, "    \"ddd\": %d,", &municipio->ddd);
            fgets(line, sizeof(line), file);
            sscanf(line, "%*s \"%[^\"]\"", municipio->fuso_horario);
            strcpy(municipio->fuso_horario, removeChar(municipio->fuso_horario));

            insere_cidade(h, *municipio);
        }
    }
    fclose(file);
}

void print_dados(tmunicipio *municipio)
{
    printf("Codigo IBGE: %d\n", municipio->codigo_ibge);
    printf("Nome: %s\n", municipio->nome);
    printf("Latitude: %f\n", municipio->latitude);
    printf("Longitude: %f\n", municipio->longitude);
    printf("Capital: %d\n", municipio->capital);
    printf("Codigo UF: %d\n", municipio->codigo_uf);
    printf("Siafi ID: %d\n", municipio->siafi_id);
    printf("DDD: %d\n", municipio->ddd);
    printf("Fuso Horario: %s\n", municipio->fuso_horario);
}

void menu_opcoes(thash h)
{
    int x;
    int codigo;
    while (x != 0)
    {
        printf("_______________________\n");
        printf("Escolha uma opcao:\n");
        printf("1 - Buscar por codigo ibge\n");
        printf("2 - Buscar por nome\n");
        printf("3 - Busca n Vizinhos\n");
        printf("0 - Sair\n");
        printf("_______________________\n");
        printf("Digite o numero da opcao: ");
        scanf("%d", &x);

        switch (x)
        {
        case 1:
            printf("Digite o codigo do municipio: ");
            scanf("%d", &codigo);
            print_dados(busca_ibge(&h, codigo));
            break;
        case 2:
            printf("Digite o nome do municipio: ");
            char nome[50];
            scanf("%s", nome);
            busca_nome(&h, nome);
            
            break;
        case 3:
            printf("Digite o codigo do municipio: ");
            scanf("%d", &codigo);
            // aqui vai ter um busca vizinho
            break;
        case 0:
            apaga_hash(&h);
            break;
        default:
            printf("Esta opcao nao existe!\n");
        }
    }
}

int main()
{

    thash h;

    constroi_hash(&h, MAX);
    preenche_municipio(&h);
    menu_opcoes(h);

    return 0;
}