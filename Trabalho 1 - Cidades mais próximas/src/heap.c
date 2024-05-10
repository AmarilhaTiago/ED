#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/libhash.h"

int pai(int n){
    return (n-1)/2;
}

int filho_esq(int n){
    return 2*n + 1;
}

int filho_dir(int n){
    return 2*n + 2;
}

void apaga_heap(theap *heap){
    free(heap->vizinhos);
    free(heap);
}

void constroi_heap(theap *heap, int max){
    heap->vizinhos = (tvizinho *)malloc(max * sizeof(tvizinho));
    heap->tam = 0;
    heap->max = max;
}

void desce(theap *heap, int n){
    int maior = n;
    int direita = filho_dir(n);
    int esquerda = filho_esq(n);

    if(direita < heap->tam && heap->vizinhos[maior].distance < heap->vizinhos[direita].distance){
        maior = direita;
    }
    if(esquerda < heap->tam && heap->vizinhos[maior].distance < heap->vizinhos[esquerda].distance){
        maior = esquerda;
    }
    if(maior != n){
        troca(&(heap->vizinhos[maior]), &(heap->vizinhos[n]));
        desce(heap, maior);
    }
}

void sobe(theap *heap, int n){
    int pos_pai = pai(n);
    if(heap->vizinhos[n].distance > heap->vizinhos[pos_pai].distance){
        troca(&(heap->vizinhos[n]), &(heap->vizinhos[pos_pai]));
        sobe(heap, pos_pai);
    }
}

void troca(tvizinho *a, tvizinho *b){
    tvizinho aux = *a;
    *a = *b;
    *b = aux;
}

void heap_sort(theap *heap){
    for(int i = heap->tam - 1; i > 0; i--){
        troca(&(heap->vizinhos[0]), &(heap->vizinhos[i]));
        heap->tam--;
        desce(heap, 0);
    }
}

void heap_insere(theap *heap, double distancia, tmunicipio municipio){
    if(heap->tam == heap->max){
        return;
    }
    heap->vizinhos[heap->tam].distance = distancia;
    heap->vizinhos[heap->tam].municipio = municipio;
    sobe(heap, heap->tam);
    heap->tam++;
}

tvizinho acessa_max(theap *heap){
    return heap->vizinhos[0];
}

void altera_prioridade(theap *heap, int n, double distancia, tmunicipio municipio){
    tvizinho aux = heap->vizinhos[n];

    heap->vizinhos[n].distance = distancia;
    heap->vizinhos[n].municipio = municipio;

    if(heap->vizinhos[n].distance > aux.distance){
        sobe(heap, n);
    }
    if(heap->vizinhos[n].distance < aux.distance){
        desce(heap, n);
    }
}