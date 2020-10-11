#ifndef POKEMON_H
#define POKEMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 100

typedef struct{
    char Nombre[max];
}NombreTipos;

typedef struct{
    char id[max];
    char nombre[max];
    char sexo[max];
    int PC;
    int PS;
}Pokemon;

typedef struct{
    char nombre[max];
    int cantidad;
    void* listaTipos;
    char evoPrevia[max];
    char evoPosterior[max];
    int numPokedex;
    char region[max];
}InfoPokemon;

Pokemon* crearPokemon( const char* id, const char* nombre, const char* sexo, int PC, int PS);

InfoPokemon* crearInfoPokemon( const char* nombre, void* listaTipos, const char* evoPrevia, const char* evoPosterior, int numPokedex, const char* region );

NombreTipos* CrearNombreTipos( const char* Nombre);

#endif
