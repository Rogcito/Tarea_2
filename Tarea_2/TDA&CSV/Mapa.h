#ifndef MAPA_H
#define MAPA_H

typedef struct{
    const void* key;
    void* value;
}Pair;

typedef struct{
    Pair ** hashArray;
    long contN; //cont no Nulos;
    long total;
    long current;
    long loadFactor;
}Mapa;

/** Crea un Mapa */
Mapa* crearMapa(long total);

/** Crea un Par (key, value) */
Pair* crearPair(const void* key, void* value);

/** Genera un numero ocupando la key ingresada( string ) */
unsigned long stringHash( const void* key);

/** Compara si las 2 keys( strings ), retorna 1 si son iguales y 0 si no lo son */
int equalString( const void* key1, const void* key2);

/** Retorna la posicion probable de la key */
long linearProbing( Mapa* mapa, const void* key );

/** Expande el arreglo del mapa si se ve sobrepasado */
void enlarge( Mapa* mapa);

/** Inserta dentro del mapa si la key no existe */
void insertMap( Mapa* mapa, const void* key, void* value);

/** Busca una key en el mapa y retorna el value */
void* searchMap(Mapa* mapa, const void* key);

/** Elimina una key completa */
void deleteKeyMap( Mapa* mapa, const void* key);

/** Retorna lo que guarda el primero en el mapa */
void* firstMap( Mapa* mapa);

/** Retorna lo que guarda el siguiente al current en el mapa */
void* nextMap( Mapa* mapa);

/** Retorna la cantidad de NO nulos que existan en el mapa */
long sizeMap( Mapa* mapa);

#endif // MAPA_H
