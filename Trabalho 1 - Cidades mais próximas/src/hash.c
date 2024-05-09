#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "../include/libhash.h"


int string_int(char *str) {
    int hash = 0;
    while (*str) {
        hash += *str;
        str++;
    }
    return hash;
}

int firstHash(int key, thash h){
    return key % h.max;
}

int secondHash(int key, thash h){
    return 1 + (key % (h.max - 1));
}

int hash_duplo(thash *hash, int i, int key){
    return (firstHash(key, *hash) + i * secondHash(key, *hash)) % hash->max;
}

int insere_cidade(thash *h, tmunicipio bucket){
    int i = 0;
    int pos = hash_duplo(h, i, bucket.codigo_ibge);

    if (h->max == (h->size+1)){
        return EXIT_FAILURE;
    }else{
        while(h->municipios[pos].codigo_ibge != 0){
            pos = hash_duplo(h,++i,bucket.codigo_ibge);
        }
        h->municipios[pos] = bucket;
        h->size +=1;
    }
    return EXIT_SUCCESS;
}

int constroi_hash(thash * h,int nbuckets){
    h->municipios = (tmunicipio *)calloc(nbuckets, sizeof(tmunicipio));
    if (h->municipios == NULL){
        return EXIT_FAILURE;
    }
    h->max = nbuckets;
    h->size = 0;
    return EXIT_SUCCESS;
}

tmunicipio * busca_ibge(thash *h, int key){
    int i = 0;
    int pos = hash_duplo(h, i, key);
    tmunicipio * ret = NULL;
    while(h->municipios[pos].codigo_ibge != 0 && ret == NULL){
        if (h->municipios[pos].codigo_ibge == key){
            ret = &(h->municipios[pos]);
        }else{
            pos = hash_duplo(h, ++i, key);
        }
    }
    return ret;
}

tmunicipio * busca_nome(thash *h, char *nome){
    int i = 0;
    int j = 0;
    int pos = hash_duplo(h, i, string_int(nome));
    tmunicipio **retorno = malloc(sizeof(tmunicipio *) * 7);
    tmunicipio *municipio = NULL;  
    while(h->municipios[pos].codigo_ibge != 0){
        if(strcmp(h->municipios[pos].nome, nome) == 0){
            municipio = &h->municipios[pos];  
            retorno[j++] = &h->municipios[pos];
        }
        pos = hash_duplo(h, ++i, string_int(nome));
    }
    if(municipio == NULL){
        printf("Cidade não encontrada\n");
        return NULL;
    }else if(j == 1){
        return municipio;
    }else if(j > 1){

        printf("Foram encontradas %d cidades com o nome %s\n", j, nome);
        printf("Opções:\n");
        for(int i = 0; i < j; i++){
            printf("%d: %s - DDD: %d\n", i + 1, retorno[i]->nome, retorno[i]->ddd);
        }
        printf("Escolha uma opção: ");
        int x = scanf("%d", &x);
        if(x > j || x < 1){
            printf("Opção inválida\n");
            return NULL;
        }
        return retorno[x - 1];
    }
}

void apaga_hash(thash *h){
    free(h->municipios);
}