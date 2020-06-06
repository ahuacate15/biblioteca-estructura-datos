#include <stdio.h>
#include <string.h>
#include <time.h>
#include "texto.h"
#include "sede.h";

#define TRUE 1
#define FALSE 0

#define TITULO 1
#define ISBN 2

typedef struct libroSede {
	Sede *sede;
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
	LibroSede *libroSede;
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
void addLibroSedeItem(Libro *libro, Sede *sede, int copias);
/*
* @description : carga 10 libros a la memoria
*/
Arbol *cargarRegistrosDefecto(Arbol *arbol, ListaSede *listaSede);

/*-----------prototitpos de funciones para interfaz--------*/
void printLibro(Libro *libro); //imprime un unico libro
void printListLibros(ListLibro *listLibro); //formatea e imprime en pantalla una lista de tipo listLibro
void addLibroMenu(Arbol *arbol, ListaSede *listaSede);
void findLibrosMENU(Arbol *arbol);
Nodo *findLibroByClaveMenu(Arbol *arbol);
void printLibrosMenu(Arbol *arbol); //obtiene todos los libros del arbol, y los imprimie en pantalla
void editLibroMenu(Arbol *arbol); //muestra la informacion de un info en pantalla, asi como la solicitud de datos para su edicion
void printCopiasPorSede(Libro *libro); //imprime la cantidad de copias del libro en cada una de las sedes

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
	libro->libroSede = NULL;
	libro->copias = 0;
	libro->siguiente = NULL;

	//el campo year se inicializa por defecto con el aï¿½o actual
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
	addLibroMenu(arbol, NULL);
	addLibroMenu(arbol, NULL);
	addLibroMenu(arbol, NULL);

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

void addLibroSedeItem(Libro *libro, Sede *sede, int copias) {
	LibroSede *libroSede = malloc(sizeof(LibroSede));
	libroSede->sede = sede;
	libroSede->copias = copias;
	libroSede->siguiente = NULL;

	//no hay existencias en ninguna sede
	if(libro->libroSede == NULL) {
		libro->libroSede = libroSede;
	} else {
		LibroSede *tmp = libro->libroSede;
		LibroSede *aux = libro->libroSede;

		//si la sede se encuentra vinculada, aumento el numero de copias
		while(tmp != NULL) {
			if(tmp->sede->id == sede->id) {
				tmp->copias += copias;
				goto stateEnd; //no agrego la sede a la cola
			}
			tmp = tmp->siguiente;
		}

		//sede no vinculada al numero de copias, la agrego al final de la lista
		while(aux->siguiente != NULL)
			aux = aux->siguiente;

		aux->siguiente = libroSede;
		stateEnd:;
	}
}

Arbol *cargarRegistrosDefecto(Arbol *arbol, ListaSede *listaSede) {

	Libro *libro1 = initializeLibro();
	libro1->titulo = "Kafka en la orilla";
	libro1->isbn = "9788483835241";
	libro1->autor = "Haruki Murakami";
	libro1->genero = "Literatura contemporánea";
	libro1->copias = 0;
	libro1->year = 1990;
	insertarNodo(arbol, arbol->raiz, NULL, libro1, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro1, ISBN);

	Libro *libro2 = initializeLibro();
	libro2->titulo = "Rebelion en la granja";
	libro2->isbn = "9781365425806";
	libro2->autor = "George Orwell";
	libro2->genero = "Distopia";
	libro2->copias = 0;
	libro2->year = 1991;
	insertarNodo(arbol, arbol->raiz, NULL, libro2, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro2, ISBN);

	Libro *libro3 = initializeLibro();
	libro3->titulo = "1984";
	libro3->isbn = "9780451524935";
	libro3->autor = "George Orwell";
	libro3->genero = "Distopia";
	libro3->copias = 0;
	libro3->year = 1990;
	insertarNodo(arbol, arbol->raiz, NULL, libro3, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro3, ISBN);

	Libro *libro4 = initializeLibro();
	libro4->titulo = "El manifiesto comunista";
	libro4->isbn = "1516868994";
	libro4->autor = "Karl Marx";
	libro4->genero = "Politica";
	libro4->copias = 0;
	libro4->year = 2001;
	insertarNodo(arbol, arbol->raiz, NULL, libro4, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro4, ISBN);

    Libro *libro5 = initializeLibro();
    libro5->titulo = "El anarquista loco";
    libro5->isbn = "9780142437230";
    libro5->autor = "Joseph Mora";
    libro5->genero = "Politica";
    libro5->copias = 0;
    libro5->year = 1990;
	insertarNodo(arbol, arbol->raiz, NULL, libro5, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro5, ISBN);
	
	Libro *libro6 = initializeLibro();
    libro6->titulo = "Croata";
    libro6->isbn = "9788412157796";
    libro6->autor = "Jorge García García";
    libro6->genero = "Novela policíaca";
    libro6->copias = 0;
    libro6->year = 2020;
	insertarNodo(arbol, arbol->raiz, NULL, libro6, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro6, ISBN);
	
	Libro *libro7 = initializeLibro();
    libro7->titulo = "El legado de los malditos";
    libro7->isbn = "9788412157789";
    libro7->autor = "Vanesa Redondo";
    libro7->genero = "Novela histórica";
    libro7->copias = 0;
    libro7->year = 2020;
	insertarNodo(arbol, arbol->raiz, NULL, libro7, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro7, ISBN);
	
	Libro *libro8 = initializeLibro();
    libro8->titulo = "El silencio de la lengua";
    libro8->isbn = "9788412157772";
    libro8->autor = "Luis Melero Marcos";
    libro8->genero = "Poética actual";
    libro8->copias = 0;
    libro8->year = 2020;
	insertarNodo(arbol, arbol->raiz, NULL, libro8, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro8, ISBN);
	
	Libro *libro9 = initializeLibro();
    libro9->titulo = "La mente dibujada";
    libro9->isbn = "9788494994616";
    libro9->autor = "Grace Klimt y Salvatwitts";
    libro9->genero = "Poesía y prosa poética ilustrada";
    libro9->copias = 0;
    libro9->year = 2019;
	insertarNodo(arbol, arbol->raiz, NULL, libro9, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro9, ISBN);
	
	Libro *libro10 = initializeLibro();
    libro10->titulo = "Drácula";
    libro10->isbn = "9780786181483";
    libro10->autor = "Bram Stoker";
    libro10->genero = "Novela gótica";
    libro10->copias = 0;
    libro10->year = 1897;
	insertarNodo(arbol, arbol->raiz, NULL, libro10, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro10, ISBN);
	
	Libro *libro11 = initializeLibro();
    libro11->titulo = "Diez negritos";
    libro11->isbn = "9788467045390";
    libro11->autor = "Agatha Christie";
    libro11->genero = "Novela negra";
    libro11->copias = 0;
    libro11->year = 1939;
	insertarNodo(arbol, arbol->raiz, NULL, libro11, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro11, ISBN);
	
	Libro *libro12 = initializeLibro();
    libro12->titulo = "La carretera";
    libro12->isbn = "9786074293258";
    libro12->autor = "Cormac McCarthy";
    libro12->genero = "Novela post-apocalíptica";
    libro12->copias = 0;
    libro12->year = 2016;
	insertarNodo(arbol, arbol->raiz, NULL, libro12, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro12, ISBN);
	
	Libro *libro13 = initializeLibro();
    libro13->titulo = "La mujer del viajero en el tiempo";
    libro13->isbn = "9786074296730";
    libro13->autor = "Audrey Niffenegger";
    libro13->genero = "Novela romántica";
    libro13->copias = 0;
    libro13->year = 2003;
	insertarNodo(arbol, arbol->raiz, NULL, libro13, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro13, ISBN);
	
	Libro *libro14 = initializeLibro();
    libro14->titulo = "Cien años de soledad";
    libro14->isbn = "9786070704031";
    libro14->autor = "Gabriel García Márquez";
    libro14->genero = "Realismo mágico";
    libro14->copias = 0;
    libro14->year = 1967;
	insertarNodo(arbol, arbol->raiz, NULL, libro14, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro14, ISBN);
	
	Libro *libro15 = initializeLibro();
    libro15->titulo = "La Vida Secreta De Las Abejas";
    libro15->isbn = "9780143035794";
    libro15->autor = "SUE MONK KIDD";
    libro15->genero = "Novela contemporánea";
    libro15->copias = 0;
    libro15->year = 2002;
	insertarNodo(arbol, arbol->raiz, NULL, libro15, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro15, ISBN);
	
	Libro *libro16 = initializeLibro();
    libro16->titulo = "La letra escarlata";
    libro16->isbn = "9781519117991";
    libro16->autor = "Nathaniel Hawthorne";
    libro16->genero = "Novela histórica";
    libro16->copias = 0;
    libro16->year = 1850;
	insertarNodo(arbol, arbol->raiz, NULL, libro16, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro16, ISBN);
	
	Libro *libro17 = initializeLibro();
    libro17->titulo = "Los Pilares de la Tierra";
    libro17->isbn = "9780307454737";
    libro17->autor = "Ken Follett";
    libro17->genero = "Novela histórica";
    libro17->copias = 0;
    libro17->year = 1989;
	insertarNodo(arbol, arbol->raiz, NULL, libro17, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro17, ISBN);
	
	Libro *libro18 = initializeLibro();
    libro18->titulo = "Juego de tronos: Canción de Hielo y Fuego";
    libro18->isbn = "9786073128834";
    libro18->autor = "George R.R. Martin";
    libro18->genero = "Fantasía heroica";
    libro18->copias = 0;
    libro18->year = 1996;
	insertarNodo(arbol, arbol->raiz, NULL, libro18, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro18, ISBN);
	
	Libro *libro19 = initializeLibro();
    libro19->titulo = "Las Aventuras de Sherlock Holmes";
    libro19->isbn = "9781514339060";
    libro19->autor = "Sir Arthur Conan Doyle";
    libro19->genero = "Policíaco";
    libro19->copias = 0;
    libro19->year = 1892;
	insertarNodo(arbol, arbol->raiz, NULL, libro19, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro19, ISBN);
	
	Libro *libro20 = initializeLibro();
    libro20->titulo = "Grandes Esperanzas";
    libro20->isbn = "9789875667334";
    libro20->autor = "Charles Dickens";
    libro20->genero = "Humor negro";
    libro20->copias = 0;
    libro20->year = 1860;
	insertarNodo(arbol, arbol->raiz, NULL, libro20, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro20, ISBN);
	
	Libro *libro21 = initializeLibro();
    libro21->titulo = "Alicia En El Pais De Las Maravillas";
    libro21->isbn = "9786070913273";
    libro21->autor = "Lewis Carroll";
    libro21->genero = "Literatura fantástica";
    libro21->copias = 0;
    libro21->year = 1865;
	insertarNodo(arbol, arbol->raiz, NULL, libro21, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro21, ISBN);
	
	Libro *libro22 = initializeLibro();
    libro22->titulo = "A sangre fría";
    libro22->isbn = "9786073112086";
    libro22->autor = "Truman Capote";
    libro22->genero = "Novela testimonio";
    libro22->copias = 0;
    libro22->year = 1965;
	insertarNodo(arbol, arbol->raiz, NULL, libro22, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro22, ISBN);
	
	Libro *libro23 = initializeLibro();
    libro23->titulo = "Un arbol crece en Brooklyn";
    libro23->isbn = "9780307392473";
    libro23->autor = "Betty Smith";
    libro23->genero = "Semibiográfica";
    libro23->copias = 0;
    libro23->year = 1943;
	insertarNodo(arbol, arbol->raiz, NULL, libro23, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro23, ISBN);
	
	Libro *libro24 = initializeLibro();
    libro24->titulo = "El Color Purpura";
    libro24->isbn = "9788422621287";
    libro24->autor = "Alice Walker";
    libro24->genero = "Literatura contemporánea";
    libro24->copias = 0;
    libro24->year = 1982;
	insertarNodo(arbol, arbol->raiz, NULL, libro24, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro24, ISBN);
	
	Libro *libro25 = initializeLibro();
	libro24->titulo = "El Conde de Monte-Cristo";
    libro25->isbn = "9781246182378";
    libro25->autor = "Alexandre Dumas";
    libro25->genero = "Aventura";
    libro25->copias = 0;
    libro25->year = 1844;
	insertarNodo(arbol, arbol->raiz, NULL, libro25, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro25, ISBN);
	
	Libro *libro26 = initializeLibro();
	libro26->titulo = "Las Aventuras De Tom Sawyer";
    libro26->isbn = "9789700744049";
    libro26->autor = "Mark Twain";
    libro26->genero = "Aventura";
    libro26->copias = 0;
    libro26->year = 1876;
	insertarNodo(arbol, arbol->raiz, NULL, libro26, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro26, ISBN);

	Libro *libro27 = initializeLibro();
	libro27->titulo = "El Dador";
    libro27->isbn = "9780613047920";
    libro27->autor = "Lois Lowry";
    libro27->genero = "Utopía";
    libro27->copias = 0;
    libro27->year = 1993;
	insertarNodo(arbol, arbol->raiz, NULL, libro27, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro27, ISBN);
	
	Libro *libro28 = initializeLibro();
	libro28->titulo = "El Principito";
    libro28->isbn = "9780156013925";
    libro28->autor = "Antoine de Saint-Exupéry";
    libro28->genero = "Novela filosófica";
    libro28->copias = 0;
    libro28->year = 1951;
	insertarNodo(arbol, arbol->raiz, NULL, libro28, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro28, ISBN);
	
	Libro *libro29 = initializeLibro();
	libro29->titulo = "Cumbres borrascosas";
    libro29->isbn = "9786073120982";
    libro29->autor = "Emily Bronte";
    libro29->genero = "Novela gótica";
    libro29->copias = 0;
    libro29->year = 1847;
	insertarNodo(arbol, arbol->raiz, NULL, libro29, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro29, ISBN);
	
	Libro *libro30 = initializeLibro();
	libro30->titulo = "Harry Potter y la piedra filosofal";
    libro30->isbn = "9788498386943";
    libro30->autor = "J. K. Rowling";
    libro30->genero = "Literatura fantástica";
    libro30->copias = 0;
    libro30->year = 1997;
	insertarNodo(arbol, arbol->raiz, NULL, libro30, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro30, ISBN);
	
	Libro *libro31 = initializeLibro();
	libro31->titulo = "El Senor de los Anillos 1. La comunidad del anillo";
    libro31->isbn = "9786070712722";
    libro31->autor = "J.R.R. Tolkien";
    libro31->genero = "Literatura fantástica";
    libro31->copias = 0;
    libro31->year = 1954;
	insertarNodo(arbol, arbol->raiz, NULL, libro31, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro31, ISBN);
	
	Libro *libro32 = initializeLibro();
	libro32->titulo = "Orgullo y prejuicio";
    libro32->isbn = "9786073127769";
    libro32->autor = "Jane Austen";
    libro32->genero = "Novela romántica";
    libro32->copias = 0;
    libro32->year = 1813;
	insertarNodo(arbol, arbol->raiz, NULL, libro32, TITULO);
	insertarNodo(arbol, arbol->raizISBN, NULL, libro32, ISBN);
	
	//agrego existencias por defecto en las sedes
	Sede *tmp = listaSede->primero;
	int copias[] = {5,1,3,5,6};
	while(tmp != NULL) {
		addLibroSedeItem(libro1, tmp, copias[0]++);
		addLibroSedeItem(libro2, tmp, copias[1]++);
		addLibroSedeItem(libro3, tmp, copias[2]++);
		addLibroSedeItem(libro4, tmp, copias[3]++);
		addLibroSedeItem(libro5, tmp, copias[4]++);
		tmp = tmp->siguiente;
	}

	return arbol;

}

void printLibro(Libro *libro) {
	printf("\n");
	printf("ISBN: %s\n", libro->isbn);
	printf("Titulo: %s\n", libro->titulo);
	printf("Autor: %s\n", libro->autor);
	printf("Aï¿½o: %d\n", libro->year);
	printf("Genero: %s\n", libro->genero);

	//imprimo el stock por sede
	printCopiasPorSede(libro);
}

void printListLibros(ListLibro *listLibro) {
	Libro *libro = listLibro->primero;

	if(libro == NULL)
		printf("\n***no se encontraron resultados\n\n");
	else {
		printf("\nTotal de resultados: %d\n", listLibro->total);
		while(libro != NULL) {
			printf("----------------------------\n");
			printf("titulo: %s\n", libro->titulo);
			printf("isbn: %s\n", libro->isbn);
			printf("autor: %s\n", libro->autor);
			printf("genero: %s\n", libro->genero);
			printf("aï¿½o: %d\n", libro->year);

			//imprimo el stock por sede
			printCopiasPorSede(libro);
			printf("\n");
			libro = libro->siguiente;
		}
	}
}

void addLibroMenu(Arbol *arbol, ListaSede *listaSede) {
	Libro *libro = initializeLibro();
	int idSede = 0, copias = 0;
	system("cls");
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

	printf("aï¿½o de edicion: ");
	scanf("%d", &libro->year);

	//agrega el registro a cada sede con 0 existencias
	Sede *tmp = listaSede->primero;
	while(tmp->siguiente != NULL) {
		addLibroSedeItem(libro, tmp, copias);
		tmp = tmp->siguiente;
	}
 
	//solicito las existencias por sede
	while(TRUE) {
		printf("\nexistencias por sede, elige una (-1 para finalizar): \n");
		printListSedesMinuature(listaSede);
		printf("\nsede >> ");
		if(scanf("%d", &idSede) == 0) {
			printf("la opcion ingresada es incorrecta\n");
			fflush(stdin);
			continue;
		}

		if(idSede == -1)
			break;

		Sede *sede = getSede(listaSede, idSede);
		if(sede == NULL) {
			printf("la sede seleccionada no existe\n");
			continue;
		} else {
			printf("ingresa el numero de copias: ");
			if(scanf("%d", &copias) == 0) {
				printf("la opcion ingresada es incorrecta\n");
				fflush(stdin);
				continue;
			}
			addLibroSedeItem(libro, sede, copias);
		}
	}
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
	system("pause");
}

void findLibrosMENU(Arbol *arbol) {
	ListLibro *list = malloc(sizeof(ListLibro));
	Nodo *raiz = NULL;
	int campo = 0;
	list->primero = NULL;
	list->ultimo = NULL;
	list->total = 0;

	char *filtro = malloc(sizeof(char) * 256); //maxima longitud para el titulo de un libro
	printf("\nbusqueda de libros (inicio del titulo o del ISBN)\n");

	while(TRUE) {
		printf("por cual campo deseas realizar la busqueda? \n");
		printf("1- titulo\n");
		printf("2- ISBN\n");
		printf("\ncampo >> ");
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
	system("pause");
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
		printf("\ncampos >> ");
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
		system("pause");
		return nodo;
	}

}

void printLibrosMenu(Arbol *arbol) {
	ListLibro *list = malloc(sizeof(ListLibro));
	list->primero = NULL;
	list->ultimo = NULL;
	list->total = 0;

	system("cls");
	printf(" ----------------------------------------------------------- \n");
	printf("|                     LIBROS->mostrar                       |\n");
	printf(" ----------------------------------------------------------- \n\n");


	buscarLibro(arbol->raizISBN, list, "", ISBN);
	printListLibros(list);
	system("pause");
}

void editLibroMenu(Arbol *arbol) {
	system("cls");
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

		printf("aï¿½o de edicion: ");
		scanf("%d", &busqueda->libro->year);
		fflush(stdin);

		printf("\n***libro modificado***\n\n");
	}

	system("pause");
}

void printCopiasPorSede(Libro *libro) {
	if(libro == NULL)
		return;

	if(libro->libroSede == NULL) {
		printf("***No existen unidades en ninguna sede***\n");
		return;
	}

	LibroSede *tmp = libro->libroSede;

	printf("\nCopias por sede\n");
	while(tmp != NULL) {
		printf("%d- %s (%d copias)\n", tmp->sede->id, tmp->sede->nombre, tmp->copias);
		tmp = tmp->siguiente;
	}
}
