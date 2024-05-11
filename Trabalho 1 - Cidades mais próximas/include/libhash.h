#ifndef __LIBHASH__
#define __LIBHASH__
#include <stdint.h>


    // Estrutura de dados relacionada aos municipios do arquivo json
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

    // Estrutura de dados Hash
    typedef struct {
         tmunicipio * municipios;
         int size;
         int max;
    }thash;

    // Estrutura de dados nó da árvore (KDtree)
    typedef struct _node{
        tmunicipio municipio;
        struct _node *esq;
        struct _node *dir;
    }tnode;

    // Estrutura de dados árvore (para guardar a raiz)
    typedef struct _tree{
        tnode *raiz;   
    }tarvore;

    //estrutura de dados vizinho para guardar um municipio e a distância
    typedef struct{
        tmunicipio municipio;
        double distance;
    }tvizinho;

    // Estrutura de dados heap
    typedef struct{
        tvizinho *vizinhos;
        int tam;
        int max;
    }theap;

// Funções de hash
int firstHash(int key, thash h);
int secondHash(int key, thash h);
int hash_duplo(thash *hash, int i, int key);
int constroi_hash(thash * h,int nbuckets);
int insere_cidade(thash *h, tmunicipio bucket);
int insere_cidade_nome(thash *h, tmunicipio bucket);
void apaga_hash(thash *h);
tmunicipio * busca_ibge(thash *h, int key);
tmunicipio * busca_nome(thash *h, char *nome);

// Funções de árvore (KDtree)
void constroi_arvore(tarvore *arvore);
void insere_arvore(tnode **node, tmunicipio municipio, int h);
void busca_vizinho(tnode *node, tmunicipio municipio, theap *heap, int h);
double calcula_distancia(tmunicipio vizinho, tmunicipio municipio);
void apaga_arvore(tnode *node);

// Funções de heap
int pai(int n);
int filho_esq(int n);
int filho_dir(int n);
void constroi_heap(theap *heap, int max);
void troca(tvizinho *a, tvizinho *b);
void desce(theap *heap, int n);
void sobe(theap *heap, int n);
void heap_insere(theap *heap, double distancia, tmunicipio municipio);
void heap_sort(theap *heap);
tvizinho acessa_max(theap *heap);
void altera_prioridade(theap *heap, int n, double distancia, tmunicipio municipio);
void apaga_heap(theap *heap);

#endif