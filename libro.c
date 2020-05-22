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
void eliminarLibro(Nodo **nodo);

/*-----------prototitpos de funciones para interfaz--------*/
void requestNewLibro(Arbol *arbol);
void findLibroMENU(Arbol *arbol);
void findLibroByClaveMenu(Arbol *arbol);
void printLibro(Libro *libro);

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

	//el campo year se inicializa por defecto con el aï¿½o actual
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	libro->year = tm.tm_year + 1900;

	return libro;
}

void requestNewLibro(Arbol *arbol) {
	Libro *libro = initializeLibro();

	printf("\ningresa los datos del libro\n");
	printf("titulo: ");
	libro->titulo = getLine(256);

	printf("autor: ");
	libro->autor = getLine(128);

	printf("isbn: ");
	libro->isbn = getLine(20);

	printf("genero: ");
	libro->genero = getLine(64);

	printf("a%co de edicion: ", 164); //agrego el caracter ï¿½
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
}

void findLibroMENU(Arbol *arbol) {
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

	Libro *libro = list->primero;

	if(libro == NULL)
		printf("no se encontraron resultados\n");
	else {
		printf("---Total de resultados: %d---\n", list->total);
		while(libro != NULL) {
			printf("libro: %s\n", libro->titulo);
			libro = libro->siguiente;
		}
	}

}

void findLibroByClaveMenu(Arbol *arbol) {
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
	if(nodo == NULL) 
		printf("no se encontraron resultados\n");
	else
		printLibro(nodo->libro);
}

void printLibro(Libro *libro) {
	printf("ISBN: %s\n", libro->isbn);
	printf("Titulo: %s\n", libro->titulo);
	printf("Autor: %s\n", libro->autor);
	printf("Año: %d\n", libro->year);
	printf("Genero: %s\n", libro->genero);
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
	if(comparacion == 0)
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

void eliminarLibro(Nodo **nodo) {
	printf("*****nodo eliminado: %p, %p\n", (*nodo), nodo);
	free(*nodo);
	*nodo = NULL;
	
	
	
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
				free((*nodo)->padre->izquierda);
				free(*nodo);
				(*nodo)->padre->izquierda == NULL;
				*nodo = NULL;
				printf("izquierda eliminada\n");
			} else if((*nodo)->padre->derecha != NULL && strcmp((*nodo)->clave, (*nodo)->padre->derecha->clave) == 0) {
			
				free((*nodo)->padre->derecha);
				free(*nodo);
				(*nodo)->padre->derecha = NULL;
				printf("derecha eliminada\n");
			} else {
				printf("nada ha sido eliminado");
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
	requestNewLibro(arbol);
	requestNewLibro(arbol);
	//requestNewLibro(arbol);
	
	Nodo *nodoISBN = buscarLibroPorClave(arbol->raizISBN, "15");
	printf("053315: %p\n", nodoISBN);
	eliminarLibro(&nodoISBN);
	printf("053315: %p\n", nodoISBN);
	printf("finalizado\n");
}
