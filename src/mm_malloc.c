#include <unistd.h> // Para sbrk
#include "mm_malloc.h"

// Inicio de la lista enlazada del heap
void *base = NULL;

void *my_malloc(size_t size) {
    // TODO: Implementar First-Fit o Best-Fit
    // 1. Verificar si hay un bloque libre del tamaño adecuado.
    // 2. Si no, pedir espacio al OS con sbrk().
    if(size == 0) return NULL;
    if(base == NULL) {
        base = sbrk(size + META_SIZE);
        if(base == (void*)-1) return NULL;
        block_meta *ptrBase = (block_meta*)base;
        ptrBase->size = size;
        ptrBase->next = NULL;
        ptrBase->free = 0;
        ptrBase->magic = 0x12345678;
        return (void*)(ptrBase+1);
    }
    else {
        block_meta *ptrCurrent = (block_meta*)base;
        while(ptrCurrent != NULL) {
            if(ptrCurrent->free && ptrCurrent->size >= size) {
                ptrCurrent->free = 0;
                return (void*)(ptrCurrent+1);
            }
            ptrCurrent = ptrCurrent->next;
        }
        block_meta *ptrBlock = sbrk(size + META_SIZE);
        if(ptrBlock == (void*)-1) return NULL;
        ptrBlock->size = size;
        ptrBlock->next = NULL;
        ptrBlock->free = 0;
        ptrBlock->magic = 0x12345678;
        ptrCurrent->next = ptrBlock;
    }
    return NULL; 
}

void my_free(void *ptr) {
    // TODO: Marcar el bloque como libre.
    // TODO: Fusionar bloques adyacentes (Coalescing).
    if(ptr == NULL) {
        return;
    }
}

void *my_calloc(size_t nmemb, size_t size) {
    // TODO: Usar my_malloc y luego memset a 0.
    if(nmemb == 0 || size == 0) {
        return NULL;
    }
    return NULL;
}

void *my_realloc(void *ptr, size_t size) {
    // TODO: Redimensionar el bloque o moverlo a uno nuevo.
    if(ptr == NULL) {
        return my_malloc(size);
    }
    if(size == 0) {
        my_free(ptr);
        return NULL;
    }
    return NULL;
}
