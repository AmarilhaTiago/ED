#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/libhash.h"
#define MAX 11141

    typedef struct {
        char codigo_ibge[7];
        char nome[100];
        float latitude;
        float longitude;
        int capital;
        int codigo_uf;
        int siafi_id;
        int ddd;
        char fuso_horario[50];
    }tmunicipio;

char * get_key(void * reg){
    return (*((tmunicipio *)reg)).codigo_ibge;
}

void preenche_municipio(tmunicipio *municipio, thash *h){
    FILE *file;
        char *path_file = "./json/municipios2.json";
        char line[40];

        file = fopen(path_file, "r");
        if(file == NULL){
            printf("Erro na abertura do arquivo\n");
        }
        
        while(fgets(line, sizeof(line), file) != NULL){
            if(strstr(line, "{")){
                printf("%s\n", line);
                municipio = (tmunicipio *)malloc(sizeof(tmunicipio));
            
                fgets(line, sizeof(line), file);
                printf("%s\n", line);
                sscanf(line, "    \"codigo_ibge\": %s,", municipio->codigo_ibge);
                fgets(line, sizeof(line), file);
                printf("%s\n", line);
                sscanf(line, "    \"nome\": %s,", municipio->nome);
                fgets(line, sizeof(line), file);
                printf("%s\n", line);
                sscanf(line, "    \"latitude\": %f,", &municipio->latitude);
                fgets(line, sizeof(line), file);
                printf("%s\n", line);
                sscanf(line, "    \"longitude\": %f,", &municipio->longitude);
                fgets(line, sizeof(line), file);
                printf("%s\n", line); 
                sscanf(line, "    \"capital\": %d,", &municipio->capital);
                fgets(line, sizeof(line), file);
                sscanf(line, "    \"codigo_uf\": %d,", &municipio->codigo_uf);
                fgets(line, sizeof(line), file);
                sscanf(line, "    \"siafi_id\": %d,", &municipio->siafi_id);
                fgets(line, sizeof(line), file);
                sscanf(line, "    \"ddd\": %d,", &municipio->ddd);
                fgets(line, sizeof(line), file);
                sscanf(line, "    \"fuso_horario\": %s,", municipio->fuso_horario);

                insere_cidade(h, municipio);
            }
        }
        fclose(file);
}

void print_dados(tmunicipio *municipio){
    printf("Codigo IBGE: %s\n", municipio->codigo_ibge);
    printf("Nome: %s\n", municipio->nome);
    printf("Latitude: %f\n", municipio->latitude);
    printf("Longitude: %f\n", municipio->longitude);
    printf("Capital: %d\n", municipio->capital);
    printf("Codigo UF: %d\n", municipio->codigo_uf);
    printf("Siafi ID: %d\n", municipio->siafi_id);
    printf("DDD: %d\n", municipio->ddd);
    printf("Fuso Horario: \"%s\"\n", municipio->fuso_horario);
}

void menu_opcoes(thash h){
    int x;
    char codigo[7];
    while(x != 0){
        printf("_______________________\n");
        printf("Escolha uma opcao:\n");
        printf("1 - Buscar por codigo\n");
        printf("2 - Buscar por nome\n");
        printf("3 - Busca n Vizinhos\n");
        printf("0 - Sair\n");
        printf("_______________________\n");
        printf("Digite o numero da opcao: ");
        scanf("%d", &x);
        
        switch(x){
            case 1:
                printf("Digite o codigo do municipio: ");
                scanf("%s", codigo);
                // print_dados((tmunicipio *)busca_ibge(h, codigo));
                break;
            case 2:
                printf("Digite o nome do municipio: ");
                char nome[50];
                scanf("%s", nome);
                //aqui vai ter um busca nome
                break;
            case 3:
                printf("Digite o codigo do municipio: ");
                scanf("%s", codigo);
                //aqui vai ter um busca vizinho
                break;
            case 0:
                apaga_hash(&h);
                break;
            default:
                printf("Esta opcao nao existe!\n");
        }
    }
}

int main(){
    
    tmunicipio municipio;
    thash h;

    constroi_hash(&h, MAX, get_key);
    printf("hi\n");

    preenche_municipio(&municipio, &h);
    menu_opcoes(h);

    return 0;
}