#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Mapa.h"

Mapa* crearMapa( long total){
    Mapa* newM = (Mapa*)malloc(sizeof(Mapa));
    newM->hashArray = malloc( total * sizeof(newM->hashArray));
    for(long i=0; i<total; i++){
        newM->hashArray[i] = NULL;
    }
    newM->contN = 0;
    newM->total = total;
    newM->current = -1;
    newM->loadFactor = (long)ceil(total*0.77);
    return newM;
}

Pair* crearPair( const void* key, void* value){
    Pair* newP = (Pair*)malloc(sizeof(Pair));
    newP->key = key;
    newP->value = value;
    return newP;
}

unsigned long stringHash( const void* key){
    const char* A_key = key;
    unsigned long num = 5381;
    for(int i=0; A_key[i] != '\0'; i++){
        num *= 33;
        num += A_key[i];
    }
    return num;
}

int equalString( const void* key1, const void* key2){
    const char* A_key1 = key1;
    const char* A_key2 = key2;
    if( strcmp( A_key1, A_key2) == 0){
        return 1;
    }
    return 0;
}

long linearProbing( Mapa* mapa, const void* key){
    unsigned long num = stringHash( key );
    long i = num % (mapa->total);
    while(1){
        if( (mapa->hashArray[i] == NULL) || (mapa->hashArray[i]->value == NULL) ){
            break;
        }
        if( equalString( mapa->hashArray[i]->key, key) ){
            break;
        }
        i++;
        if( i == (mapa->total)){
            i = 0;
        }
    }
    return i;
}

void enlarge( Mapa* mapa ){
    Pair** auxA = mapa->hashArray;
    long auxT = mapa->total;

    mapa->hashArray = malloc( (auxT*2) * sizeof(mapa->hashArray) );
    for(long i=0; i < (auxT*2); i++){
        mapa->hashArray[i] = NULL;
    }
    mapa->contN = 0;
    mapa->total = auxT*2;
    mapa->loadFactor = (long)ceil( (mapa->total) * 0.77);

    for( long i=0; i < auxT; i++ ){
        if( auxA[i] != NULL){
            if( auxA[i]->value != NULL){
                insertMap( mapa, auxA[i]->key, auxA[i]->value );
            }
            free( auxA[i]);
        }
    }
    free( auxA);
}

void insertMap( Mapa* mapa, const void* key, void* value){
    long i = linearProbing( mapa, key);

    if( (mapa->hashArray[i] == NULL) || (mapa->hashArray[i]->value == NULL) ){
        Pair* newP = crearPair( key, value);
        mapa->hashArray[i] = newP;
        mapa->contN++;

        if( mapa->contN >= mapa->loadFactor ){
            enlarge( mapa );
        }
    }
}

void * searchMap( Mapa* mapa, const void* key){
    long i = linearProbing( mapa, key);

    if( (mapa->hashArray[i] == NULL) || (mapa->hashArray[i]->value == NULL) ){
        return NULL;
    }
    mapa->current = i;
    return mapa->hashArray[mapa->current]->value;
}

void deleteKeyMap( Mapa* mapa, const void* key){
    long i = linearProbing( mapa, key);

    if( mapa->hashArray[i] != NULL ){
        mapa->hashArray[i]->value = NULL;
        mapa->contN--;
    }
}

void* firstMap( Mapa* mapa){
    for(long i=0; i<(mapa->total); i++){
        if( mapa->hashArray[i] != NULL ){
            if( mapa->hashArray[i]->value != NULL){
                mapa->current = i;
                return mapa->hashArray[mapa->current]->value;
            }
        }
    }
    return NULL;
}

void* nextMap( Mapa* mapa){
    for( long i = (mapa->current + 1) ; i<(mapa->total) ; i++){
        if( mapa->hashArray[i] != NULL){
            if(mapa->hashArray[i]->value != NULL){
                mapa->current = i;
                return mapa->hashArray[mapa->current]->value;
            }
        }
    }
    return NULL;
}

long sizeMap( Mapa* mapa){
	return mapa->contN;
}
