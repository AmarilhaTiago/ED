#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "../include/libhash.h"


// Função para transformar uma string em um inteiro
int string_int(char *str) {
    int hash = 0;
    while (*str) {
        hash += *str;
        str++;
    }
    return abs(hash);
}

// Função para calcular o primeiro hash
int firstHash(int key, thash h){
    return key % h.max;
}

// Função para calcular o segundo hash, usamos o +1 e (h.max - 1) para garantir que sejam primos entre si e não ser 0
int secondHash(int key, thash h){
    return 1 + (key % (h.max - 1));
}

// Função para calcular o hash duplo
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

int insere_cidade_nome(thash *h, tmunicipio bucket){
    int i = 0;
    int pos = hash_duplo(h, i, string_int(bucket.nome));

    if (h->max == (h->size+1)){
        return EXIT_FAILURE;
    }else{
        while(h->municipios[pos].codigo_ibge != 0){
            pos = hash_duplo(h,++i, string_int(bucket.nome));
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
    retorno[0] = NULL;
    while(h->municipios[pos].codigo_ibge != 0){
        if(strcmp(h->municipios[pos].nome, nome) == 0){ 
            retorno[j++] = &h->municipios[pos];

        }
        pos = hash_duplo(h, ++i, string_int(nome));
    }
    
    if(j == 0){
        printf("\nCidade não encontrada\n");
        return NULL;
    }else if(j == 1){
        return retorno[0];
    }
        printf("Foram encontradas %d cidades com o nome %s\n", j, nome);
        printf("Opções:\n");
        for(int i = 0; i < j; i++){
            printf("--------------------\n");
            printf("Opção %d:\n", i + 1);
            printf("Nome: %s\n", retorno[i]->nome);
            printf("Código IBGE: %d\n", retorno[i]->codigo_ibge);
            printf("DDD: %d\n", retorno[i]->ddd);
        }
        printf("Escolha uma opção: ");
        int x;
        scanf("%d", &x);
        if(x > j || x < 1){
            printf("Opção inválida\n");
            return NULL;
        }
        return retorno[x - 1];
}

void apaga_hash(thash *h){
    free(h->municipios);
}