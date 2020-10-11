#ifndef NODO_H
#define NODO_H

typedef struct Nodito{
    void* data;
    struct Nodo* next;
    struct Nodo* prev;
}Nodo;

/** crea un nodo */
Nodo* crearNodo( void* data);

#endif // NODO_H
