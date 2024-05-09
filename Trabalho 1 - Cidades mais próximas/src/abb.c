#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/libhash.h"


void insere_arvore(tnode **node, tmunicipio municipio, int h){
    if(*node == NULL){
        *node = (tnode *)malloc(sizeof(tnode));
        (*node)->municipio = municipio;
        (*node)->esq = NULL;
        (*node)->dir = NULL;
        printf("Cidade inserida: %s\n", municipio.nome);
    }
    if(h % 2 == 0){
        if(municipio.latitude < (*node)->municipio.latitude){
            //inserindo na esquerda caso a nova cidade tenha latitude menor que a cidade atual
            insere_arvore(&(*node)->esq, municipio, ++h);
        }else{
            // inserindo na direita caso a nova cidade tenha latitude maior ou igual que a cidade atual
            insere_arvore(&(*node)->dir, municipio, ++h);
        }
    }else{
        if(municipio.longitude < (*node)->municipio.longitude){
            //inserindo na esquerda caso a nova cidade tenha longitude menor que a cidade atual
            insere_arvore(&(*node)->esq, municipio, ++h);
        }else{
            // inserindo na direita caso a nova cidade tenha longitude maior ou igual que a cidade atual
            insere_arvore(&(*node)->dir, municipio, ++h);
        }
    }

}

double calcula_distancia(tmunicipio vizinho, tmunicipio municipio){
    double latitudeV = vizinho.latitude;
    double longitudeV = vizinho.longitude;
    double latitudeM = municipio.latitude;
    double longitudeM = municipio.longitude;

    double distancia = pow(latitudeV - latitudeM, 2) + pow(longitudeV - longitudeM, 2);

    return distancia;
}


tmunicipio * busca_vizinho(tnode *node, tmunicipio municipio, theap *heap, int h){
    if(node == NULL){
        return NULL;
    }
    double dist = calcula_distancia(node->municipio, municipio);
    if(dist > 0){
        if(heap->tam < heap->max){
            heap_insere(heap, dist, node->municipio);
        }else if(dist < acessa_max(heap).distance){
            altera_prioridade(heap, 0, dist, node->municipio);
        }
    }

    tnode *proximo = node->esq;
    tnode *contra = node->dir;

    if(h % 2 == 0){
        if(municipio.latitude < node->municipio.latitude){
            proximo = node->esq;
            contra = node->dir;
        }else{
            proximo = node->dir;
            contra = node->esq;
        }
    }else{
        if(municipio.longitude < node->municipio.longitude){
            proximo = node->esq;
            contra = node->dir;
        }else{
            proximo = node->dir;
            contra = node->esq;
        }
    }
    busca_vizinho(proximo, municipio, heap, h + 1);
    busca_vizinho(contra, municipio, heap, h + 1);

}

void constroi_arvore(tarvore *arvore){
    arvore->raiz = NULL;
}

void libera_arvore(tnode *node){
    if(node != NULL){
        libera_arvore(node->esq);
        libera_arvore(node->dir);
        free(node);
    }
}

