#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "libro.h"
#include "sede.h"
#include "traslado.h"
#include "alumno.h"
#include "prestamo.h"
#include "usuario.h"

//contantes para menu principal
#define TRUE 1
#define RETROCEDER 0

//constantes para submenu prestamos
#define AGREGAR_PRESTAMO 1
#define BUSCAR_PRESTAMO 2

//constantes para submenu prestamos
#define REALIZAR_DEVOLUCION 1

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

char printMainMenu();
char printMenuPrestamos();
char printMenuDevoluciones();
char printMenuLibros();
char printMenuSedes();
char printMenuAlumnos();


//variables globales
int usuarioLogueado = 0;

int main() {
	setlocale(LC_ALL,"spanish");
	ListaSede *listSede = initListSede();
	listSede = cargarSedesDefecto(listSede);

	Arbol *arbolLibros = initializeArbol();
	arbolLibros = cargarRegistrosDefecto(arbolLibros, listSede);

	ArbolUsuario *ptrArbolUsuario = initArbolUsuario();
	cargarUsuariosPrueba(ptrArbolUsuario);

	ListaAlumno *listaAlumno = initListaAlumno();
	cargaInicialAlumnos(listaAlumno, ptrArbolUsuario);

	ArbolPrestamo *ptrArbolPrestamo = initArbolPrestamo();
	cargarPrestamosPrueba(ptrArbolPrestamo, listaAlumno, arbolLibros);
	

	inicio:;
	while(TRUE) {
		
		stateLogin:;
		system("cls");

		if(!usuarioLogueado) {

			if(!iniciarSesionMENU(ptrArbolUsuario->raiz)) {
				printf("las credenciales ingresadas son incorrectas\n\n");
				system("pause");
				goto stateLogin;
			} else {
				usuarioLogueado = TRUE;
			}
		}



		switch(printMainMenu()) {
			case 'p': //prestamos
				while(TRUE) {
					switch(printMenuPrestamos()) {
						case 'a': //agregar
							agregarPrestamoMENU(ptrArbolPrestamo, listaAlumno, arbolLibros);
							break;
						case 'b': //buscar
							buscarPrestamosMENU(ptrArbolPrestamo);
							break;
						case 'g': //generar archivo
							buscarRegistrosPrestamos(ptrArbolPrestamo);
						case 'r': //retroceder
							goto inicio;
							break;
						default:
							printf("La opcion ingresada es incorrecta\n\n");
							system("pause");
					}
				}
				break;
			case 'd': //devoluciones
				while(TRUE) {
					switch(printMenuDevoluciones()) {
						case 'd': //hacer devolucion
							realizarDevolucion(ptrArbolPrestamo, listaAlumno, arbolLibros);
							break;
						case 'b': //buscar
							buscarDevoluciones(ptrArbolPrestamo);
						case 'r': //retroceder
							goto inicio;
							break;
						default:
							printf("La opcion ingresada es incorrecta\n\n");
							system("pause");
					}
				}
				break;
			case 't': //traslados
				realizarTrastadoMenu(arbolLibros, listSede);
				break;
			case 'l': //libros
				while(TRUE) {
					switch(printMenuLibros()) {
						case 'a': //agregar
							addLibroMenu(arbolLibros, listSede);
							break;
						case 'b': //buscar
							findLibrosMENU(arbolLibros);
							break;
						case 'i': //buscar por ID
							findLibroByClaveMenu(arbolLibros);
							break;
						case 'e': //editar
							editLibroMenu(arbolLibros);
							break;
						case 'm': //mostrar
							printLibrosMenu(arbolLibros);
							break;
						case 'r': //retroceder
							goto inicio;
							break;
						default:
							printf("La opcion ingresada es incorrecta\n\n");
							system("pause");
					}
				}
				break;
			case 's': //sedes
				while(TRUE) {
					switch (printMenuSedes()) {
						case 'm': //mostrar
							printListSedes(listSede);
							break;
						case 'e': //editar
							editSedeMenu(listSede);
							break;
						case 'r': //retroceder
							goto inicio;
							break;
						default:
							printf("La opcion ingresada es incorrecta\n");
							system("pause");
					}
				}
			case 'a': //alumnos
				while(TRUE) {
					switch(printMenuAlumnos()) {
						case 'a': //agregar
							insertarAlumno(listaAlumno, ptrArbolUsuario);
							break;
						case 'b': //buscar
							BusquedaAlumno(listaAlumno);
							break;
						case 'm': //modificar
							modificarAlumno(listaAlumno);
							break;
						case 'e': //eliminar
							eliminarAlumno(listaAlumno);
							break;
						case 't': //mostrar todos
							mostrarAlumnos(listaAlumno);
							break;
						case 'r': //retroceder
							goto inicio;
						default:
							printf("La opcion ingresada es incorrecta\n");
							system("pause");
					}
				}
			case 'c': //cerrar sesion
				usuarioLogueado = 0;
				goto stateLogin;
				return;
			default:
				printf("La opcion ingresada en incorrecta\n\n");
				system("pause");
		}
	}
	return 0;
}

char printMainMenu() {
	char opcion = 'c';

	while(TRUE) {
		fflush(stdin);
		system("cls");
		printf(" ----------------------------------------------------------- \n");
		printf("|                  SISTEMA BIBLIOTECARIO                    |\n");
		printf(" ----------------------------------------------------------- \n\n");

		printf("p)prestamos\t d)devoluciones\t t)traslados\t l)libros\n");
		printf("a)alumnos\t s)sedes\t c)cerrar sesion\n\n");

		printf(">> ");
		scanf("%c", &opcion);
		return opcion;
	}

}

char printMenuPrestamos() {
	char opcion = 'r';
	while(TRUE) {
		fflush(stdin);
		system("cls");
		printf(" ----------------------------------------------------------- \n");
		printf("|                         PRESTAMOS                         |\n");
		printf(" ----------------------------------------------------------- \n\n");
		printf("a)agregar\t b)buscar\t g)generar archivo\t  r)retroceder\n\n");

		printf("prestamos >> ");
		scanf("%c", &opcion);

		return opcion;
	}
}

char printMenuDevoluciones() {
	char opcion = 'r';
	while(TRUE) {
		fflush(stdin);
		system("cls");
		printf(" ----------------------------------------------------------- \n");
		printf("|                         DEVOLUCIONES                         |\n");
		printf(" ----------------------------------------------------------- \n\n");
		printf("d)devolucion\t b)buscar\t r)retroceder\n\n");

		printf("devolucion >> ");
		scanf("%c", &opcion);
		return opcion;
	}
}

char printMenuLibros() {
	char opcion = 'r';
	while(TRUE) {
		fflush(stdin);
		system("cls");
		printf(" ----------------------------------------------------------- \n");
		printf("|                          LIBROS                           |\n");
		printf(" ----------------------------------------------------------- \n\n");
		printf("a)agregar\t b)buscar\t i)Buscar por id\n");
		printf("e)editar\t m)mostrar\t r)retroceder\n\n");

		printf("libros >> ");
		scanf("%c", &opcion);
		return opcion;
	}
}

char printMenuSedes() {
	char opcion = 'r';
	while(TRUE) {
		fflush(stdin);
		system("cls");
		printf(" ----------------------------------------------------------- \n");
		printf("|                          SEDES                            |\n");
		printf(" ----------------------------------------------------------- \n\n");
		printf("m)mostrar\t e)editar \tr)retroceder\n\n");

		printf("sedes >> ");
		scanf("%c", &opcion);
		return opcion;
	}
}

char printMenuAlumnos() {
	char opcion = 'r';
	while(TRUE) {
		fflush(stdin);
		system("cls");
		printf(" ----------------------------------------------------------- \n");
		printf("|                         ALUMNOS                           |\n");
		printf(" ----------------------------------------------------------- \n\n");
		printf("a)agregar\t b)buscar\t m)modificar\n");
		printf("e)eliminar\t t)mostrar todos\t r)retroceder\n\n");

		printf("alumnos >> ");
		scanf("%c", &opcion);
		return opcion;
	}
}
