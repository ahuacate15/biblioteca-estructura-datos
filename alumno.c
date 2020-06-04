#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "texto.h"

//Definiendo estructura Alumno
typedef struct {
    int carnet;
    char *nombreAlumno;
    char *apellidoAlumno;
    char *carrera;
    char *telefono;
    char *correo;
    struct Alumno *siguiente;
} Alumno;

typedef struct listaAlumno {
    int total;
    Alumno *primero;
    Alumno *ultimo;
} ListaAlumno;

//Crear punteros para el primero y ultimo elemento de la lista
Alumno *primero = NULL;
Alumno *ultimo = NULL;

//prototipos de funciones
Alumno *initAlumno();
ListaAlumno *initListaAlumno();
void insertarAlumno(ListaAlumno *listaAlumno);
int existeAlumno(ListaAlumno *listaAlumno, int carnet);
void mostrarAlumnos(ListaAlumno *listaAlumno);
void BusquedaAlumno(ListaAlumno *listaAlumno);
void busquedaNombre(ListaAlumno *listaAlumno);
void busquedaApellido(ListaAlumno *listaAlumno);
void busquedaCarrera(ListaAlumno *listaAlumno);
void busquedaTelefono(ListaAlumno *listaAlumno);
void busquedaCorreo(ListaAlumno *listaAlumno);
void busquedaCarnet(ListaAlumno *listaAlumno);
void eliminarAlumno(ListaAlumno *listaAlumno);
void modificarAlumno(ListaAlumno *listaAlumno);
int validadCorreo(char mail[]);


//Declaracion de variables globales
int h;

Alumno *initAlumno() {
    Alumno *alumno = malloc(sizeof(Alumno));
	alumno->nombreAlumno = malloc(sizeof(char) * 30);
	alumno->apellidoAlumno = malloc(sizeof(char) * 30);
	alumno->carrera = malloc(sizeof(char) * 50);
	alumno->telefono = malloc(sizeof(char) * 10);
	alumno->correo = malloc(sizeof(char) * 25);
    alumno->siguiente = NULL;
    return alumno;
}

ListaAlumno *initListaAlumno() {
    ListaAlumno *lista = malloc(sizeof(ListaAlumno));
    lista->total = 0;
    lista->primero = NULL;
    lista->ultimo = NULL;
    return lista;
}

//Funcion para agregar elementos a la lista
void insertarAlumno(ListaAlumno *listaAlumno){
	
	//Reservar en memoria el nuevo nodo
	Alumno *alumno = malloc(sizeof(Alumno));
	//Declaracion de variable
	int numCarnet=0,exit=0;
	char verificarCorreo[25], email[60];
	//Limpieza de pantalla
	
	system("cls");
	printf(" ----------------------------------------------------------- \n");
	printf("|                     ALUMNOS->agregar                      |\n");
	printf(" ----------------------------------------------------------- \n\n");
	fflush(stdin);
	
	//Peticion y almacenamiento de datos
	for(h=0;h<1;h++)
	{
		//Peticion de nuevo elemento y validacion de entero
		printf("carnet: ");
		if(scanf("%d",&numCarnet)==0)
		{
			printf("error: el carnet acepta unicamente numeros***\n\n");
			fflush(stdin);
			h--;
		}
	}
	if(existeAlumno(listaAlumno, numCarnet)==0)
	{
		fflush(stdin);
		alumno->carnet=numCarnet;
		printf("nombres: ");
		alumno->nombreAlumno = getLine(30);

		printf("apellidos: ");
		alumno->apellidoAlumno = getLine(30);

		printf("carrera: ");
		alumno->carrera = getLine(50);

		printf("telefono: ");
		alumno->telefono = getLine(10);

        //Validar estructura de correo
		while(exit==0)
		{
			printf("correo institucional: ");
			alumno->correo = getLine(30);

			if(strchr(alumno->correo, '@') != NULL && strchr(alumno->correo, '.') != NULL)
			{
			    exit = 1;
			} else {
				printf("error: el correo ingresado es invalido***\n\n");
			}

		}

		alumno->siguiente = NULL;
		listaAlumno->total++;
		//Verificacion si la lista est? vacia o no
		if(listaAlumno->primero == NULL)
		{
			listaAlumno->primero = alumno;
			listaAlumno->ultimo = alumno;
		}
		else
		{
			listaAlumno->ultimo->siguiente = alumno;
			listaAlumno->ultimo = alumno;
		}
	}
	else
	{
		printf("El alumno existe. No se puede repetir\n");
	}
	printf("\n***alumno registrado***\n\n");
	system("pause");
}

//Verificando si el alumno ya existe mediante la busqueda del carnet
int existeAlumno(ListaAlumno *listaAlumno, int carnet)
{
	//Rserva de memoria
	Alumno* actual = malloc(sizeof(Alumno));

	//Establecer el primer valor de la lista
	actual= listaAlumno->primero;

	//Nodo que identifica al nodo anterior
	Alumno* anterior=malloc(sizeof(Alumno));
	anterior=NULL;

	//Declaracion de variables para determinar qu? nodo se est? buscando y si el nodo se encontr?
	int encontrado=0;
	//Si la lista tiene elementos
	if(primero!=NULL)
	{
		//Mientras el alumno actual sea distinto a NULL y si todavia no se ha encontrado el alumno
		while(actual!=NULL && encontrado==0)
		{
			//Si el nodo actual coincide con el nodo buscado
			if(actual->carnet==carnet)
			{
				//El alumno ya se encontr?
				encontrado=1;
			}
			//Se guarda el nodo actual al nodo anterior
			anterior=actual;
			//El nodo actual apuntar? al nodo siguiente
			actual=actual->siguiente;
		}
		//Si el nodo no se encuentra
		if(encontrado==0)
		{

		}
	}
	//Si no hay elementos en la lista
	else
	{
		//printf("La lista no contiene elementos\n");
	}

	return encontrado;
}

//Impresion de todos los alumnos dentro de la lista
void mostrarAlumnos(ListaAlumno *listaAlumno) {
	//Limpieza pantalla
	system("cls");
	printf(" ----------------------------------------------------------- \n");
	printf("|                     ALUMNOS->mostrar                      |\n");
	printf(" ----------------------------------------------------------- \n\n");

	//Crear puntero para el recorrido de la lista
	Alumno *i = listaAlumno->primero;
	//Preguntar si la lista esta vacia
	if(i != NULL){
		printf("Total de registros: %d\n", listaAlumno->total);
		//Mientras existan valores dentro de la lista seguir? mostrando
		while(i != NULL){
			printf("\nCarnet: %d",i->carnet);
			printf("\nNombres: %s",i->nombreAlumno);
			printf("\nApellidos: %s",i->apellidoAlumno);
			printf("\nCarrera: %s",i->carrera);
			printf("\nTelefono: %s",i->telefono);
			printf("\nCorreo: %s",i->correo);
			printf("\n");
			//Apuntar al siguiente nodo del actual
			i = i->siguiente;
		}//Fin de while
	}
	//Si la lista est? vacia
	else
	{
		printf("\n***no se encontraron resultados\n\n");
	}
	system("pause");
}

//Menu para la busqueda de Alumno
void BusquedaAlumno(ListaAlumno *listaAlumno)
{
	int salirBusquedaAlumno=0;
	while(salirBusquedaAlumno==0)
	{
		int opcion=0;
		system("cls");
		printf(" ----------------------------------------------------------- \n");
		printf("|                     ALUMNOS->buscar                       |\n");
		printf(" ----------------------------------------------------------- \n\n");
		printf("\ningresa el campo de busqueda\n");
		printf("1)carnet \t2)nombre \t3)apellido \t4)carrera\n");
		printf("5)telefono \t6)correo \t7)salir\n\n");
		printf(">> ");
		scanf("%d",&opcion);
		switch(opcion)
		{
			case 1:
				busquedaCarnet(listaAlumno);
				break;
			case 2:
				busquedaNombre(listaAlumno);
				break;
			case 3:
				busquedaApellido(listaAlumno);
				break;
			case 4:
				busquedaCarrera(listaAlumno);
				break;
			case 5:
				busquedaTelefono(listaAlumno);
				break;
			case 6:
				busquedaCorreo(listaAlumno);
				break;
			case 7:
				salirBusquedaAlumno=1;
				break;
		    default:
		    	printf("Opcion no valida");
				system("pause");
		    	break;
		}
		
	}
}

//Funcion para buscar un elemento en la lista mientras sea nombre
void busquedaNombre(ListaAlumno *listaAlumno)
{

	//Rserva de memoria
	Alumno* actual=malloc(sizeof(Alumno));

	//Establecer el primer valor de la lista
	actual=listaAlumno->primero;

	//Nodo que identifica al nodo anterior
	Alumno* anterior=malloc(sizeof(Alumno));
	anterior=NULL;

	//Declaracion de variables para determinar qu? nodo se est? buscando y si el nodo se encontr?
	int encontrado=0;
	char *nodoBuscar = malloc(sizeof(char) * 100);
	fflush(stdin);
	printf("ingresa el nombre a: ");
	nodoBuscar = getLine(100);

	//Si la lista tiene elementos
	if(listaAlumno->primero!=NULL)
	{
		//Mientras el nodo actual sea distinto a NULL y si todavia no se ha encontrado el nodo
		while(actual!=NULL)//&& encontrado==0)
		{
			//Si el nodo actual coincide con el nodo buscado
			if(strstr(actual->nombreAlumno, nodoBuscar) != NULL)
			//if(strcmp(actual->correo,nodoBuscar)==0)//if(actual->nombre==nodoBuscar)
			{
				//Impresi?n de que el nodo ya se encontr?
				//printf("ALUMNO ENCONTRADO\n");
				//printf("\nNombre: %s",actual->nombre);
				printf("\nCarnet: %d",actual->carnet);
				printf("\nNombres: %s",actual->nombreAlumno);
				printf("\nApellidos: %s",actual->apellidoAlumno);
				printf("\nCarrera: %s",actual->carrera);
				printf("\nTelefono: %s",actual->telefono);
				printf("\nCorreo: %s",actual->correo);
				printf("\n------------------------\n");
				encontrado=1;
			}
			//Se guarda el nodo actual al nodo anterior
			anterior=actual;
			//El nodo actual apuntar? al nodo siguiente
			actual=actual->siguiente;
		}
		//Si el nodo no se encuentra
		if(encontrado==0)
		{
			//Impresion de que ningun nodo coincide con la busqueda
			printf("\n***no se encontraron resultados\n\n");
		}
	}
	//Si no hay elementos en la lista
	else
	{
		printf("\n***La lista no contiene elementos\n");
	}
	system("pause");
}

//Funcion para buscar un elemento en la lista mientras sea apellido
void busquedaApellido(ListaAlumno *listaAlumno)
{

	//Rserva de memoria
	Alumno* actual=malloc(sizeof(Alumno));

	//Establecer el primer valor de la lista
	actual=listaAlumno->primero;

	//Nodo que identifica al nodo anterior
	Alumno* anterior=malloc(sizeof(Alumno));
	anterior=NULL;

	//Declaracion de variables para determinar qu? nodo se est? buscando y si el nodo se encontr?
	int encontrado=0;
	char *nodoBuscar = malloc(sizeof(char) * 100);
	fflush(stdin);
	printf("Ingresa apellido: ");
	nodoBuscar = getLine(100);

	//Si la lista tiene elementos
	if(listaAlumno->primero!=NULL)
	{
		//Mientras el nodo actual sea distinto a NULL y si todavia no se ha encontrado el nodo
		while(actual!=NULL)//&& encontrado==0)
		{
			//Si el nodo actual coincide con el nodo buscado
			if(strstr(actual->apellidoAlumno, nodoBuscar) != NULL)
			//if(strcmp(actual->correo,nodoBuscar)==0)//if(actual->nombre==nodoBuscar)
			{
				//Impresi?n de que el nodo ya se encontr?
				//printf("ALUMNO ENCONTRADO\n");
				//printf("\nNombre: %s",actual->nombre);
				printf("\nCarnet: %d",actual->carnet);
				printf("\nNombres: %s",actual->nombreAlumno);
				printf("\nApellidos: %s",actual->apellidoAlumno);
				printf("\nCarrera: %s",actual->carrera);
				printf("\nTelefono: %s",actual->telefono);
				printf("\nCorreo: %s",actual->correo);
				printf("\n------------------------\n");
				encontrado=1;
			}
			//Se guarda el nodo actual al nodo anterior
			anterior=actual;
			//El nodo actual apuntar? al nodo siguiente
			actual=actual->siguiente;
		}
		//Si el nodo no se encuentra
		if(encontrado==0)
		{
			//Impresion de que ningun nodo coincide con la busqueda
			printf("\n***no se encontraron resultados\n\n");
		}
	}
	//Si no hay elementos en la lista
	else
	{
		printf("\n***La lista no contiene elementos\n");
	}
	system("pause");
}

//Funcion para buscar un elemento en la lista mientras sea carrera
void busquedaCarrera(ListaAlumno *listaAlumno)
{
	//Rserva de memoria
	Alumno* actual=malloc(sizeof(Alumno));

	//Establecer el primer valor de la lista
	actual=listaAlumno->primero;

	//Nodo que identifica al nodo anterior
	Alumno* anterior=malloc(sizeof(Alumno));
	anterior=NULL;

	//Declaracion de variables para determinar qu? nodo se est? buscando y si el nodo se encontr?
	int encontrado=0;
	char *nodoBuscar = malloc(sizeof(char) * 100);
	fflush(stdin);
	printf("Ingresa carrera: ");
	nodoBuscar = getLine(100);

	//Si la lista tiene elementos
	if(listaAlumno->primero!=NULL)
	{
		//Mientras el nodo actual sea distinto a NULL y si todavia no se ha encontrado el nodo
		while(actual!=NULL)//&& encontrado==0)
		{
			//Si el nodo actual coincide con el nodo buscado
			if(strstr(actual->carrera, nodoBuscar) != NULL)
			//if(strcmp(actual->correo,nodoBuscar)==0)//if(actual->nombre==nodoBuscar)
			{
				//Impresi?n de que el nodo ya se encontr?
				//printf("ALUMNO ENCONTRADO\n");
				//printf("\nNombre: %s",actual->nombre);
				printf("\nCarnet: %d",actual->carnet);
				printf("\nNombres: %s",actual->nombreAlumno);
				printf("\nApellidos: %s",actual->apellidoAlumno);
				printf("\nCarrera: %s",actual->carrera);
				printf("\nTelefono: %s",actual->telefono);
				printf("\nCorreo: %s",actual->correo);
				printf("\n------------------------\n");
				encontrado=1;
			}
			//Se guarda el nodo actual al nodo anterior
			anterior=actual;
			//El nodo actual apuntar? al nodo siguiente
			actual=actual->siguiente;
		}
		//Si el nodo no se encuentra
		if(encontrado==0)
		{
			//Impresion de que ningun nodo coincide con la busqueda
			printf("\n***no se encontraron resultados\n\n");
		}
	}
	//Si no hay elementos en la lista
	else
	{
		printf("\n***La lista no contiene elementos\n\n");
	}
	system("pause");
}

//Funcion para buscar un elemento en la lista mientras sea telefono
void busquedaTelefono(ListaAlumno *listaAlumno)
{

	//Rserva de memoria
	Alumno* actual=malloc(sizeof(Alumno));
	//Establecer el primer valor de la lista
	actual=listaAlumno->primero;
	//Nodo que identifica al nodo anterior
	Alumno* anterior=malloc(sizeof(Alumno));
	anterior=NULL;
	//Declaracion de variables para determinar qu? nodo se est? buscando y si el nodo se encontr?
	int encontrado=0;
	char *nodoBuscar = malloc(sizeof(char) * 100);
	fflush(stdin);
	printf("Ingresa telefono: ");
	nodoBuscar = getLine(100);

	//Si la lista tiene elementos
	if(listaAlumno->primero!=NULL)
	{
		//Mientras el nodo actual sea distinto a NULL y si todavia no se ha encontrado el nodo
		while(actual!=NULL)//&& encontrado==0)
		{
			//Si el nodo actual coincide con el nodo buscado
			if(strstr(actual->telefono, nodoBuscar) != NULL)
			//if(strcmp(actual->correo,nodoBuscar)==0)//if(actual->nombre==nodoBuscar)
			{
				//Impresi?n de que el nodo ya se encontr?
				//printf("ALUMNO ENCONTRADO\n");
				//printf("\nNombre: %s",actual->nombre);
				printf("\nCarnet: %d",actual->carnet);
				printf("\nNombres: %s",actual->nombreAlumno);
				printf("\nApellidos: %s",actual->apellidoAlumno);
				printf("\nCarrera: %s",actual->carrera);
				printf("\nTelefono: %s",actual->telefono);
				printf("\nCorreo: %s",actual->correo);
				printf("\n------------------------\n");
				encontrado=1;
			}
			//Se guarda el nodo actual al nodo anterior
			anterior=actual;
			//El nodo actual apuntar? al nodo siguiente
			actual=actual->siguiente;
		}
		//Si el nodo no se encuentra
		if(encontrado==0)
		{
			//Impresion de que ningun nodo coincide con la busqueda
			printf("\n***no se encontraron resultados\n\n");
		}
	}
	//Si no hay elementos en la lista
	else
	{
		printf("\n**La lista no contiene elementos\n");
	}
	system("pause");
}

//Funcion para buscar un elemento en la lista mientras sea correo
void busquedaCorreo(ListaAlumno *listaAlumno)
{

	//Rserva de memoria
	Alumno* actual=malloc(sizeof(Alumno));

	//Establecer el primer valor de la lista
	actual=listaAlumno->primero;

	//Nodo que identifica al nodo anterior
	Alumno* anterior=malloc(sizeof(Alumno));
	anterior=NULL;

	//Declaracion de variables para determinar qu? nodo se est? buscando y si el nodo se encontr?
	int encontrado=0;
	char *nodoBuscar = malloc(sizeof(char) * 100);
	fflush(stdin);
	printf("Ingrese correo a buscar: ");
	nodoBuscar = getLine(100);

	//Si la lista tiene elementos
	if(listaAlumno->primero!=NULL)
	{
		//Mientras el nodo actual sea distinto a NULL y si todavia no se ha encontrado el nodo
		while(actual!=NULL)//&& encontrado==0)
		{
			//Si el nodo actual coincide con el nodo buscado
			if(strstr(actual->correo, nodoBuscar) != NULL)
			//if(strcmp(actual->correo,nodoBuscar)==0)//if(actual->nombre==nodoBuscar)
			{
				//Impresi?n de que el nodo ya se encontr?
				//printf("ALUMNO ENCONTRADO\n");
				//printf("\nNombre: %s",actual->nombre);
				printf("\nCarnet: %d",actual->carnet);
				printf("\nNombres: %s",actual->nombreAlumno);
				printf("\nApellidos: %s",actual->apellidoAlumno);
				printf("\nCarrera: %s",actual->carrera);
				printf("\nTelefono: %s",actual->telefono);
				printf("\nCorreo: %s",actual->correo);
				printf("\n------------------------\n");
				encontrado=1;
			}
			//Se guarda el nodo actual al nodo anterior
			anterior=actual;
			//El nodo actual apuntar? al nodo siguiente
			actual=actual->siguiente;
		}
		//Si el nodo no se encuentra
		if(encontrado==0)
		{
			//Impresion de que ningun nodo coincide con la busqueda
			printf("\n***no se encontraron resultados\n\n");
		}
	}
	//Si no hay elementos en la lista
	else
	{
		printf("\n***La lista no contiene elementos\n");
	}
	system("pause");
}

//Funcion para buscar un elemento en la lista
void busquedaCarnet(ListaAlumno *listaAlumno)
{

	//Rserva de memoria
	Alumno* actual=malloc(sizeof(Alumno));

	//Establecer el primer valor de la lista
	actual=listaAlumno->primero;

	//Nodo que identifica al nodo anterior
	Alumno* anterior=malloc(sizeof(Alumno));
	anterior=NULL;

	//Declaracion de variables para determinar qu? nodo se est? buscando y si el nodo se encontr?
	int encontrado=0,alumnoBuscar=0;
	fflush(stdin);
	
	//Peticion y almacenamiento de datos
	for(h=0;h<1;h++)
	{
		//Peticion de carnet de alumno y validacion de entero
		printf("Ingresa carnet: ");
		if(scanf("%d",&alumnoBuscar)==0)
		{
			fflush(stdin);
			h--;
		}
	}
	//Si la lista tiene elementos
	if(listaAlumno->primero!=NULL)
	{
		//Mientras el nodo actual sea distinto a NULL y si todavia no se ha encontrado el nodo
		while(actual!=NULL && encontrado==0)
		{
			//Si el nodo actual coincide con el nodo buscado
			if(actual->carnet==alumnoBuscar)
			{
				//Impresi?n de que el nodo ya se encontr?
				printf("alumno encontrado\n");
				//printf("\nNombre: %s",actual->nombre);
				printf("\nCarnet: %d",actual->carnet);
				printf("\nNombres: %s",actual->nombreAlumno);
				printf("\nApellidos: %s",actual->apellidoAlumno);
				printf("\nCarrera: %s",actual->carrera);
				printf("\nTelefono: %s",actual->telefono);
				printf("\nCorreo: %s",actual->correo);
				printf("\n");
				encontrado=1;
			}
			//Se guarda el nodo actual al nodo anterior
			anterior=actual;
			//El nodo actual apuntar? al nodo siguiente
			actual=actual->siguiente;
		}
		//Si el nodo no se encuentra
		if(encontrado==0)
		{
			//Impresion de que ningun nodo coincide con la busqueda
			printf("\n***no se encontraron resultados\n\n");
		}
	}
	//Si no hay elementos en la lista
	else
	{
		printf("\nLa lista no contiene elementos\n");
	}
	system("pause");
}

//Funcion para eliminar alumno de la lista
void eliminarAlumno(ListaAlumno *listaAlumno)
{

	//Rserva de memoria
	Alumno* actual=malloc(sizeof(Alumno));

	//Establecer el primer valor de la lista
	actual=listaAlumno->primero;

	//Nodo que identifica al nodo anterior
	Alumno* anterior=malloc(sizeof(Alumno));
	anterior=NULL;

	//Declaracion de variables para determinar qu? nodo se est? buscando y si el nodo se encontr?
	int encontrado=0,alumnoEliminar=0;

	//Peticion y almacenamiento de datos
	for(h=0;h<1;h++)
	{
		//Peticion de carnet de alumno y validacion de entero
		printf("Ingrese carnet de Alumno : ");
		if(scanf("%d",&alumnoEliminar)==0)
		{
			fflush(stdin);
			h--;
		}
	}
	//Si la lista tiene elementos
	if(listaAlumno->primero!=NULL)
	{
		//Mientras el nodo actual sea distinto a NULL y si todavia no se ha encontrado el nodo
		while(actual!=NULL && encontrado==0)
		{
			//Si el nodo actual coincide con el nodo buscado
			if(actual->carnet==alumnoEliminar)
			{
				//Impresi?n de que el nodo ya se encontr?
				printf("alumno encontrado\n");
				//Si el nodo a eliminar es el primero de la lista entonces el primer pasar? a estar despues
				if(actual==listaAlumno->primero)
				{
					listaAlumno->primero=listaAlumno->primero->siguiente;
				}
				//Si no es el caso anterior entonces el nodo anterior del nodo actual apuntar? al nodo siguiente del actual
				else
				{
					anterior->siguiente=actual->siguiente;
				}
				//Impresi?n de que ya se modific? el valor del nodo
				printf("\n**alumno eliminado\n");
				//Bandera para indicar que ya se encontr? el nodo
				encontrado=1;
			}
			//Se guarda el nodo actual al nodo anterior
			anterior=actual;
			//El nodo actual apuntar? al nodo siguiente
			actual=actual->siguiente;
		}
		//Si el nodo no se encuentra
		if(encontrado==0)
		{
			//Impresion de que ningun nodo coincide con la busqueda
			printf("\n***no se encontraron resultados\n\n");
		}
	}
	//Si no hay elementos en la lista
	else
	{
		printf("\nLa lista no contiene elementos\n");
	}
	system("pause");
}

//Funcion para modificar alumno de la lista
void modificarAlumno(ListaAlumno *listaAlumno)
{

	//Nodo para recorrer la lista
	Alumno* actual=malloc(sizeof(Alumno));

	//Establecer el primer valor de la pila
	actual=listaAlumno->primero;

	//Declaracion de variables para determinar qu? alumno se est? buscando y si el alumno se encontr?
	int encontrado=0,alumnoBuscar=0,datoModificar=0,opcionModificarAlumno=0,exit=0;
	char email[25];

	//printf("Ingrese nodo a modificar: ");
	for(h=0;h<1;h++)
	{
		//Petici?n del alumno a buscar
		printf("Ingrese carnet a buscar: ");
		//Almacenamiento de alumno a buscar y verificando que sea entero
		if(scanf("%d",&alumnoBuscar)==0)
		{
			fflush(stdin);
			h--;
		}
	}
	//Si la lista tiene elementos
	if(listaAlumno->primero!=NULL)
	{
		//Mientras el alumno actual sea distinto a NULL y si todavia no se ha encontrado el alumno
		while(actual!=NULL && encontrado==0)
		{
			//Si el alumno actual coincide con el alumno buscado
			if(actual->carnet==alumnoBuscar)
			{
				//Impresi?n de que el alumno ya se encontr?
				printf("\nalumno encontrado\n");
				printf("elige el dato que deseas modificar\n");
				printf("1)nombre \t2)apellido \t3)carrera\n");
				printf("4)telefono \t5)correo \n");
				printf("\n>> ");

				scanf("%d",&opcionModificarAlumno);
				switch(opcionModificarAlumno)
				{
					case 1:
						printf("Ingrese nombres del alumno: ");
						scanf("%s",&actual->nombreAlumno);
						printf("***dato modificado\n");
						break;
					case 2:
						printf("Ingrese apellidos del alumno: ");
						scanf("%s",&actual->apellidoAlumno);
						printf("***dato modificado\n");
						break;
					case 3:
						printf("Ingrese carrera del alumno: ");
						scanf("%s",&actual->carrera);
						printf("***dato modificado\n");
						break;
					case 4:
						printf("Ingrese telefono del alumno: ");
						scanf("%s",&actual->telefono);
						printf("***dato modificado\n");
						break;
					case 5:
						while(exit==0)
						{
							printf("Ingrese correo del alumno: ");
							scanf("%s",&email);
							if(strchr(email, '@') != NULL && strchr(email, '.') != NULL)
							{
								strcpy(actual->correo,email);
							    exit = 1;
							}
						}
						printf("***dato modificado\n");
						break;
				    default:
				    	printf("***Opcion no valida\n");
				    	break;
				}
				//Bandera para indicar que ya se encontr? el alumno
				encontrado=1;
				printf("\n***alumno modificado***\n\n");
			}
			//El nodo actual apuntar? al alumno siguiente
			actual=actual->siguiente;
		}
		//Si el alumno no se encuentra
		if(encontrado==0)
		{
			//Impresion de que ningun alumno coincide con la busqueda
			printf("\n***No se encontro el nodo\n");

		}
	}
	//Si no hay elementos en la lista
	else
	{
		printf("\n***La lista no contiene elementos\n");
	}

	system("pause");
}

//Validar estructura de correo
int validadCorreo(char mail[])
{
	//Declaracion de varibles
	int correoValido;
	if(strchr( mail, '.' ) && strchr( mail, '@' ))
	{
		correoValido=1;
	}
	else
	{
		correoValido=0;
	}
	return correoValido;
}
