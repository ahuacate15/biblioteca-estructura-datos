#include <stdio.h>
#include <string.h>
#include <time.h>
#include "texto.h"

#define TRUE 1
#define FALSE 0

#define TITULO 1
#define ISBN 2

typedef struct libro {
	int id;
	char *titulo;
	char *autor;
	char *isbn;
	int year;
	int copias;
	char *genero;
	struct Libro *siguiente;
} Libro;

//estructura para la busqueda por titulo
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

typedef struct listLibro {
	int total;
	Libro *primero;
	Libro *ultimo;
} ListLibro;

/*-----------prototipos de funciones estandar----------*/
Arbol *initializeArbol();
Libro *initializeLibro();
/*
* @param padre : indica el padre del nodo que se inserta, en caso de la raiz, su valor es NULL
* @param campo : define la clave por la que se guardara el nodo en el arbol
* usa la constantes definidas: TITULO, ISBN
*/
Nodo *insertarNodo(Arbol *arbol, Nodo *nodo, Nodo *padre, Libro *libro, int campo);

/*
* @param campo : definel la claev por la que se buscara el nodo en el arbol
* usa las constantes definidas: TITULO, ISBN
*/
ListLibro *buscarLibro(Nodo *nodo, ListLibro *list, char *clave, int campo);
/*
* @description : buscar un nodo en el arbol binario, segun la clave. retorna un unico nodo
*/
Nodo *buscarLibroPorClave(Nodo *nodo, char *clave);
Libro *addLibroToList(ListLibro *list, Libro *libro);
void eliminarLibro(Nodo **nodo, Nodo *padre);
/*
* @description : carga 10 libros a la memoria
*/
Arbol *cargarRegistrosDefecto(Arbol *arbol);

/*-----------prototitpos de funciones para interfaz--------*/
void printLibro(Libro *libro); //imprime un unico libro
void printListLibros(ListLibro *listLibro); //formatea e imprime en pantalla una lista de tipo listLibro
void addLibroMenu(Arbol *arbol);
void findLibrosMENU(Arbol *arbol);
Nodo *findLibroByClaveMenu(Arbol *arbol);
void printLibrosMenu(Arbol *arbol); //obtiene todos los libros del arbol, y los imprimie en pantalla
void editLibroMenu(Arbol *arbol); //muestra la informacion de un info en pantalla, asi como la solicitud de datos para su edicion

Arbol *initializeArbol() {
	Arbol *arbol = malloc(sizeof(Arbol));
	arbol->raiz = NULL;
	arbol->raizISBN = NULL;
	arbol->total = 0;
	return arbol;
}

Libro *initializeLibro() {
	Libro *libro = malloc(sizeof(Libro));
	libro->titulo = malloc(sizeof(char) * 256);
	libro->autor = malloc(sizeof(char) * 128);
	libro->isbn = malloc(sizeof(char) * 20);
	libro->genero = malloc(sizeof(char) * 64);
	libro->copias = 0;
	libro->siguiente = NULL;

	//el campo year se inicializa por defecto con el a�o actual
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	libro->year = tm.tm_year + 1900;

	return libro;
}

Nodo *insertarNodo(Arbol *arbol, Nodo *nodo, Nodo *padre, Libro *libro, int campo) {
	char *clave = NULL;

	//la clave unica del nodo puede variar
	switch(campo) {
		case TITULO:
			clave = lowerString(libro->titulo);
			break;
		case ISBN:
			clave = lowerString(libro->isbn);
			break;
	}

	if(nodo == NULL) {
		nodo = malloc(sizeof(Nodo));
		nodo->clave = clave; //el titulo del libro se almacena en minusculas, cuando es la clave del nodo
		nodo->libro = libro;
		nodo->izquierda = NULL;
		nodo->derecha = NULL;
		nodo->padre = padre;
		nodo->activo = TRUE;

		//la clave unica del nodo puede variar
		switch(campo) {
			case TITULO:
				//el primer elemento se convierte en la raiz del arbol
				if(arbol->raiz == NULL)
					arbol->raiz = nodo;
				break;
			case ISBN:
			  //el primer elemento se convierte en la raiz del arbol
			  if(arbol->raizISBN == NULL)
					arbol->raizISBN = nodo;
				break;
		}

		arbol->total++;
		return nodo;
	} else {

		//cuando se inserta un nodo por segunda vez, su padre es la raiz
		//cuando es un nodo mas profundo, su padre en el elemento
		nodo->padre = padre == NULL ? arbol->raiz : padre;
		//la clave esta repetida
		if(strcmp(clave, nodo->clave) == 0)
			return NULL;
		else if(strcmp(clave, nodo->clave) > 0)
			nodo->derecha = insertarNodo(arbol, nodo->derecha, nodo->padre, libro, campo);
		else
			nodo->izquierda = insertarNodo(arbol, nodo->izquierda, nodo->padre, libro, campo);
	}
}

ListLibro *buscarLibro(Nodo *nodo, ListLibro *list, char *clave, int campo) {

	if(nodo == NULL)
		return NULL;

	int comparacion = searchStartOfString(nodo->clave, clave);

	if(comparacion == 0) {
		addLibroToList(list, nodo->libro);
		buscarLibro(nodo->izquierda, list, clave, campo);
		buscarLibro(nodo->derecha, list, clave, campo);
		return nodo;
	} else if(comparacion < 0) {
		buscarLibro(nodo->izquierda, list, clave, campo);
	} else {
		buscarLibro(nodo->derecha, list, clave, campo);
	}

	return NULL;
}

Nodo *buscarLibroPorClave(Nodo *nodo, char *clave) {
	if(nodo == NULL)
		return NULL;

	int comparacion = strcmp(clave, nodo->clave);
	if(comparacion == 0 && nodo->activo)
		return nodo;
	else if(comparacion < 0)
		buscarLibroPorClave(nodo->izquierda, clave);
	else
		buscarLibroPorClave(nodo->derecha, clave);

}


Libro *addLibroToList(ListLibro *list, Libro *libro) {
	Libro *tmp = NULL;

	if(list->total == 0) {
		list->primero = libro;
		list->ultimo = libro;
		list->total = 1;
	} else {
		tmp = list->ultimo;
		tmp->siguiente = libro;
		list->ultimo = libro;
		list->total++;

	}
	return libro;
}

void eliminarLibro(Nodo **nodo, Nodo *padre) {
	(*nodo)->clave = "TEST";
	/*
	//elimino una hoja
	if((*nodo)->izquierda == NULL && (*nodo)->derecha == NULL) {
		printf("es una hoja: %p\n", (*nodo));
		//raiz del arbol
		if((*nodo)->padre == NULL) {
			free(*nodo);
			*nodo = NULL;
		} else {
			if((*nodo)->padre->izquierda != NULL && strcmp((*nodo)->clave, (*nodo)->padre->izquierda->clave) == 0) {
				free(*nodo);
				*nodo = NULL;

				padre->izquierda = NULL;
			} else if((*nodo)->padre->derecha != NULL && strcmp((*nodo)->clave, (*nodo)->padre->derecha->clave) == 0) {
				free(*nodo);
				*nodo = NULL;
				padre->derecha = NULL;
			} else {
				printf("nada ha sido eliminado\n");
			}
		}
	}
	*/
}

void deletePointer(void **ptr) {
	free(*ptr);
	*ptr = NULL;
}

void test() {


	Arbol *arbol = initializeArbol();
	addLibroMenu(arbol);
	addLibroMenu(arbol);
	addLibroMenu(arbol);

	Nodo *nodoISBN = buscarLibroPorClave(arbol->raizISBN, "15");
	Nodo *nodoTitulo = buscarLibroPorClave(arbol->raiz, "15");

	printf("isbn: %p %p\n", nodoISBN, arbol->raizISBN->izquierda);
//	printf("titulo: %p %p\n", nodoISBN, arbol->raizISBN->izquierda);

	//eliminarLibroPorClave(arbol->raizISBN, "15");
	eliminarLibro(&nodoISBN, nodoISBN->padre);
	//eliminarLibro(&nodoTitulo, nodoTitulo->padre);


	printf("isbn: %s\n", nodoISBN->clave);
//	printf("titulo: %p %p\n", nodoISBN, arbol->raizISBN->izquierda);
	//printf("titulo: %p\n", nodoTitulo);
	printf("finalizado\n");
}

Arbol *cargarRegistrosDefecto(Arbol *arbol) {
	//Nodo *insertarNodo(Arbol *arbol, Nodo *nodo, Nodo *padre, Libro *libro, int campo);

	Libro *libro1 = initializeLibro();
	libro1->titulo = "kafka en la orilla";
	libro1->isbn = "053315";
	libro1->autor = "haruki murakami";
	libro1->copias = 0;
	libro1->year = 1990;

	Libro *libro2 = initializeLibro();
	libro2->titulo = "rebelion en la granja";
	libro2->isbn = "053316";
	libro2->autor = "george orwell";
	libro2->copias = 0;
	libro2->year = 1991;

	Libro *libro3 = initializeLibro();
	libro3->titulo = "1984";
	libro3->isbn = "053317";
	libro3->autor = "george orwell";
	libro3->copias = 0;
	libro3->year = 1990;

	Libro *libro4 = initializeLibro();
	libro4->titulo = "el manifiesto comunista";
	libro4->isbn = "053318";
	libro4->autor = "karl marx";
	libro4->copias = 0;
	libro4->year = 2001;

    Libro *libro5 = initializeLibro();
    libro5->titulo = "el anarquista loco";
    libro5->isbn = "053319";
    libro5->autor = "joseph mora";
    libro5->copias = 0;
    libro5->year = 1990;


	insertarNodo(arbol, arbol->raiz, NULL, libro1, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro1, ISBN);
	insertarNodo(arbol, arbol->raiz, NULL, libro2, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro2, ISBN);
	insertarNodo(arbol, arbol->raiz, NULL, libro3, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro3, ISBN);
	insertarNodo(arbol, arbol->raiz, NULL, libro4, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro4, ISBN);
	insertarNodo(arbol, arbol->raiz, NULL, libro5, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro5, ISBN);

	return arbol;

}

void printLibro(Libro *libro) {
	printf("ISBN: %s\n", libro->isbn);
	printf("Titulo: %s\n", libro->titulo);
	printf("Autor: %s\n", libro->autor);
	printf("A�o: %d\n", libro->year);
	printf("Genero: %s\n", libro->genero);
}

void printListLibros(ListLibro *listLibro) {
	Libro *libro = listLibro->primero;

	if(libro == NULL)
		printf("\n***no se encontraron resultados\n\n");
	else {
		printf("Total de resultados: %d\n", listLibro->total);
		while(libro != NULL) {
			printf("----------------------------\n");
			printf("titulo: %s\n", libro->titulo);
			printf("isbn: %s\n", libro->isbn);
			printf("autor: %s\n", libro->autor);
			printf("genero: %s\n", libro->genero);
			printf("a�o: %d\n", libro->year);
			printf("\n");
			libro = libro->siguiente;
		}
	}
}

void addLibroMenu(Arbol *arbol) {
	Libro *libro = initializeLibro();

	printf(" ----------------------------------------------------------- \n");
	printf("|                     LIBROS->agregar                       |\n");
	printf(" ----------------------------------------------------------- \n\n");
	fflush(stdin);

	stateTitulo:;
	printf("titulo: ");
	libro->titulo = getLine(256);
	//libros con titulo duplicado
	if(buscarLibroPorClave(arbol->raiz, libro->titulo) != NULL) {
		printf("El titulo ya existe\n");
		goto stateTitulo;
	}

	stateIsbn:;
	printf("isbn: ");
	libro->isbn = getLine(20);
	//libros con isbn duplicado
	if(buscarLibroPorClave(arbol->raizISBN, libro->isbn) != NULL) {
		printf("El ISBN ya existe\n");
		goto stateIsbn;
	}

	printf("autor: ");
	libro->autor = getLine(128);

	printf("genero: ");
	libro->genero = getLine(64);

	printf("a%co de edicion: ", 164); //agrego el caracter �
	scanf("%d", &libro->year);
	fflush(stdin);

	//ordeno estructura segun el titulo del libro
	if(arbol->raiz == NULL)
		arbol->raiz = insertarNodo(arbol, NULL, NULL, libro, TITULO);
	else
		insertarNodo(arbol, arbol->raiz, NULL, libro, TITULO);

	//ordeno estructura segun el ISBN del libro
	if(arbol->raizISBN == NULL)
		arbol->raizISBN = insertarNodo(arbol, NULL, NULL, libro, ISBN);
	else
		insertarNodo(arbol, arbol->raizISBN, NULL, libro, ISBN);

	printf("\n***libro registrado***\n\n");
}

void findLibrosMENU(Arbol *arbol) {
	ListLibro *list = malloc(sizeof(ListLibro));
	Nodo *raiz = NULL;
	int campo = 0;
	list->primero = NULL;
	list->ultimo = NULL;
	list->total = 0;

	char *filtro = malloc(sizeof(char) * 256); //maxima longitud para el titulo de un libro
	printf("\nbusqueda de libros\n");

	while(TRUE) {
		printf("por cual campo deseas realizar la busqueda? \n");
		printf("1- titulo\n");
		printf("2- ISBN\n");
		scanf("%d", &campo);

		if(campo >= 1 && campo <= 2) //valido el campo seleccionado
			break;
		else
			printf("la opcion ingresada es incorrecta\n\n");
	}

	fflush(stdin);
	switch (campo) {
		case TITULO:
			printf("ingresa el titulo del libro: ");
			filtro = getLine(256);
			raiz = arbol->raiz;
			break;
		case ISBN:
			printf("ingresa el ISBN del libro: ");
			filtro = getLine(20);
			raiz = arbol->raizISBN;
			break;
	}

	buscarLibro(raiz, list, filtro, campo);
	printListLibros(list);
}

Nodo *findLibroByClaveMenu(Arbol *arbol) {
	char *filtro = malloc(sizeof(char) * 256);
	Nodo *raiz = NULL;
	int campo = 0;

	printf("\nbusqueda especifica de libro\n");
	while(TRUE) {
		printf("por cual campo deseas realizar la busqueda? \n");
		printf("1- titulo\n");
		printf("2- ISBN\n");
		scanf("%d", &campo);

		if(campo >= 1 && campo <= 2) //valido el campo seleccionado
			break;
		else
			printf("la opcion ingresada es incorrecta\n\n");
	}

	fflush(stdin);
	switch (campo) {
		case TITULO:
			printf("ingresa el titulo del libro: ");
			filtro = getLine(256);
			raiz = arbol->raiz;
			break;
		case ISBN:
			printf("ingresa el ISBN del libro: ");
			filtro = getLine(20);
			raiz = arbol->raizISBN;
			break;
	}

	Nodo *nodo = buscarLibroPorClave(raiz, filtro);
	if(nodo == NULL) {
		printf("***no se encontraron resultados***\n");
		return NULL;
	}
	else {
		printLibro(nodo->libro);
		return nodo;
	}

}

void printLibrosMenu(Arbol *arbol) {
	ListLibro *list = malloc(sizeof(ListLibro));
	list->primero = NULL;
	list->ultimo = NULL;
	list->total = 0;

	printf(" ----------------------------------------------------------- \n");
	printf("|                     LIBROS->mostrar                       |\n");
	printf(" ----------------------------------------------------------- \n\n");


	buscarLibro(arbol->raizISBN, list, "", ISBN);
	printListLibros(list);
}

void editLibroMenu(Arbol *arbol) {
	printf(" ----------------------------------------------------------- \n");
	printf("|                     LIBROS->editar                        |\n");
	printf(" ----------------------------------------------------------- \n\n");
	Nodo *busqueda = findLibroByClaveMenu(arbol);
	char *titulo = malloc(sizeof(256));
	char *isbn = malloc(sizeof(20));

	if(busqueda != NULL) {
		stateTitulo:;
		printf("\nIngresa los nuevos datos\n");
		printf("titulo: ");
		titulo = getLine(256);

		//libros con titulo duplicado
		if(strcmp(titulo, busqueda->libro->titulo) != 0 && buscarLibroPorClave(arbol->raiz, titulo) != NULL) {
			printf("El titulo ya existe\n");
			goto stateTitulo;
		}

		busqueda->libro->titulo = titulo;

		stateIsbn:;
		printf("isbn: ");
		isbn = getLine(20);

		//libros con isbn duplicado
		if(strcmp(isbn, busqueda->libro->isbn) != 0 && buscarLibroPorClave(arbol->raizISBN, isbn) != NULL) {
			printf("El ISBN ya existe\n");
			goto stateIsbn;
		}
		busqueda->libro->isbn = isbn;

		printf("autor: ");
		busqueda->libro->autor = getLine(128);

		printf("genero: ");
		busqueda->libro->genero = getLine(64);

		printf("a%co de edicion: ", 164); //agrego el caracter �
		scanf("%d", &busqueda->libro->year);
		fflush(stdin);

		printf("\n***libro modificado***\n\n");
	}
}
