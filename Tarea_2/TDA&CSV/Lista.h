#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"

typedef struct{
    Nodo* head;
    Nodo* current;
    Nodo* last;
    long total;
}Lista;

Lista* crearLista();

void pushBackL( Lista* L, void* data );

void* firstL ( Lista* L );

void* nextL ( Lista* L );

void pushCurrentL(Lista* L, void* data);

void deleteCurrentL( Lista* L );

void deleteL( Lista* L);


#endif // LISTA_H
