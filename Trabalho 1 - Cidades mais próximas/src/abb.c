#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/libhash.h"


// Função para inserir uma cidade na árvore de dimensão 2
void insere_arvore(tnode **node, tmunicipio municipio, int h){
    //caso a árvore esteja vazia
    if(*node == NULL){
        *node = (tnode *)malloc(sizeof(tnode));
        (*node)->municipio = municipio;
        (*node)->esq = NULL;
        (*node)->dir = NULL;
    // caso a árvore não esteja vazia
    // if par ou ímpar para saber qual dimensão será usada para comparação
    }else if(h % 2 == 0){
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

// Função para calcular a distância entre dois municípios com pitágoras
double calcula_distancia(tmunicipio vizinho, tmunicipio municipio){
    double latitudeV = vizinho.latitude;
    double longitudeV = vizinho.longitude;
    double latitudeM = municipio.latitude;
    double longitudeM = municipio.longitude;

    double distancia = pow(latitudeV - latitudeM, 2) + pow(longitudeV - longitudeM, 2);

    return distancia;
}


// Função para buscar os vizinhos de um município
void busca_vizinho(tnode *node, tmunicipio municipio, theap *heap, int h){
    if(node == NULL){
        return;
    }
    // calcula a distância entre o município atual e o município que está sendo buscado
    double dist = calcula_distancia(node->municipio, municipio);


    if(dist > 0){
        // se a distância for menor que a o tamanho máximo do heap, insere o município no heap
        if(heap->tam < heap->max){
            heap_insere(heap, dist, node->municipio);
        // se a distância do nó atual for menor do que o primeiro da heap, ele altera a prioridade
        }else if(dist < acessa_max(heap).distance){
            altera_prioridade(heap, 0, dist, node->municipio);

        }
    }

    // Inicialização de um nó para o próximo e outro para o contrário
    tnode *proximo = node->esq;
    tnode *contra = node->dir;

    // Verifica se a altura é par ou ímpar para saber qual dimensão será usada para comparação
    if(h % 2 == 0){
        // se a latitude do município atual for menor que a latitude do nó atual, o próximo é a esquerda e o contrário é a direita
        if(municipio.latitude < node->municipio.latitude){
            proximo = node->esq;
            contra = node->dir;
        }else{
        // se a latitude do município atual for maior ou igual que a latitude do nó atual, o próximo é a direita e o contrário é a esquerda
            proximo = node->dir;
            contra = node->esq;
        }
    }else{
        // se a longitude do município atual for menor que a longitude do nó atual, o próximo é a esquerda e o contrário é a direita
        if(municipio.longitude < node->municipio.longitude){
            proximo = node->esq;
            contra = node->dir;
        }else{
        // se a longitude do município atual for maior ou igual que a longitude do nó atual, o próximo é a direita e o contrário é a esquerda
            proximo = node->dir;
            contra = node->esq;
        }
    }
    // Chamada recursiva da função busca_vizinho para o próximo e o contrário
    busca_vizinho(proximo, municipio, heap, h + 1);
    busca_vizinho(contra, municipio, heap, h + 1);

}

void constroi_arvore(tarvore *arvore){
    arvore->raiz = NULL;
}

void apaga_arvore(tnode *arvore){
    if(arvore != NULL){
        apaga_arvore(arvore->esq);
        apaga_arvore(arvore->dir);
        free(arvore);
    }
}

