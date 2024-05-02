#ifndef __LIBHASH__
#define __LIBHASH__
#include <stdint.h>

    typedef struct {
         uintptr_t * municipios;
         int size;
         int max;
         uintptr_t deleted;
         char * (*get_key)(void *);
    }thash;

uint32_t hashf(const char* str, uint32_t h);
int hash_duplo(thash *hash, int i, const char *key);
int insere_cidade(thash * h, void * bucket);
int constroi_hash(thash * h,int nbuckets, char * (*get_key)(void *) );
void * busca_ibge(thash h, const char * key);
void apaga_hash(thash *h);


#endif