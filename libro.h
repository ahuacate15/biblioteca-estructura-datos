#define TITULO 1
#define ISBN 2

typedef struct sede Sede;
typedef struct listaSede ListaSede;

typedef struct libroSede {
	struct sede *sede;
	int copias;
	struct LibroSede *siguiente;
} LibroSede;

typedef struct libro {
	int id;
	char *titulo;
	char *autor;
	char *isbn;
	int year;
	int copias;
	char *genero;
	struct libroSede *libroSede;
	struct Libro *siguiente;
} Libro;

typedef struct nodo {
	char *clave;
	Libro *libro;
	int activo;
	struct nodo *padre;
	struct nodo *izquierda;
	struct nodo *derecha;
} Nodo;

typedef struct arbol {
	Nodo *raiz; //ordenado segun titulo de libro
	Nodo *raizISBN; //ordenado segun ISBN
	int total;
} Arbol;

Libro *initializeLibro();
void addLibroMenu(Arbol *arbol, ListaSede *listaSede); //opcion 1
void findLibrosMENU(Arbol *arbol); //opcion 2
Nodo *findLibroByClaveMenu(Arbol *arbol); //opcion 3
void editLibroMenu(); //opcion 4
void printLibrosMenu(Arbol *arbol); //opcion 5
Arbol *cargarRegistrosDefecto(Arbol *Arbol, ListaSede *listaSede);
void printCopiasPorSede(Libro *libro) ;

//eliminar luego
void addLibroSedeItem(Libro *libro, Sede *sede, int copias);
Nodo *buscarLibroPorClave(Nodo *nodo, char *clave);
