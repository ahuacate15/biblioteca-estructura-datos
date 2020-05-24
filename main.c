#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "libro.h"
#include "sede.h";

//contantes para menu principal
#define PRESTAMOS 1
#define DEVOLUCIONES 2
#define TRASLADOS 3
#define LIBROS 4
#define ALUMNOS 5
#define ERROR -1
#define FINALIZAR 7
#define TRUE 1
#define RETROCEDER 0

//constantes para submenu libros
#define AGREGARLIBRO 1
#define BUSCARLIBRO 2
#define BUSCARLIBROPORID 3
#define MODIFICARLIBRO 4
#define MOSTRARLIBROS 5

int printMainMenu();
int printMenuLibros();

int main() {
	Arbol *arbolLibros = initializeArbol();
	arbolLibros = cargarRegistrosDefecto(arbolLibros);
	ListaSede *listSede = initListSede();
	listSede = cargarSedesDefecto(listSede);
	setlocale(LC_ALL,"spanish");

	inicio:;
	while(TRUE) {
		switch(printMainMenu()) {
			case LIBROS:
				while(TRUE) {
					switch(printMenuLibros()) {
						case AGREGARLIBRO:
							addLibroMenu(arbolLibros, listSede);
							break;
						case BUSCARLIBRO:
							findLibrosMENU(arbolLibros);
							break;
						case BUSCARLIBROPORID:
							findLibroByClaveMenu(arbolLibros);
							break;
						case MODIFICARLIBRO:
							editLibroMenu(arbolLibros);
							break;
						case MOSTRARLIBROS:
							printLibrosMenu(arbolLibros);
							break;
						case 6: //atras
							goto inicio;
							break;
						default:
							printf("La opcion ingresada en incorrecta\n\n");
					}
				}
				break;
			case FINALIZAR:
				return;
			default:
				printf("La opcion ingresada en incorrecta\n\n");
		}
	}
	return 0;
}

int printMainMenu() {
	int opcion = NULL;

	while(TRUE) {
		printf(" ----------------------------------------------------------- \n");
		printf("|                  SISTEMA BIBLIOTECARIO                    |\n");
		printf(" ----------------------------------------------------------- \n\n");

		printf("1)prestamos\t 2)devoluciones\t 3)traslados\t 4)libros\n");
		printf("5)alumnos\t 6)sedes\t 7)finalizar\n\n");

		printf(">> ");

		if(scanf("%d", &opcion) == 0) {
			printf("La opcion ingresada es incorrecta\n\n");
			fflush(stdin);
			continue;
		}
		return opcion;
	}

}

int printMenuLibros() {
	int opcion = 0;
	while(TRUE) {
		printf(" ----------------------------------------------------------- \n");
		printf("|                          LIBROS                           |\n");
		printf(" ----------------------------------------------------------- \n\n");
		printf("1)Agregar\t 2)Buscar\t 3)Buscar por id\n");
		printf("4)Modificar\t 5)Mostrar\t 6)Atras\n\n");

		printf(">> ");
		if(scanf("%d", &opcion) == 0) {
			printf("La opcion ingresada es incorrecta\n\n");
			fflush(stdin);
			continue;
		}
		return opcion;
	}
}
