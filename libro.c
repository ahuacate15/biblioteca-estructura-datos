#include <stdio.h>
#include <string.h>
#include <time.h>
#include "texto.h"

#define TRUE 1
#define FALSE 0

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

typedef struct nodo { 
	char *clave;
	Libro *libro;
	struct nodo *izquierda;
	struct nodo *derecha;
} Nodo;


typedef struct arbol {
	Nodo *raiz;
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
Nodo *insertarNodo(Arbol *arbol, Nodo *nodo, Libro *libro);
ListLibro *buscarLibroPorTitulo(Nodo *nodo, ListLibro *list, char *titulo);
Libro *addLibroToList(ListLibro *list, Libro *libro);

/*-----------prototitpos de funciones para interfaz--------*/
void requestNewLibro(Arbol *arbol);
void findLibroByTitulo(Arbol *arbol);

Arbol *initializeArbol() {
	Arbol *arbol = malloc(sizeof(Arbol));
	arbol->raiz = NULL;
	arbol->total = 0;
	return arbol;
}

Libro *initializeLibro() {
	Libro *libro = malloc(sizeof(Libro));
	libro->titulo = malloc(sizeof(char) * 256);
	libro->autor = malloc(sizeof(char) * 128);
	libro->isbn = malloc(sizeof(char) * 20);
	libro->copias = 0;
	libro->genero = malloc(sizeof(char) * 64);
	libro->siguiente = NULL;
	
	//el campo year se inicializa por defecto con el año actual
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
	
	/*
	printf("autor: ");
	libro->autor = getLine(128);
	
	printf("isbn: ");
	libro->isbn = getLine(20);
	
	printf("genero: ");
	libro->genero = getLine(64);
	*/
	
	if(arbol->raiz == NULL)
		arbol->raiz = insertarNodo(arbol, NULL, libro);
	else
		insertarNodo(arbol, arbol->raiz, libro);
}

void findLibroByTitulo(Arbol *arbol) {
	ListLibro *list = malloc(sizeof(ListLibro));
	list->primero = NULL;
	list->ultimo = NULL;
	list->total = 0;
	
	char *filtro = malloc(sizeof(char) * 256); //maxima longitud para el titulo de un libro
	printf("\nbusqueda de libros\n");
	
	printf("ingresa el titulo: ");
	filtro = getLine(256);
	 
	buscarLibroPorTitulo(arbol->raiz, list, filtro);
	
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

Nodo *insertarNodo(Arbol *arbol, Nodo *nodo, Libro *libro) {
	if(nodo == NULL) {
		nodo = malloc(sizeof(Nodo));
		nodo->clave = lowerString(libro->titulo); //el titulo del libro se almacena en minusculas, cuando es la clave del nodo
		nodo->libro = libro;
		nodo->izquierda = NULL;
		nodo->derecha = NULL;
		
		//el primer elemento se convierte en la raiz del arbol
		if(arbol->raiz == NULL) arbol->raiz = nodo;
		
		arbol->total++;
		return nodo;
	} else {
		//la clave esta repetida
		if(strcmp(lowerString(libro->titulo), nodo->clave) == 0) 
			return NULL;
		else if(strcmp(lowerString(libro->titulo), nodo->clave) > 0)
			nodo->derecha = insertarNodo(arbol, nodo->derecha, libro);
		else
			nodo->izquierda = insertarNodo(arbol, nodo->izquierda, libro);
	}
}

ListLibro *buscarLibroPorTitulo(Nodo *nodo, ListLibro *list, char *titulo) {

	if(nodo == NULL)
		return NULL;

	int comparacion = searchStartOfString(nodo->clave, titulo);
	
	if(comparacion == 0) {
		addLibroToList(list, nodo->libro);
		buscarLibroPorTitulo(nodo->izquierda, list, titulo);
		buscarLibroPorTitulo(nodo->derecha, list, titulo);
		return nodo;
	} else if(comparacion < 0) {
		buscarLibroPorTitulo(nodo->izquierda, list, titulo);
	} else {
		buscarLibroPorTitulo(nodo->derecha, list, titulo);
	}
	
	return NULL;
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



void test() {
	
	Libro *libro = initializeLibro();
	libro->titulo = "karka en la orilla";
	
	Libro *libro2 = initializeLibro();
	libro2->titulo = "1984";
	
	Libro *libro3 = initializeLibro();
	libro3->titulo = "matematicas discretas II";

	Libro *libro4 = initializeLibro();
	libro4->titulo = "los detectives salvajes";
	
	Libro *libro5 = initializeLibro();
	libro5->titulo = "voces de chernobil";
	
	Libro *libro6 = initializeLibro();
	libro6->titulo = "la ciudad de los perros";
	
	Libro *libro7 = initializeLibro();
	libro7->titulo = "la madre";
	
	Libro *libro8 = initializeLibro();
	libro8->titulo = "linux kernel development";
	
	Libro *libro9 = initializeLibro();
	libro9->titulo = "120 dias en sodoma";
	
	Libro *libro10 = initializeLibro();
	libro10->titulo = "cien anios de soledad";
	
	Libro *libro11 = initializeLibro();
	libro11->titulo = "electronica digital";
	
	Libro *libro12 = initializeLibro();
	libro12->titulo = "building a rest api";
	
	Libro *libro13 = initializeLibro();
	libro13->titulo = "el ensayo sobre la ceguera";
	
	Libro *libro14 = initializeLibro();
	libro14->titulo = "diarios de ana frank";
	
	Arbol *arbol = initializeArbol();
	arbol->raiz = insertarNodo(arbol, NULL, libro);
	insertarNodo(arbol, arbol->raiz, libro2);
	insertarNodo(arbol, arbol->raiz, libro3);
	insertarNodo(arbol, arbol->raiz, libro4);
	insertarNodo(arbol, arbol->raiz, libro5);
	insertarNodo(arbol, arbol->raiz, libro6);
	insertarNodo(arbol, arbol->raiz, libro7);
	insertarNodo(arbol, arbol->raiz, libro8);
	insertarNodo(arbol, arbol->raiz, libro9);
	insertarNodo(arbol, arbol->raiz, libro10);
	insertarNodo(arbol, arbol->raiz, libro11);
	insertarNodo(arbol, arbol->raiz, libro12);
	insertarNodo(arbol, arbol->raiz, libro13);
	insertarNodo(arbol, arbol->raiz, libro14);
	
	requestNewLibro(arbol);
	requestNewLibro(arbol);
	requestNewLibro(arbol);
	
	findLibroByTitulo(arbol);

}





