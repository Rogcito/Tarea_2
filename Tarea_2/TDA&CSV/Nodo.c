#include <stdio.h>
#include <stdlib.h>

#include "Nodo.h"

Nodo* crearNodo( void* data){
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->data = data;
    nuevoNodo->next = NULL;
    nuevoNodo->prev = NULL;
    return nuevoNodo;
}

