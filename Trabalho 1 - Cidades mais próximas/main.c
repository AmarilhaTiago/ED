#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int codigo_ibge;
    char nome[100];
    float latitude;
    float longitude;
    int capital;
    int codigo_uf;
    int siafi_id;
    int ddd;
    char fuso_horario[50];
}tmunicipio;

void preenche_municipios(tmunicipio *municipio){
    FILE *file;
        char *path_file = "../json/municipios2.json";
        char line[150];

        file = fopen(path_file, "r");

        if(file == NULL){
            printf("Erro na abertura do arquivo\n");
            return EXIT_FAILURE;
        }

        int codigo_ibge;
        char nome[100];
        double latitude;
        double longitude;
        int capital;
        int codigo_uf;
        int siafi_id;
        int ddd;
        char fuso_horario[50];

        while(fgets(line, sizeof(line), file) != NULL){
            if(strstr(line, "{")){
                
                fgets(line, sizeof(line), file);
                sscanf(line, "    \"codigo_ibge\": %d,", &codigo_ibge);
                municipio->codigo_ibge = codigo_ibge;
                fgets(line, sizeof(line), file);
                sscanf(line, "    \"nome\": %s,", nome);
                strcpy(municipio->nome, nome);
                fgets(line, sizeof(line), file);
                sscanf(line, "    \"latitude\": %lf,", &latitude);
                municipio->latitude = latitude;
                fgets(line, sizeof(line), file);
                sscanf(line, "    \"longitude\": %lf,", &longitude);
                municipio->longitude = longitude;
                fgets(line, sizeof(line), file);
                sscanf(line, "    \"capital\": %d,", &capital);
                municipio->capital = capital;
                fgets(line, sizeof(line), file);
                sscanf(line, "    \"codigo_uf\": %d,", &codigo_uf);
                municipio->codigo_uf = codigo_uf;
                fgets(line, sizeof(line), file);
                sscanf(line, "    \"siafi_id\": %d,", &siafi_id);
                municipio->siafi_id = siafi_id;
                fgets(line, sizeof(line), file);
                sscanf(line, "    \"ddd\": %d,", &ddd);
                municipio->ddd = ddd;
                fgets(line, sizeof(line), file);
                sscanf(line, "    \"fuso_horario\": %s,", fuso_horario);
                strcpy(municipio->fuso_horario, fuso_horario);
            }
        }
        fclose(file);
}

int main(){

    tmunicipio municipio;

    // Chama a função para preencher a estrutura com os dados dos municípios
    preenche_municipios(&municipio);

    // Imprime os dados do município
    printf("Codigo IBGE: %d\n", municipio.codigo_ibge);
    printf("Nome: %s\n", municipio.nome);
    printf("Latitude: %f\n", municipio.latitude);
    printf("Longitude: %f\n", municipio.longitude);
    printf("Capital: %d\n", municipio.capital);
    printf("Codigo UF: %d\n", municipio.codigo_uf);
    printf("Siafi ID: %d\n", municipio.siafi_id);
    printf("DDD: %d\n", municipio.ddd);
    printf("Fuso Horario: %s\n", municipio.fuso_horario);

    return 0;
}