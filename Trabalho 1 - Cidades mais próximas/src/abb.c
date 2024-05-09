#include <stdio.h>
#include <stdlib.h>
#include "../include/libhash.h"


void insere_arvore(tnode **node, tmunicipio municipio, int h){
    if(*node == NULL){
        *node = (tnode *)malloc(sizeof(tnode));
        (*node)->municipio = municipio;
        (*node)->esq = NULL;
        (*node)->dir = NULL;
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

double calcula_distancia(tvizinho vizinho, tmunicipio municipio){
    double latitudeV = vizinho.municipio.latitude;
    double longitudeV = vizinho.municipio.longitude;
    double latitudeM = municipio.latitude;
    double longitudeM = municipio.longitude;

    double distancia = pow(latitudeV - latitudeM, 2) + pow(longitudeV - longitudeM, 2);

    return distancia;
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

