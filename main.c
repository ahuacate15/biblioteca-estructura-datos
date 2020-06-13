#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "libro.h"
#include "sede.h"
#include "traslado.h"
#include "alumno.h"
#include "prestamo.h"

//contantes para menu principal
#define PRESTAMOS 1
#define DEVOLUCIONES 2
#define TRASLADOS 3
#define LIBROS 4
#define ALUMNOS 5
#define SEDES 6
#define ERROR -1
#define FINALIZAR 7
#define TRUE 1
#define RETROCEDER 0

//constantes para submenu prestamos
#define AGREGAR_PRESTAMO 1
#define BUSCAR_PRESTAMO 2

//constantes para submenu libros
#define AGREGARLIBRO 1
#define BUSCARLIBRO 2
#define BUSCARLIBROPORID 3
#define MODIFICARLIBRO 4
#define MOSTRARLIBROS 5

//constantes para submenu alumnos
#define AGREGAR_ALUMNO 1
#define BUSCAR_ALUMNO 2
#define MODIFICAR_ALUMNO 3
#define ELIMINAR_ALUMNO 4
#define MOSTRAR_ALUMNOS 5

//constantes para acciones del menu
#define MOSTRAR 1
#define EDITAR 2

int printMenuPrestamos();
int printMainMenu();
int printMenuLibros();
int printMenuSedes();
int printMenuAlumnos();

int main() {
	ListaSede *listSede = initListSede();
	listSede = cargarSedesDefecto(listSede);

	Arbol *arbolLibros = initializeArbol();
	arbolLibros = cargarRegistrosDefecto(arbolLibros, listSede);

	ListaAlumno *listaAlumno = initListaAlumno();
	cargaInicialAlumnos(listaAlumno);

	ArbolPrestamo *ptrArbolPrestamo = initArbolPrestamo();
	cargarPrestamosPrueba(ptrArbolPrestamo, listaAlumno, arbolLibros);
	
	setlocale(LC_ALL,"spanish");

	inicio:;
	while(TRUE) {
		system("cls");
		switch(printMainMenu()) {
			case PRESTAMOS:
				while(TRUE) {
					switch(printMenuPrestamos()) {
						case AGREGAR_PRESTAMO:
							agregarPrestamoMENU(ptrArbolPrestamo, listaAlumno, arbolLibros);
							break;
						case BUSCAR_PRESTAMO:
							buscarPrestamosMENU(ptrArbolPrestamo);
							break;
						case 3:
							buscarRegistrosPrestamos(ptrArbolPrestamo);
						case 4: //atras
							goto inicio;
							break;
						default:
							printf("La opcion ingresada es incorrecta\n\n");
							system("pause");
					}
				}
				break;
			case TRASLADOS:
				realizarTrastadoMenu(arbolLibros, listSede);
				break;
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
							printf("La opcion ingresada es incorrecta\n\n");
							system("pause");
					}
				}
				break;
			case SEDES:
				while(TRUE) {
					switch (printMenuSedes()) {
						case MOSTRAR:
							printListSedes(listSede);
							break;
						case EDITAR:
							editSedeMenu(listSede);
							break;
						case 3:
							goto inicio;
							break;
						default:
							printf("La opcion ingresada es incorrecta\n");
							system("pause");
					}
				}
			case ALUMNOS:
				while(TRUE) {
					switch(printMenuAlumnos()) {
						case AGREGAR_ALUMNO:
							insertarAlumno(listaAlumno);
							break;
						case BUSCAR_ALUMNO:
							BusquedaAlumno(listaAlumno);
							break;
						case MODIFICAR_ALUMNO:
							modificarAlumno(listaAlumno);
							break;
						case ELIMINAR_ALUMNO:
							eliminarAlumno(listaAlumno);
							break;
						case MOSTRAR_ALUMNOS:
							mostrarAlumnos(listaAlumno);
							break;
						case 6:
							goto inicio;
						default:
							printf("La opcion ingresada es incorrecta\n");
							system("pause");
					}
				}
			case FINALIZAR:
				return;
			default:
				printf("La opcion ingresada en incorrecta\n\n");
				system("pause");
		}
	}
	return 0;
}

int printMainMenu() {
	int opcion = NULL;

	while(TRUE) {
		system("cls");
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

int printMenuPrestamos() {
	int opcion = 0;
	while(TRUE) {
		system("cls");
		printf(" ----------------------------------------------------------- \n");
		printf("|                         PRESTAMOS                         |\n");
		printf(" ----------------------------------------------------------- \n\n");
		printf("1)Agregar\t 2)Buscar\t 3)Generar Archivo\t  4)Atras\n\n");

		printf("prestamos >> ");
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
		system("cls");
		printf(" ----------------------------------------------------------- \n");
		printf("|                          LIBROS                           |\n");
		printf(" ----------------------------------------------------------- \n\n");
		printf("1)Agregar\t 2)Buscar\t 3)Buscar por id\n");
		printf("4)Modificar\t 5)Mostrar\t 6)Atras\n\n");

		printf("libros >> ");
		if(scanf("%d", &opcion) == 0) {
			printf("La opcion ingresada es incorrecta\n\n");
			fflush(stdin);
			continue;
		}
		return opcion;
	}
}

int printMenuSedes() {
	int opcion = 0;
	while(TRUE) {
		system("cls");
		printf(" ----------------------------------------------------------- \n");
		printf("|                          SEDES                            |\n");
		printf(" ----------------------------------------------------------- \n\n");
		printf("1)Mostrar\t 2)Editar \t3)Atras\n\n");

		printf("sedes >> ");
		if(scanf("%d", &opcion) == 0) {
			printf("La opcion ingresada es incorrecta\n\n");
			fflush(stdin);
			continue;
		}
		return opcion;
	}
}

int printMenuAlumnos() {
	int opcion = 0;
	while(TRUE) {
		system("cls");
		printf(" ----------------------------------------------------------- \n");
		printf("|                         ALUMNOS                           |\n");
		printf(" ----------------------------------------------------------- \n\n");
		printf("1)Agregar\t 2)Buscar\t 3)Modificar\n");
		printf("4)Eliminar\t 5)Mostrar\t 6)Atras\n\n");

		printf("alumnos >> ");
		if(scanf("%d", &opcion) == 0) {
			printf("La opcion ingresada es incorrecta\n\n");
			fflush(stdin);
			continue;
		}
		return opcion;
	}
}
