#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/libhash.h"
#define MAX_HASH 11141


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

void preenche_municipio(thash *h_ibge, thash *h_nome, tarvore *arvore)
{
    // Definindo as váriaveis
    tmunicipio *municipio;
    FILE *file;
    char *path_file = "../json/municipios.json";
    char line[70];

    // Abrindo o arquivo
    file = fopen(path_file, "r");
    if (file == NULL)
    {
        printf("Erro na abertura do arquivo\n");
    }
    // Percorrendo cada linha do arquivo e guardando na variável line
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Verifica se a linha contém uma chave, o que indica o início de um município
        if (strstr(line, "{"))
        {
            // Alocando memória para a variável municipio
            municipio = (tmunicipio *)malloc(sizeof(tmunicipio));

            // Lendo as informações do município
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

            // Inserindo o município nas estruturas
            insere_cidade(h_ibge, *municipio);
            insere_cidade_nome(h_nome, *municipio);
            insere_arvore(&arvore->raiz, *municipio, 0);
        }
    }
    // Fechando o arquivo
    fclose(file);
}

void print_dados(tmunicipio *municipio)
{
    printf("_______________________\n");
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

void menu_opcoes(thash h_ibge, thash h_nome, tarvore arv)
{
    tmunicipio *muni;
    theap heap;
    int n;
    int x = -1;
    int codigo;
    while (x != 0)
    {
        printf("_______________________\n");
        printf("Escolha uma opcao:\n");
        printf("1 - Buscar por codigo ibge\n");
        printf("2 - Buscar vizinhos por ibge\n");
        printf("3 - Buscar vizinhos por nome\n");
        printf("0 - Sair\n");
        printf("_______________________\n");
        printf("Digite o numero da opcao: ");
        scanf("%d", &x);

        switch (x)
        {
        case 1:
            printf("Digite o codigo do municipio: ");
            scanf("%d", &codigo);
            muni = busca_ibge(&h_ibge, codigo);
            if(muni != NULL){
                print_dados(muni);
            }else{
                printf("\nCidade não encontrada!\n");
            }
            break;
        case 2:
        printf("Digite o codigo do municipio: ");
            scanf("%d", &codigo);
            muni = busca_ibge(&h_ibge, codigo);
            if(muni != NULL){
                printf("Digite quantos vizinhos você deseja procurar: ");
                scanf("%d", &n);
                constroi_heap(&heap, n);
                busca_vizinho(arv.raiz, *muni, &heap, 0);
                heap_sort(&heap);
                for(int i = 0; i < n; i++){
                    printf("_______________________\n");
                    printf("Vizinho %d:\n", i + 1);
                    printf("Distancia: %f km\n", sqrt(heap.vizinhos[i].distance) * 100);
                    printf("Código IBGE do municipio: %d\n", heap.vizinhos[i].municipio.codigo_ibge);
                }
                apaga_heap(&heap);
            }
            break;
        case 3:
            printf("Digite o nome do municipio: ");
            char nome[50];
            scanf(" %[^\n]", nome);
            muni = busca_nome(&h_nome, nome);
            if(muni != NULL){
                printf("Digite quantos vizinhos você deseja procurar: ");
                scanf("%d", &n);
                constroi_heap(&heap, n);
                busca_vizinho(arv.raiz, *muni, &heap, 0);
                heap_sort(&heap);
                for(int i = 0; i < n; i++){
                    printf("_______________________\n");
                    printf("Vizinho %d:\n", i + 1);
                    printf("Distancia: %f km\n", sqrt(heap.vizinhos[i].distance) * 100);
                    printf("Dados do vizinho %d: \n", i + 1);
                    print_dados(&heap.vizinhos[i].municipio);
                }
                apaga_heap(&heap);
            }
            break;
        case 0:
            apaga_hash(&h_ibge);
            apaga_hash(&h_nome);
            apaga_arvore(arv.raiz);
            apaga_heap(&heap);
            break;
        default:
            printf("Esta opcao nao existe!\n");
        }
    }
}

int main()
{
    // Inicializações
    thash h_ibge;
    thash h_nome;
    tarvore arvore;

    // Construções
    constroi_arvore(&arvore);
    constroi_hash(&h_ibge, MAX_HASH);
    constroi_hash(&h_nome, MAX_HASH);

    // Chama o parser e preenche as estruturas
    preenche_municipio(&h_ibge, &h_nome, &arvore);

    //Exibe o menu de opções
    menu_opcoes(h_ibge, h_nome, arvore);

    return 0;
}