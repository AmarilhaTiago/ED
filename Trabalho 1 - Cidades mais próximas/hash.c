#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define SEED    0x12345678
#include "./include/libhash.h"

uint32_t hashf(const char* str, uint32_t h){
    for (; *str; ++str) {
        h ^= *str;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h;
}

int hash_duplo(thash *hash, int i, const char *key){
    int firstHash = hashf(key, SEED) % hash->max;
    int secondHash = (hashf(key, SEED) % (hash->max - 1)) + 1;
    return abs((firstHash + i*secondHash) % hash->max);
}

int insere_cidade(thash * h, void * bucket){
    int i = 0;
    int hash = hashf(h->get_key(bucket), SEED);
    int pos = hash %(h->max);
    /*se esta cheio*/
    printf("entrei na insere\n");
    if (h->max == (h->size+1)){
        printf("entrei no if\n");
        free(bucket);
        return EXIT_FAILURE;
    }else{  /*fazer a insercao*/
    printf("entrei no else\n");
        while(h->municipios[pos] != 0){
            printf("entrei no while\n");
            if (h->municipios[pos] == h->deleted)
                break;
            pos = hash_duplo(h, ++i, bucket);
        }
        h->municipios[pos] = (uintptr_t)bucket;
        h->size +=1;
        printf("inseri\n");
    }
    return EXIT_SUCCESS;
}



int constroi_hash(thash * h,int nbuckets, char * (*get_key)(void *) ){
    h->municipios = calloc(nbuckets + 1, sizeof(void *));
    if (h->municipios == NULL){
        return EXIT_FAILURE;
    }
    h->max = nbuckets + 1;
    h->size = 0;
    h->deleted = (uintptr_t)&(h->size);
    h->get_key = get_key;
    return EXIT_SUCCESS;
}


void * busca_ibge(thash  h, const char * key){
    int i = 0;
    int pos = hashf(key, SEED) % (h.max);
    void * ret = NULL;
    while(h.municipios[pos]!=0 && ret == NULL){
        if (strcmp(h.get_key((void*)h.municipios[pos]),key) == 0){
            ret = (void *) h.municipios[pos];
        }else{
            pos = hash_duplo(&h, ++i, key);
        }
    }
    return ret;

}

void apaga_hash(thash *h){
    free(h->municipios);
    free(h);
}