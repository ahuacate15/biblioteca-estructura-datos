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

/*-----------definicion de funciones----------*/
/*
int main() {
    ListaSede *lista = initListSede();

    requestNewSede(lista);
    //requestNewSede(lista);
    printListSedes(lista);

    return 0;
}
*/
