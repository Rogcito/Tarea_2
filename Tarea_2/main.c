#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "TDA&CSV/Lista.h"
#include "TDA&CSV/Mapa.h"

#include "FunMain.h"

#define min 20

void menuIE( Mapa* TipoBox, Mapa* NameBox, Mapa* IdBox, Mapa* RegionBox, Lista* mayorPC, Lista* mayorPS, Mapa* NamePoke, Lista* NumPoke );
void menuAlmacenamiento( Mapa* TipoBox, Mapa* NameBox, Mapa* RegionBox, Lista* mayorPC, Lista* mayorPS, Mapa* NamePoke );
void menuPokedex( Mapa* NamePoke, Lista* NumPoke );

int main(){
    system("COLOR A");

    Mapa* TipoBox = crearMapa(min);
    Mapa* NameBox = crearMapa(min);
    Mapa* IdBox = crearMapa(min);
    Mapa* RegionBox = crearMapa(min);
    Lista* mayorPC = crearLista();
    Lista* mayorPS = crearLista();

    Mapa* NamePoke = crearMapa(min);
    Lista* NumPoke = crearLista();

    int opcion;

    do{
        system("cls");
        printf("\n\t\tPOKEMON\n\n");

        printf("   1-.Importar/Exportar Archivo\n");
        printf("   2-.Atrapar Pokemon\n");
        printf("   3-.Liberar Pokemon\n");
        printf("   4-.Almacenamiento\n");
        printf("   5-.Pokedex\n");
        printf("   6-.Salir\n");
        printf("   Opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch(opcion){
            case 1:
                menuIE(TipoBox, NameBox, IdBox, RegionBox, mayorPC, mayorPS, NamePoke, NumPoke );
            break;
            case 2:
                AtraparPokemon( TipoBox, NameBox, IdBox, RegionBox, mayorPC, mayorPS, NamePoke, NumPoke );
            break;
            case 3:
                LiberarPokemon( TipoBox, NameBox, IdBox, RegionBox, mayorPC, mayorPS, NamePoke );
            break;
            case 4:
                menuAlmacenamiento( TipoBox, NameBox, RegionBox, mayorPC, mayorPS, NamePoke );
            break;
            case 5:
                menuPokedex( NamePoke, NumPoke);
            break;
        }
        if( opcion != 6){  //para que no guarde la ultima eleccion
            opcion = 0;
        }
    }while( opcion != 6);

    return 0;
}

void menuIE( Mapa* TipoBox, Mapa* NameBox, Mapa* IdBox, Mapa* RegionBox, Lista* mayorPC, Lista* mayorPS, Mapa* NamePoke, Lista* NumPoke){
    int opcion;

    do{
        system("cls");
        printf("\n\tARCHIVO\n\n");

        printf("   1-.Importar Archivo\n");
        printf("   2-.Exportar Archivo\n");
        printf("   3-.Atras\n");
        printf("   Opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch( opcion ){
            case 1:
                ImportarArchivo(TipoBox, NameBox, IdBox, RegionBox, mayorPC, mayorPS, NamePoke, NumPoke);
            break;
            case 2:
                ExportarArchivo(IdBox, NamePoke);
            break;
        }
        if(opcion != 3){ //para que no guarde la ultima eleccion
            opcion = 0;
        }

    }while( opcion != 3);
}

void menuAlmacenamiento( Mapa* TipoBox, Mapa* NameBox, Mapa* RegionBox, Lista* mayorPC, Lista* mayorPS, Mapa* NamePoke ){
    int opcion;

    do{
        system("cls");
        printf("\n\tALMACENAMIENTO POKEMON\n\n");

        printf("   1-.Buscar Pokemones por nombre\n");
        printf("   2-.Buscar Pokemones por tipo\n");
        printf("   3-.Mostrar Pokemones por mayor PC\n");
        printf("   4-.Mostrar Pokemones por mayor PS\n");
        printf("   5-.Mostrar Pokemones por region\n");
        printf("   6-.Atras\n");
        printf("   Opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch( opcion ){
            case 1:
                BuscarPokemonBox(NameBox, 0);
            break;
            case 2:
                BuscarPokemonBox(TipoBox, 1);
            break;
            case 3:
                MostrarPokemonLista(mayorPC, 0);
            break;
            case 4:
                MostrarPokemonLista(mayorPS, 1);
            break;
            case 5:
                MostrarRegion( RegionBox);
            break;
        }
        if(opcion != 6){ //para que no guarde la ultima eleccion
            opcion = 0;
        }

    }while( opcion != 6);
}

void menuPokedex( Mapa* NamePoke, Lista* NumPoke){
    int opcion;

    do{
        system("cls");
        printf("\n\tPOKEDEX\n\n");

        printf("   1-.Buscar Pokemon por nombre\n");
        printf("   2-.Mostrar Pokedex\n");
        printf("   3-.Atras\n");
        printf("   Opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch( opcion ){
            case 1:
                BuscarNombrePokedex( NamePoke );
            break;
            case 2:
                MostrarPokedex( NumPoke );
            break;
        }
        if(opcion != 3){ //para que no guarde la ultima eleccion
            opcion = 0;
        }

    }while( opcion != 3);
}








