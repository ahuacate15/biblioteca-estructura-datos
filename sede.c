#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "texto.h"

#define TRUE 1
#define FALSE 0

typedef struct sede {
    int id;
    char *nombre;
    char *departamento;
    char *telefono;
    char *correo;
    char *direccion;
    struct sede *siguiente;
    struct sede *anterior;
} Sede;

typedef struct listaSede {
    int total;
    Sede *primero;
    Sede *ultimo;
} ListaSede;

/*-----------prototipos de funciones estandar----------*/
ListaSede *initListSede();
Sede *initSede();
Sede *appendSede(ListaSede *lista, Sede *sede); //agregar una sede al final de la lista, retorna el nodo creado
int isEmptyListSede(ListaSede *lista); //compruebo si la lista se encuentra vacia
Sede *getSede(ListaSede *lista, int id); //obtengo la sede segun el id
int removeSede(ListaSede *lista, int id); //elimino una sede segun el id

/*--------prototipo de funciones para interfaz --------*/
void requestNewSede(ListaSede *lista); //solicito los datos de una sede y la agrego a la lista
void printListSedes(ListaSede *lista);
void printListSedesMinuature(ListaSede *lista);
ListaSede *cargarSedesDefecto(ListaSede *lista);

ListaSede *initListSede() {
    ListaSede *lista = malloc(sizeof(ListaSede));
    lista->total = 0;
    lista->primero = NULL;
    lista->ultimo = NULL;
    return lista;
}

Sede *initSede() {
    Sede *sede = malloc(sizeof(Sede));
    sede->nombre = malloc(sizeof(char) * 60); //maximo 60 caracteres
    sede->departamento = malloc(sizeof(char) * 30); //maximo 30 caracteres
    sede->telefono = malloc(sizeof(char) * 10); //maximo 10 caracteres
    sede->correo = malloc(sizeof(char) * 60); //maximo 60 caracteres
    sede->direccion = malloc(sizeof(char) * 254); //maximo 254 caracteres
    sede->siguiente = NULL;
    sede->anterior = NULL;
    return sede;
}

//agregar una sede al final de la lista, retorna el nodo creado
Sede *appendSede(ListaSede *lista, Sede *sede) {
    Sede *aux;
    sede->id = lista->total + 1; //asigno ID autoincrementable

    if(lista->total == 0) {
        lista->primero = sede;
        lista->ultimo = sede;
        lista->total = 1;
    } else {
        aux = lista->ultimo;
        aux->siguiente = sede;
        sede->anterior = aux;
        lista->ultimo = sede;
        lista->total++;
    }

    return sede;
}

//compruebo si la lista se encuentra vacia
int isEmptyListSede(ListaSede *lista) {
    if(lista == NULL || lista->total == 0)
        return TRUE;
    else
        return FALSE;
}

//obtengo la sede segun el id
Sede *getSede(ListaSede *lista, int id) {
    Sede *primero, *resultado = NULL;
    int cont = 1;

    primero = lista->primero;
    while(primero != NULL) {
        if(cont == id) {
            resultado = primero;
            break;
        }

        primero = primero->siguiente;
        cont++;
    }
}

//elimino una sede segun el id
int removeSede(ListaSede *lista, int id) {
    Sede *sede = NULL;
    int cont = 0, encontrado = FALSE;

    if(lista == NULL)
        return FALSE;

    sede = lista->primero;

    if(lista->total == 1) { //eliminar el unico elemento de la lista
        free(lista->primero);
        lista = initListSede();
    } else {  //la lista contiene mas de un elemento

        sede = lista->primero;
        for(int i=0; i<lista->total; i++) {
            if(sede->id == id) { //busco un elemento por ID
                encontrado = TRUE;
                break;
            }
            sede = sede->siguiente;
        }

        if(!encontrado)
            return FALSE;

        if(sede->id == lista->primero->id) { //primer elemento de la lista
            lista->primero = sede->siguiente;
            lista->total--;
            free(sede);
        } else if(sede->id == lista->ultimo->id) { //ultimo elemento de la lista
            sede->anterior->siguiente = NULL;
            lista->ultimo = sede->anterior;
            lista->total--;
            free(sede);
        } else { //elementos que no se ubican en los extremos
            sede->anterior->siguiente = sede->siguiente;
            lista->total--;
            free(sede);
        }

        return TRUE;
    }

}

//solicito los datos de una sede y la agrego a la lista
void requestNewSede(ListaSede *lista) {
    Sede *sede = initSede();
    printf("\ningresa los datos de la sede\n");

    printf("nombre: ");
    sede->nombre = getLine(60);

    printf("departamento: ");
    sede->departamento = getLine(30);

    printf("telefono: ");
    sede->telefono = getLine(10);

    printf("correo electronico: ");
    sede->correo = getLine(60);

    printf("direccion: ");
    sede->direccion = getLine(254);

    printf("Elemento guardado con el ID: %d\n", appendSede(lista, sede)->id);
}

void printListSedes(ListaSede *lista) {
    Sede *sede = lista->primero;

    printf("\nTotal de registros: %d\n", lista->total);
    while(sede != NULL) {
        printf("id: %d\n", sede->id);
        printf("nombre: %s\n", sede->nombre);
        printf("departamento: %s\n", sede->departamento);
        printf("telefono: %s\n", sede->telefono);
        printf("correo: %s\n", sede->correo);
        printf("direccion: %s\n", sede->direccion);
        printf("\n");

        sede = sede->siguiente;
    }
}

void printListSedesMinuature(ListaSede *lista) {
    Sede *sede = lista->primero;

    while(sede != NULL) {
        printf("%d- %s\n", sede->id, sede->nombre);
        sede = sede->siguiente;
    }
}

ListaSede *cargarSedesDefecto(ListaSede *lista) {
    Sede *sede1 = initSede();
    sede1->nombre = "ITCA santa tecla";
    sede1->departamento = "La libertad";
    sede1->telefono = "2132-7400";
    sede1->correo = "biblioteca.santatecla@itca.edu.sv";
    sede1->direccion = "Carretera a Santa Tecla km. 11, La Libertad, El Salvador";
    appendSede(lista, sede1);

    Sede *sede2 = initSede();
    sede2->nombre = "ITCA santa ana";
    sede2->departamento = "Santa ana";
    sede2->telefono = "2440-4348";
    sede2->correo = "biblioteca.santaana@itca.edu.sv";
    sede2->direccion = "Cuadra y media al sur del Estadio Óscar Quiteño";
    appendSede(lista, sede2);

    Sede *sede3 = initSede();
    sede3->nombre = "ITCA san miguel";
    sede3->departamento = "San miguel";
    sede3->telefono = "2669-2298";
    sede3->correo = "biblioteca.sanmiguel@itca.edu.sv";
    sede3->direccion = "Km. 140 Carretera a Santa Rosa de Lima";
    appendSede(lista, sede3);

    return lista;
}
