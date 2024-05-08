#include <stdio.h>
#include <stdlib.h>
#include "../include/libhash.h"


void insere_arvore(tnode **node, tmunicipio municipio, int i){
    if(*node == NULL){
        *node = (tnode *)malloc(sizeof(tnode));
        (*node)->municipio = municipio;
        (*node)->esq = NULL;
        (*node)->dir = NULL;
        (*node)->h = 0;
    }
    if(i % 2 == 0){
        if(municipio.latitude < (*node)->municipio.latitude){
            //inserindo na esquerda caso a nova cidade tenha latitude menor que a cidade atual
            insere_arvore(&(*node)->esq, municipio, ++i);
        }else{
            // inserindo na direita caso a nova cidade tenha latitude maior ou igual que a cidade atual
            insere_arvore(&(*node)->dir, municipio, ++i);
        }
    }else{
        if(municipio.longitude < (*node)->municipio.longitude){
            //inserindo na esquerda caso a nova cidade tenha longitude menor que a cidade atual
            insere_arvore(&(*node)->esq, municipio, ++i);
        }else{
            // inserindo na direita caso a nova cidade tenha longitude maior ou igual que a cidade atual
            insere_arvore(&(*node)->dir, municipio, ++i);
        }
    }

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

