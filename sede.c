#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
Prueba
/*-----------definicion de estructuras----------*/
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

/*--------prototipo de funciones para interfaz --------*/
void printListSedes(ListaSede *lista);

/*-----------prototipos de funciones estandar----------*/
ListaSede *initListSede(); 
Sede *initSede();
void appendSede(ListaSede *lista, Sede *sede); //agregar una sede al final de la lista
int isEmptyListSede(ListaSede *lista); //compruebo si la lista se encuentra vacia
Sede *getSede(ListaSede *lista, int id); //obtengo la sede segun el id
int removeSede(ListaSede *lista, int id); //elimino una sede segun el id

/*-----------definicion de funciones----------*/
int main() {
    ListaSede *lista = initListSede();

    for(int i=0; i<10; i++) {
        Sede *sede = initSede();
        sede->nombre = "Biblioteca estudiantil ";
        sede->departamento = "San salvador";
        appendSede(lista, sede);
    }

    printListSedes(lista);

    removeSede(lista, 1);
    removeSede(lista, 10);
    removeSede(lista, 7);
    removeSede(lista, 3);



    return 0;
}

void printListSedes(ListaSede *lista) {
    Sede *sede = lista->primero;

    printf("\nTotal de registros: %d\n", lista->total);
    while(sede != NULL) {
        printf("*id: %d\n", sede->id);
        printf("nombre: %s\n", sede->nombre);
        printf("departamento: %s\n", sede->departamento);
        printf("telefono: %s\n", sede->telefono);
        printf("correo: %s\n", sede->correo);
        printf("direccion: %s\n", sede->direccion);
        printf("\n");

        sede = sede->siguiente;
    }
}

ListaSede *initListSede() {
    ListaSede *lista = malloc(sizeof(ListaSede));
    lista->total = 0;
    lista->primero = NULL;
    lista->ultimo = NULL;
    return lista;
}

Sede *initSede() {
    Sede *sede = malloc(sizeof(Sede));
    sede->nombre = NULL;
    sede->departamento = NULL;
    sede->telefono = NULL;
    sede->correo = NULL;
    sede->direccion = NULL;
    sede->siguiente = NULL;
    sede->anterior = NULL;
    return sede;
}

void appendSede(ListaSede *lista, Sede *sede) {
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
}

int isEmptyListSede(ListaSede *lista) {
    if(lista == NULL || lista->total == 0)
        return TRUE;
    else
        return FALSE;
}

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
