
#include "FunMain.h"

void lowerCase (char* str){
	for(int i=0; str[i]!='\0'; i++){
		str[i] = tolower(str[i]);
	}
}

void removeSpacesInPlace (char* str) {

	size_t str_len = strlen(str); // para tener strlen se debe incluir <string.h>
	char result [str_len];
	size_t p = 0;

	size_t i = 0;
	for (i = 0; i < str_len; ++i) {
		if (str[i] != ' ') {
			// result necesita su propio posicionador o iremos dejando agujeros
			result[p] = str[i];

			// Sólo avanzamos la posición p si se realiza la inserción
			p++;
		}
	}

	// funciones como printf buscan el caracter 0
	// aunque dejamos str con el mismo tamaño en memoria, ponemos la
	// marca de fin de la cadena en donde corresponde
	if (p < str_len)
		str[p] = '\0';

	// Reescribimos str con el contenido de result
	for (i = 0; i < p; ++i) {
		str[i] = result[i];
	}
}

void arreglarString(char* str){
    lowerCase( str );
    removeSpacesInPlace( str );

    if( strcmp(str, "notiene") == 0){
        strcpy(str, "No tiene");
    }else{

        str[0] = toupper(str[0]);
        int ind = 0;

        for(int i=0; str[i]!='\0'; i++){
            if( ind == 1 ){
                str[i] = toupper(str[i]);
                ind = 0;
            }else if( str[i] == ',' ){
                ind = 1;
            }
        }
    }
}

/** toma un string separado por comas y retorna una lista enlazada con los datos separados en nodos */
void* vectorizarTipos( const char* str){
    Lista* newL = crearLista();

    char texto[max];
    strcpy( texto, str);
    char delimitador[] = ",";

    char* token = strtok( texto, delimitador);
    if(token != NULL){
        while( token != NULL){
            NombreTipos* newNT = CrearNombreTipos( token );
            pushBackL(newL, newNT);
            token = strtok(NULL, delimitador);
        }
    }

    return newL;
}

int obtenerID( Mapa* IdBox ){
    for( int i = 1; i<101; i++){
        char num[max];
        sprintf(num, "%d", i); //transforma el int a un string
        if( searchMap(IdBox, num ) == NULL ){
            return i;
        }
    }
    return 101;
}

//------------------------------

void ListaOrdenadaPC( Lista* L, Pokemon* P){
    Pokemon* auxP = firstL( L );
    while(auxP != NULL){
        if( P->PC > auxP->PC ){
            pushCurrentL( L, P);
            return;
        }
        auxP = nextL( L );
    }
    pushBackL( L, P);
}

void ListaOrdenadaPS( Lista* L, Pokemon* P){
    Pokemon* auxP = firstL( L );
    while(auxP != NULL){
        if( P->PS > auxP->PS ){
            pushCurrentL( L, P);
            return;
        }
        auxP = nextL( L );
    }
    pushBackL( L, P);
}

void ListaOrdenadaNP( Lista* L, InfoPokemon* IP){
    InfoPokemon* auxIP = firstL( L );
    while(auxIP != NULL){
        if( IP->numPokedex < auxIP->numPokedex ){
            pushCurrentL( L, IP);
            return;
        }
        auxIP = nextL( L );
    }
    pushBackL( L, IP);
}

//------------------------------

void insertarListaMapa( Mapa* mapa, void* key, void* value ){
    Lista* auxL = searchMap(mapa, key);
    if( auxL == NULL ){
        Lista* newL = crearLista();
        pushBackL(newL, value);
        insertMap(mapa, key, newL);
    }else{
        pushBackL(auxL, value);
    }
}

void insertarPokemon( Mapa* TipoBox, Mapa* NameBox, Mapa* IdBox, Mapa* RegionBox, Lista* mayorPC, Lista* mayorPS, Mapa* NamePoke, Lista* NumPoke, Pokemon* newP, InfoPokemon* newIP ){
    //insertar en mapa tipos
    Lista* auxL = newIP->listaTipos;
    NombreTipos* tipo = firstL(auxL);
    while( tipo != NULL){
        insertarListaMapa(TipoBox, tipo->Nombre, newP);
        tipo = nextL(auxL);
    }
    //insertar en mapa namebox (ALMACENAMIENTO)
    insertarListaMapa(NameBox, newP->nombre, newP);
    //insertar en mapa IdBox
    insertMap(IdBox, newP->id, newP);
    //insertar en sortedMap mayorPC
    ListaOrdenadaPC( mayorPC, newP);
    //insertar en sortedMap mayorPS
    ListaOrdenadaPS( mayorPS, newP);

    //insertar en mapa namePoke (POKEDEX)
    InfoPokemon* auxP = searchMap(NamePoke, newIP->nombre);
    if( auxP == NULL){
        insertMap(NamePoke, newIP->nombre, newIP);
        //insertar en mapa numPoke
        ListaOrdenadaNP(NumPoke, newIP);
        //insertar en mapa region
        insertarListaMapa(RegionBox, newIP->region, newIP);
    }else{
        auxP->cantidad++;
    }
}

void eliminarListaMapa( Mapa* mapa, void* key, char* ID){
    Lista* LP = searchMap(mapa, key);
    Pokemon* auxLP = firstL(LP);
    while(auxLP != NULL){
        if( strcmp(auxLP->id, ID) == 0 ){
            deleteCurrentL(LP);
            break;
        }
        auxLP = nextL(LP);
    }
}

void eliminarListaOrdenada( Lista* L, char* ID ){
    Pokemon* auxP = firstL(L);
    while( auxP != NULL ){
        if( strcmp(auxP->id, ID) == 0 ){
            deleteCurrentL(L);
            break;
        }
        auxP = nextL(L);
    }
}

//Funciones Principales

void ImportarArchivo( Mapa* TipoBox, Mapa* NameBox, Mapa* IdBox, Mapa* RegionBox, Lista* mayorPC, Lista* mayorPS, Mapa* NamePoke, Lista* NumPoke ){
    system("cls");

    char archivo[max], nombre[max], tipos[max], sexo[max], evoPrevia[max], evoPost[max], region[max] ;
    int numPokedex = -1, PC = -1, PS = -1;

  	printf("\n\t\tCARGAR LISTA POKEMON\n\n");

  	printf("   Nombre del archivo(sin.csv): ");
  	gets( archivo );
  	strcat(archivo,".csv");

  	FILE* L_POKEMON = fopen( archivo, "r");

    if( L_POKEMON == NULL){
        printf("\n   Archivo NO existe\n\n");
    }else{
        int ind = 0;
        char linea[1024];
        printf("\n   Procesando archivo...\n");

        while( fgets(linea, 1023, L_POKEMON) != NULL ){

            const char * Nombre = get_csv_field( linea, 1);
            const char * Tipos = get_csv_field( linea, 2);
            PC = atoi( get_csv_field(linea, 3) );
            PS = atoi( get_csv_field(linea, 4) );
            const char * Sexo = get_csv_field(linea, 5);
            const char * EvoPrevia = get_csv_field( linea, 6);
            const char * EvoPost = get_csv_field( linea, 7);
            numPokedex = atoi( get_csv_field(linea, 8) );
            const char * Region = get_csv_field( linea, 9);

            //evita warnings
            strcpy(nombre, Nombre);
            strcpy(tipos, Tipos);
            strcpy(sexo, Sexo);
            strcpy(evoPrevia, EvoPrevia);
            strcpy(evoPost, EvoPost);
            strcpy(region, Region);

            arreglarString(nombre);
            arreglarString(tipos);
            arreglarString(sexo);
            arreglarString(evoPrevia);
            arreglarString(evoPost);
            arreglarString(region);

            if( sizeMap(IdBox) == 100){
                ind = 1;
                printf("\n");
            }

            if( ind == 0){
                if( (strcmp(nombre,"") != 0)&&(strcmp(tipos,"") != 0 )&&(PC >= 0)&&(PS >= 0)&&( (strcmp(sexo,"Macho") == 0)||(strcmp(sexo,"Hembra") == 0)||(strcmp(sexo,"No tiene") == 0) )&&(strcmp(evoPrevia,"") != 0)&&(strcmp(evoPost,"") != 0)&&(numPokedex >= 0)&&(strcmp(region,"") != 0) ){

                    char id[max];
                    sprintf( id, "%d", obtenerID( IdBox ));

                    Pokemon* newP = crearPokemon( id, nombre, sexo, PC, PS);
                    InfoPokemon* newIP = crearInfoPokemon( nombre, vectorizarTipos(tipos), evoPrevia, evoPost, numPokedex, region);

                    insertarPokemon(TipoBox, NameBox, IdBox, RegionBox, mayorPC, mayorPS, NamePoke, NumPoke, newP, newIP);

                }
            }else{
                printf("    %s, -%s-, %d, %d, %s, %s, %s, %d, %s\n", nombre, tipos, PC, PS, sexo, evoPrevia, evoPost, numPokedex, region);
            }
        }
        fclose( L_POKEMON);
        if( ind == 1){
            printf("\n   -Estos Pokemones NO fueron ingresados debido a que el almacenamiento se encuentra lleno-\n\n");
        }
        printf("   Archivo finalizado\n");
    }

    printf("\n");
    system("pause");
}

void ExportarArchivo( Mapa* IdBox, Mapa* NamePoke){
    system("cls");

    char archivo[max];
    printf("\n\t\tEXPORTAR POKEMONES A UN ARCHIVO\n\n");

    if( sizeMap(IdBox) == 0 ){
        printf("   ERROR::No existen Pokemones para exportar\n");
    }else{
        printf("   Nombre del archivo(sin.csv): ");
        gets( archivo );
        strcat(archivo,".csv");

        FILE* POKEMONES = fopen( archivo, "w");
        fprintf(POKEMONES,"id,nombre,tipos,pc,ps,sexo,evolucion previa,evolucion posterior,numero pokedex,region\n");

        for( int i = 1; i<101; i++){
            char num[max];
            sprintf(num, "%d", i); //transforma el int a un string
            Pokemon* auxP = searchMap(IdBox, num );
            if( auxP != NULL ){
                InfoPokemon* auxIP = searchMap(NamePoke, auxP->nombre);

                fprintf(POKEMONES,"%s,%s,%c",auxP->id, auxP->nombre,34);

                Lista* tipos = auxIP->listaTipos;
                NombreTipos* name = firstL(tipos);
                while(name != NULL){
                    fprintf(POKEMONES,"%s", name->Nombre);
                    name = nextL(tipos);
                    if(name != NULL){
                        fprintf(POKEMONES,",");
                    }
                }

                fprintf(POKEMONES,"%c,%d,%d,%s,%s,%s,%d,%s\n",34,auxP->PC,auxP->PS,auxP->sexo,auxIP->evoPrevia,auxIP->evoPosterior,auxIP->numPokedex,auxIP->region);
            }
        }
        fclose(POKEMONES);

        printf("\n   Pokemones exportados Correctamente\n");
    }

    printf("\n");
    system("pause");
}

void AtraparPokemon( Mapa* TipoBox, Mapa* NameBox, Mapa* IdBox, Mapa* RegionBox, Lista* mayorPC, Lista* mayorPS, Mapa* NamePoke, Lista* NumPoke ){
    system("cls");

    char nombre[max], tipos[max], sexo[max], evoPrevia[max], evoPost[max], region[max];
    int PC, PS, numPokedex;

    printf("\n\t\tPOKEMON ATRAPADO\n\n");

    printf("    Nombre Pokemon              : ");
    gets(nombre);
    printf("    Tipos(separar por comas)    : ");
    gets(tipos);
    printf("    Puntos de Combate(PC)       : ");
    scanf("%d", &PC );
    printf("    Puntos de Salud(PC)         : ");
    scanf("%d", &PS );
    getchar();
    printf("    Sexo(Macho/Hembra/No tiene) : ");
    gets(sexo);
    printf("    Evolucion Previa(si no exite ingresar: No Tiene)    : ");
    gets(evoPrevia);
    printf("    Evolucion Posterior(si no exite ingresar: No Tiene) : ");
    gets(evoPost);
    printf("    Numero en la Pokedex        : ");
    scanf("%d", &numPokedex );
    getchar();
    printf("    Region del Pokemon          : ");
    gets(region);

    arreglarString(nombre);
    arreglarString(tipos);
    arreglarString(sexo);
    arreglarString(evoPrevia);
    arreglarString(evoPost);
    arreglarString(region);

    if( (strcmp(nombre,"") != 0)&&(strcmp(tipos,"") != 0 )&&(PC >= 0)&&(PS >= 0)&&( (strcmp(sexo,"Macho") == 0)||(strcmp(sexo,"Hembra") == 0)||(strcmp(sexo,"No tiene") == 0) )&&(strcmp(evoPrevia,"") != 0)&&(strcmp(evoPost,"") != 0)&&(numPokedex >= 0)&&(strcmp(region,"") != 0) ){

        if( sizeMap( IdBox ) == 100 ){
            printf("\n   -ERROR::Almacenamiento Completo\n");

            printf("\n");
            system("pause");
            return;

        }else{
            char id[max];
            sprintf( id, "%d", obtenerID( IdBox ));

            Pokemon* newP = crearPokemon( id, nombre, sexo, PC, PS);
            InfoPokemon* newIP = crearInfoPokemon( nombre, vectorizarTipos(tipos), evoPrevia, evoPost, numPokedex, region);

            insertarPokemon(TipoBox, NameBox, IdBox, RegionBox, mayorPC, mayorPS, NamePoke, NumPoke, newP, newIP);
        }
    }else{
        printf("\n   -ERROR::Datos Incorrectos\n");
    }

    printf("\n   -Pokemon Atrapado Correctamente\n");

    printf("\n");
    system("pause");
}

void LiberarPokemon( Mapa* TipoBox, Mapa* NameBox, Mapa* IdBox, Mapa* RegionBox, Lista* mayorPC, Lista* mayorPS, Mapa* NamePoke ){
    system("cls");

    char ID[max];
    int id;

    printf("\n\tLIBERAR POKEMON\n\n");

    printf("    ID del Pokemon  : ");
    scanf("%d", &id);
    getchar();

    if( id > 0 ){
        sprintf( ID, "%d", id);

        Pokemon* auxP = searchMap( IdBox, ID);
        if( auxP != NULL ){
            //restar 1 al pokemon en la pokedex
            InfoPokemon* auxIP = searchMap( NamePoke, auxP->nombre );
            if( auxIP->cantidad > 0 ){
                auxIP->cantidad--;
            }

            //eliminar pokemon en tipos
            Lista* L = auxIP->listaTipos;
            NombreTipos* tipo = firstL(L);
            while( tipo != NULL){
                eliminarListaMapa( TipoBox, tipo->Nombre, ID);
                tipo = nextL(L);
            }

            //eliminar pokemon en nombres
            eliminarListaMapa( NameBox, auxP->nombre, ID);
            //eliminar pokemon por region
            eliminarListaMapa( RegionBox, auxIP->region, ID);

            //eliminar en las listas
            eliminarListaOrdenada(mayorPC, ID);
            eliminarListaOrdenada(mayorPS, ID);

            //eliminar en el mapa ID
            deleteKeyMap( IdBox, auxP->id);

            free(auxP);

            printf("\n   -Pokemon Liberado Correctamente\n");
        }else{
            printf("\n   -ERROR::Pokemon NO Existe\n");
        }
    }else{
        printf("\n   -ERROR::Datos Incorrectos\n");
    }

    printf("\n");
    system("pause");
}

//Almacenamiento

void BuscarPokemonBox( Mapa* mapa, int ind ){
    system("cls");
    char valor[max];

    if( ind == 0){
        printf("\n   BUSCAR POKEMONES POR NOMBRE EN EL ALMACENAMIENTO\n\n\n");
        printf("    Nombre del Pokemon   : ");
        gets(valor);
    }else{
        printf("\n   BUSCAR POKEMONES POR TIPO EN EL ALMACENAMIENTO\n\n\n");
        printf("    Tipo del Pokemon     : ");
        gets(valor);
    }

    arreglarString(valor);

    Lista* L = searchMap( mapa, valor );
    if( L == NULL ){
        if( ind == 0){
            printf("\n   -ERROR::NO existen Pokemones con ese Nombre\n");
        }else{
            printf("\n   -ERROR::NO existen Pokemones con ese Tipo\n");
        }
    }else{
        printf("\n");
        Pokemon* auxP = firstL(L);
        while( auxP != NULL ){

            printf("   ID                    : %s\n", auxP->id);
            printf("   Nombre                : %s\n", auxP->nombre);
            printf("   Puntos de Combate(PC) : %d\n", auxP->PC);
            printf("   Puntos de Salud(PS)   : %d\n", auxP->PS);
            printf("   Sexo                  : %s\n", auxP->sexo);
            printf("\n---------------------------------------\n");

            auxP = nextL(L);
        }
    }

    printf("\n");
    system("pause");
}

void MostrarPokemonLista( Lista* L, int ind ){
    system("cls");

    if( ind == 0){
        printf("\n\tPOKEMONES POR MAYOR PC(puntos de combate)\n\n\n");
    }else{
        printf("\n\tPOKEMONES POR MAYOR PS(puntos de salud)\n\n\n");
    }



    Pokemon* auxP = firstL( L );
    if( auxP == NULL ){
        printf("   -ERROR::Almacenamiento Vacio\n");
    }else{
        while( auxP != NULL){

            printf("   ID                    : %s\n", auxP->id);
            printf("   Nombre                : %s\n", auxP->nombre);
            printf("   Puntos de Combate(PC) : %d\n", auxP->PC);
            printf("   Puntos de Salud(PS)   : %d\n", auxP->PS);
            printf("   Sexo                  : %s\n", auxP->sexo);
            printf("\n---------------------------------------\n");

            auxP = nextL( L );
        }
    }

    printf("\n");
    system("pause");
}

void MostrarRegion( Mapa* RegionBox){
    system("cls");

    printf("\n\tPOKEMONES POR REGION\n\n\n");

    Lista* L = firstMap(RegionBox);
    if( L == NULL){
        printf("   -ERROR::Almacenamiento Vacio\n");
    }else{
        while( L != NULL){
            int cont = 0;
            printf("\n---------------------------------------\n");

            InfoPokemon* auxP = firstL(L);
            printf("   Region                     : %s\n", auxP->region);
            while(auxP != NULL){
                cont += auxP->cantidad;
                auxP = nextL(L);
            }
            printf("   Cantidad en Almacenamiento : %d Pokemones\n\n", cont);

            auxP = firstL(L);
            while( auxP != NULL){

                printf("   Nombre                : %s\n", auxP->nombre);
                printf("   Existencia            : %d\n", auxP->cantidad);

                printf("   Tipos                 : ");
                Lista* tipos = auxP->listaTipos;
                NombreTipos* name = firstL(tipos);
                while(name != NULL){
                    printf("%s", name->Nombre);
                    name = nextL(tipos);
                    if( name != NULL){
                        printf(",");
                    }else{
                        printf("\n");
                    }
                }

                printf("   Evolucion Previa      : %s\n", auxP->evoPrevia);
                printf("   Evolucion Posterior   : %s\n", auxP->evoPosterior);
                printf("   Numero en la Pokedex  : %d\n", auxP->numPokedex);
                printf("\n---------------------------------------\n");

                auxP = nextL(L);
            }

            L = nextMap(RegionBox);
        }
    }

    printf("\n");
    system("pause");
}

//Pokedex

void BuscarNombrePokedex( Mapa* NamePoke ){
    system("cls");

    char nombre[max];

    printf("\n\tBUSCAR POKEMON EN LA POKEDEX\n\n\n");

    printf("    Nombre del Pokemon   : ");
    gets(nombre);

    arreglarString(nombre);

    if( strcmp(nombre, "") != 0 ){
        InfoPokemon* auxP = searchMap(NamePoke, nombre);
        if( auxP == NULL ){
            printf("\n   -ERROR::Pokemon NO Existe\n");
        }else{

            printf("\n    Nombre                : %s\n", auxP->nombre);
            printf("    Existencia            : %d\n", auxP->cantidad);

            printf("    Tipos                 : ");
            Lista* tipos = auxP->listaTipos;
            NombreTipos* name = firstL(tipos);
            while(name != NULL){
                printf("%s", name->Nombre);
                name = nextL(tipos);
                if( name != NULL){
                    printf(",");
                }else{
                    printf("\n");
                }
            }

            printf("    Evolucion Previa      : %s\n", auxP->evoPrevia);
            printf("    Evolucion Posterior   : %s\n", auxP->evoPosterior);
            printf("    Numero en la Pokedex  : %d\n", auxP->numPokedex);
            printf("    Region                : %s\n", auxP->region);
        }
    }else{
        printf("\n   -ERROR::Datos Incorrectos\n");
    }

    printf("\n");
    system("pause");
}

void MostrarPokedex( Lista* L ){
    system("cls");

    printf("\n\t\tPOKEDEX\n\n\n");

    InfoPokemon* auxP = firstL( L );
    if( auxP == NULL ){
        printf("   -ERROR::Pokedex Sin Datos\n");
    }else{
        while( auxP != NULL){

            printf("   Nombre                : %s\n", auxP->nombre);
            printf("   Existencia            : %d\n", auxP->cantidad);

            printf("   Tipos                 : ");
            Lista* tipos = auxP->listaTipos;
            NombreTipos* name = firstL(tipos);
            while(name != NULL){
                printf("%s", name->Nombre);
                name = nextL(tipos);
                if( name != NULL){
                    printf(",");
                }else{
                    printf("\n");
                }
            }

            printf("   Evolucion Previa      : %s\n", auxP->evoPrevia);
            printf("   Evolucion Posterior   : %s\n", auxP->evoPosterior);
            printf("   Numero en la Pokedex  : %d\n", auxP->numPokedex);
            printf("   Region                : %s\n", auxP->region);
            printf("\n---------------------------------------\n");

            auxP = nextL( L );
        }
    }

    printf("\n");
    system("pause");
}

