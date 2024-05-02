#ifndef __LIBHASH__
#define __LIBHASH__
#include <stdint.h>


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

    typedef struct {
         tmunicipio * municipios;
         int size;
         int max;
    }thash;

int firstHash(int key, thash h);
int secondHash(int key, thash h);
int hash_duplo(thash *hash, int i, int key);
int insere_cidade(thash *h, tmunicipio bucket);
int constroi_hash(thash * h,int nbuckets);
tmunicipio * busca_ibge(thash *h, int key);
void apaga_hash(thash *h);


#endif