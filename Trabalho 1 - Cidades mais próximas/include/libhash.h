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

    typedef struct _node{
        tmunicipio municipio;
        struct _node *esq;
        struct _node *dir;
    }tnode;

    typedef struct _tree{
        tnode *raiz;    
    }tarvore;

    typedef struct{
        tmunicipio municipio;
        double distance;
    }tvizinho;

    typedef struct{
        tvizinho *vizinhos;
        int tam;
        int max;
    }theap;


int firstHash(int key, thash h);
int secondHash(int key, thash h);
int hash_duplo(thash *hash, int i, int key);
int insere_cidade(thash *h, tmunicipio bucket);
int constroi_hash(thash * h,int nbuckets);
tmunicipio * busca_ibge(thash *h, int key);
void apaga_hash(thash *h);
void insere_arvore(tnode **node, tmunicipio municipio, int i);
void constroi_arvore(tarvore *arvore);
void libera_arvore(tnode *node);
int pai(int n);
int filho_esq(int n);
int filho_dir(int n);
void libera_heap(theap *heap);
void constroi_heap(theap *heap, int max);
void desce(theap *heap, int n);
void sobe(theap *heap, int n);
void troca(tvizinho *a, tvizinho *b);
void heap_sort(theap *heap);




#endif