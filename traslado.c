#include <stdio.h>
#include <stdlib.h>
#include "libro.h"
#include "sede.h"

#define TRUE 1
#define FALSE 0

int verificarExistenciasLibro(Libro *libro, Sede *sede); //obtiene las existencias de un libro en una sede determinada
void realizarTrastadoMenu(Arbol *arbol, ListaSede *lista);

int verificarExistenciasLibro(Libro *libro, Sede *sede) {
    if(libro == NULL || sede == NULL)
        return -1;

    if(libro->libroSede == NULL)
        return -1;

    Sede *tmp = libro->libroSede->sede;

    //busco la sede en la lista de sedes relacionadas al libro
    while(tmp != NULL) {
        if(tmp->id == sede->id)
            return libro->libroSede->copias;
        tmp = tmp->siguiente;
    }

    return 0;
}

void realizarTrastadoMenu(Arbol *arbol, ListaSede *lista) {
    Sede *origen = NULL, *destino = NULL;
    int idSedeOrigen = 0, idSedeDestino = 0, copias = 0, campoBusqueda = 0;
    Nodo *raiz = NULL;
    char *filtro = malloc(sizeof(char) * 256);

    printf(" ----------------------------------------------------------- \n");
	printf("|                           TRASLADOS                       |\n");
	printf(" ----------------------------------------------------------- \n\n");

    stateBusquedaLibro:;
    printf("elige el campo de busqueda para el libro: \n");
    printf("1)titulo \t2)ISBN\n");
    printf("\n>> ");
    if(scanf("%d", &campoBusqueda) == 0) {
        printf("la opcion ingresada es incorrecta\n");
        fflush(stdin);
        goto stateBusquedaLibro;
    }

    if(campoBusqueda != 1 && campoBusqueda != 2) {
        printf("la opcion ingresada es incorrecta\n");
        fflush(stdin);
        goto stateBusquedaLibro;
    }

	fflush(stdin);
    if(campoBusqueda == TITULO) {
        printf("ingresa el titulo del libro: ");
        filtro = getLine(256);
        raiz = arbol->raiz;
    } else { //busqueda por ISBN
        printf("ingresa el ISBN del libro: ");
        filtro = getLine(20);
        raiz = arbol->raizISBN;
    }


    Nodo *nodo = buscarLibroPorClave(raiz, filtro);
    if(nodo == NULL) {
        printf("\n***no se encontraron resultados\n\n");
        return;
    } else {
        printCopiasPorSede(nodo->libro);
    }

    printf("\n");
    stateSedeOrigen:;
    printf("ingresa el ID de la sede origen: ");

    if(scanf("%d", &idSedeOrigen) == 0) {
        printf("la opcion ingresada es incorrecta\n\n");
        fflush(stdin);
        goto stateSedeOrigen;
    }
    origen = getSede(lista, idSedeOrigen);
    if(origen == NULL) {
        printf("la sede ingresada no existe\n\n");
        goto stateSedeOrigen;
    }

    stateSedeDestino:;
    printf("ingresa el ID de la sede destino: ");
    if(scanf("%d", &idSedeDestino) == 0) {
        printf("la opcion ingresada es incorrecta\n\n");
        fflush(stdin);
        goto stateSedeDestino;
    }

    destino = getSede(lista, idSedeDestino);
    if(destino == NULL) {
        printf("la sede ingresada no existe\n\n");
        goto stateSedeDestino;
    }

    if(idSedeOrigen == idSedeDestino) {
        printf("no puedes realizar traslados hacia una misma sede\n\n");
        goto stateSedeOrigen;
    }

    stateExistencias:;
    printf("ingresa la cantidad de copias a trasladar: ");
    if(scanf("%d", &copias) == 0) {
        printf("la opcion ingresada es incorrecta\n\n");
        fflush(stdin);
        goto stateExistencias;
    }

    if(copias > verificarExistenciasLibro(nodo->libro, origen)) {
            printf("la sede '%s' no cuenta con suficientes copias para realizar el traslado\n\n", origen->nombre);
            goto stateExistencias;
    }

    //saco las copias de la sede origen
    addLibroSedeItem(nodo->libro, origen, copias * -1);
    //recibo las copias en la sede destino
    addLibroSedeItem(nodo->libro, destino, copias);
    printf("\n***traslado completao con exito***\n\n");
}
