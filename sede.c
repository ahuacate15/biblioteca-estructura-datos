#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

/*-----------definicion de estructuras----------*/
typedef struct sede { 
    int id;
    char *nombre;
    char *departamento;
    char *telefono;
    char *correo;
    char *direccion;
    struct sede *siguiente;
} Sede;

typedef struct listaSede {
    int total;
    Sede *primero;
    Sede *ultimo;
} ListaSede;

/*-----------prototipos de funciones----------*/
ListaSede *initListSede();
Sede *initSede();
void appendSede(ListaSede *lista, Sede *sede);
void addSede(ListaSede *lista, Sede *sede, int element);
void isEmptyListSede(ListaSede lista);
Sede *getSede(ListaSede *lista, int index);
int containtSede(ListaSede *lista, int id);
void *removeSede(ListaSede *lista, int index);

/*-----------definicion de funciones----------*/
int main() {
    ListaSede *lista = initListSede();

    Sede *sede = initSede();
    sede->nombre = "Biblioteca estudiantil la esperanza";
    sede->departamento = "San saltador";
    sede->telefono = "7709-0910";
    sede->correo = "biblioteca.ss@itca.edu.sv";
    sede->direccion = "Avenida las gardenias, pasaje #1";

    appendSede(lista, sede);

    Sede *sedeTwo = initSede();
    sedeTwo->nombre = "Biblioteca estudiantes la joya";
    appendSede(lista, sedeTwo);
   
    Sede *sedeThree = initSede();
    sedeThree->nombre = "Biblioteca emilio coreas";
    appendSede(lista, sedeThree);

    printf("[%d] primer registro: %s\n", lista->primero->id, lista->primero->nombre);
    printf("[%d] segundo registro: %s\n", lista->primero->siguiente->id, lista->primero->siguiente->nombre);
    printf("[%d] tercer registro: %s\n", lista->primero->siguiente->siguiente->id, lista->primero->siguiente->siguiente->nombre);
    return 0;
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
    sede->nombre = "";
    sede->departamento = "";
    sede->telefono = "";
    sede->correo = "";
    sede->direccion = "";
    sede->siguiente = NULL;
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
        lista->ultimo = sede;
        lista->total++;
    }
}

//acero, engranaje, muelle