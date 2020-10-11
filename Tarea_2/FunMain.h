#ifndef FUNMAIN_H
#define FUNMAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#include "TDA&CSV/Mapa.h"
#include "TDA&CSV/Lista.h"
#include "TDA&CSV/CSV.h"
#include "Pokemon.h"

#define max 100

void lowerCase (char* str);

void removeSpacesInPlace (char* str);

void arreglarString(char* str );

void* vectorizarTipos( const char* str);

int obtenerID( Mapa* IdBox );

//----------------------------------

void ListaOrdenadaPC( Lista* L, Pokemon* P);

void ListaOrdenadaPS( Lista* L, Pokemon* P);

void ListaOrdenadaNP( Lista* L, InfoPokemon* IP);

//----------------------------------

void insertarListaMapa( Mapa* mapa, void* key, void* value );

void insertarPokemon( Mapa* TipoBox, Mapa* NameBox, Mapa* IdBox, Mapa* RegionBox, Lista* mayorPC, Lista* mayorPS, Mapa* NamePoke, Lista* NumPoke, Pokemon* newP, InfoPokemon* newIP );

//Funciones principales

void ImportarArchivo( Mapa* TipoBox, Mapa* NameBox, Mapa* IdBox, Mapa* RegionBox, Lista* mayorPC, Lista* mayorPS, Mapa* NamePoke, Lista* NumPoke );

void ExportarArchivo( Mapa* IdBox, Mapa* NamePoke);

void AtraparPokemon( Mapa* TipoBox, Mapa* NameBox, Mapa* IdBox, Mapa* RegionBox, Lista* mayorPC, Lista* mayorPS, Mapa* NamePoke, Lista* NumPoke );

void LiberarPokemon( Mapa* TipoBox, Mapa* NameBox, Mapa* IdBox, Mapa* RegionBox, Lista* mayorPC, Lista* mayorPS, Mapa* NamePoke );

//almacenamiento

void BuscarPokemonBox( Mapa* mapa, int ind );

void MostrarPokemonLista( Lista* L, int ind );

void MostrarRegion( Mapa* RegionBox);

//Pokedex

void BuscarNombrePokedex( Mapa* NamePoke );

void MostrarPokedex( Lista* L );

#endif
