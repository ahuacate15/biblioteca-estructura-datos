typedef struct libro Libro;
typedef struct arbol Arbol;
typedef struct nodo Nodo;
typedef struct sede Sede;
typedef struct listaSede ListaSede;

Libro *initializeLibro();
void addLibroMenu(Arbol *arbol, ListaSede *listaSede); //opcion 1
void findLibrosMENU(Arbol *arbol); //opcion 2
Nodo *findLibroByClaveMenu(Arbol *arbol); //opcion 3
void editLibroMenu(); //opcion 4
void printLibrosMenu(Arbol *arbol); //opcion 5
Arbol *cargarRegistrosDefecto(Arbol *Arbol);

//eliminar luego
void addLibroSedeItem(Libro *libro, Sede *sede, int copias);
Nodo *buscarLibroPorClave(Nodo *nodo, char *clave);
