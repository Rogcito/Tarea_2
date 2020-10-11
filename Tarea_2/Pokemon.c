#include "Pokemon.h"

Pokemon* crearPokemon(const char* id, const char* nombre, const char* sexo, int PC, int PS){
    Pokemon* newP = (Pokemon*)malloc(sizeof(Pokemon));

    strcpy(newP->id, id);
    strcpy(newP->nombre, nombre);
    strcpy(newP->sexo, sexo);
    newP->PC = PC;
    newP->PS = PS;

    return newP;
}

InfoPokemon* crearInfoPokemon(const char* nombre, void* listaTipos, const char* evoPrevia, const char* evoPosterior, int numPokedex, const char* region ){
    InfoPokemon* newIP = (InfoPokemon*)malloc(sizeof(InfoPokemon));

    strcpy(newIP->nombre, nombre);
    newIP->cantidad = 1;
    newIP->listaTipos = listaTipos;
    strcpy(newIP->evoPrevia, evoPrevia);
    strcpy(newIP->evoPosterior, evoPosterior);
    newIP->numPokedex = numPokedex;
    strcpy(newIP->region, region);

    return newIP;
}

NombreTipos* CrearNombreTipos( const char* Nombre){
    NombreTipos* newNL = (NombreTipos*)malloc(sizeof(NombreTipos));

    strcpy( newNL->Nombre, Nombre);

    return newNL;
}
