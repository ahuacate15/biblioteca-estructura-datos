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
void printListSedesMinuature(ListaSede *lista); //imprimime el ID y el nombre de la sede (unicamente)
ListaSede *cargarSedesDefecto(ListaSede *lista);
void editSedeMenu(ListaSede *lista);
