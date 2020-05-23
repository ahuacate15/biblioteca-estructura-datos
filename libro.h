typedef struct libro Libro;
typedef struct arbol Arbol;
typedef struct nodo Nodo;

Libro *initializeLibro();
void addLibroMenu(Arbol *arbol); //opcion 1
void findLibrosMENU(Arbol *arbol); //opcion 2
Nodo *findLibroByClaveMenu(Arbol *arbol); //opcion 3
void editLibroMenu(); //opcion 4
void printLibrosMenu(Arbol *arbol); //opcion 5
Arbol *cargarRegistrosDefecto(Arbol *Arbol);
