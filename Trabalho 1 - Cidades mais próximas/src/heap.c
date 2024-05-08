#include <stdio.h>
#include <stdlib.h>
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

void libera_heap(theap *heap){
    free(heap->vizinhos);
    free(heap);
}

void constroi_heap(theap *heap, int max){
    heap->vizinhos = (tvizinho *)calloc(max, sizeof(tvizinho));
    heap->tam = 0;
    heap->max = max;
}
