#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//#include "texto.h"

#define TRUE 1
#define FALSE 0

//Definiendo estructura Alumno
typedef struct alumno { 
    int carnet;
    char *nombreAlumno;
    char *apellidoAlumno;
    char *carrera;
    char *telefono;
    char *correo;
    struct usuario *siguiente;
    struct usuario *anterior;
} Alumno;

//Definiendo estructura Lista de Alumnos
typedef struct listaAlumno {
    int total;
    Alumno *primero;
    Alumno *ultimo;
} ListaAlumno;

//Inicializacion de Lista de Alumnos
ListaAlumno *initListAlumno() {
    ListaAlumno *lista = malloc(sizeof(ListaAlumno));
    lista->total = 0;
    lista->primero = NULL;
    lista->ultimo = NULL;
    return lista;
}

//Estableciendo tamaños de campos de la estructura Alumnos
Alumno *initAlumno() {
    Alumno *alumno = malloc(sizeof(Alumno));
    alumno->nombreAlumno = malloc(sizeof(char) * 30); //maximo 30 caracteres
    alumno->apellidoAlumno = malloc(sizeof(char) * 30); //maximo 30 caracteres
    alumno->carrera = malloc(sizeof(char) * 100); //maximo 100 caracteres
    alumno->telefono = malloc(sizeof(char) * 10); //maximo 10 caracteres
    alumno->correo = malloc(sizeof(char) * 50); //maximo 50 caracteres
    alumno->siguiente = NULL;
    alumno->anterior = NULL;
    return alumno;
}

//Agregar Alumno a Lista
Alumno *appendAlumno(ListaAlumno *lista, Alumno *alumno) {
    Alumno *aux;
    alumno->carnet = lista->total + 1; //asigno ID autoincrementable

    if(lista->total == 0) {
        lista->primero = alumno;
        lista->ultimo = alumno;
        lista->total = 1;
    } else {
        aux = lista->ultimo;
        aux->siguiente = alumno;
        alumno->anterior = aux;
        lista->ultimo = alumno;
        lista->total++;
    }

    return alumno;
}

//Impresion de todos los Usuarios en la lista
void printListAlumno(ListaAlumno *lista) {
    Alumno *alumno = lista->primero;

    printf("\nREGISTROS: %d\n", lista->total);
    while(alumno != NULL) {
        printf("Carnet: %d\n", alumno->carnet);
        printf("Nombres de Alumno: %s\n", alumno->nombreAlumno);
        printf("Apellidos de Alumno: %s\n", alumno->apellidoAlumno);
        printf("Carrera: %s\n", alumno->carrera);
        printf("Telefono: %s\n", alumno->telefono);
        printf("Correo: %s\n", alumno->correo);
        printf("\n");

        alumno = alumno->siguiente;
    }
}

//Asignacion de tamaños a campos de Alumno
char *getLine(int max) {
    char c, *buffer = malloc(sizeof(char) * max);
    int i = 0;

    while((c = getchar()) != '\n' && i < max - 1) 
        buffer[i++] = c;
    
    buffer[i] = '\0';

    return buffer;

}

//Insercion de datos de Alumno a lista
void requestNewAlumno(ListaAlumno *lista) {
    Alumno *alumno = initAlumno();
    printf("\nIngrese datos de Nuevo Usuario\n");

    printf("Nombres del Alumno: ");
    alumno->nombreAlumno = getLine(30);

    printf("Apellidos del Alumno: ");
    alumno->apellidoAlumno = getLine(30);

    printf("Carrera del Alumno: ");
    alumno->carrera = getLine(100);

    printf("Telefono del Alumno: ");
    alumno->telefono = getLine(10);
    
    printf("Correo del Alumno: ");
    alumno->correo = getLine(50);

    printf("Elemento guardado con el ID: %d\n", appendAlumno(lista, alumno)->carnet);
}

//Eliminacion de Alumno
int removeAlumno(ListaAlumno *lista, int id) {
    Alumno *alumno = NULL;
    int cont = 0, encontrado = FALSE;

    if(lista == NULL)
        return FALSE;

    alumno = lista->primero;
    
    if(lista->total == 1) { //eliminar el unico elemento de la lista
        free(lista->primero);
        lista = initListAlumno();
    } else {  //la lista contiene mas de un elemento

        alumno = lista->primero;
        for(int i=0; i<lista->total; i++) {
            if(alumno->carnet == id) { //busco un elemento por ID
                encontrado = TRUE;
                break;
            } 
            alumno = alumno->siguiente;
        }

        if(!encontrado)
            return FALSE;
        
        if(alumno->carnet == lista->primero->carnet) { //primer elemento de la lista
            lista->primero = alumno->siguiente;
            lista->total--;
            free(alumno);
        } else if(alumno->carnet == lista->ultimo->carnet) { //ultimo elemento de la lista
            //alumno->anterior->siguiente = NULL;
            lista->ultimo = alumno->anterior;
            lista->total--;
            free(alumno);
        } else { //elementos que no se ubican en los extremos
            //alumno->anterior->siguiente = alumno->siguiente;
            lista->total--;
            free(alumno);
        }

        return TRUE;
    }
}

//Busqueda de Alumno especifico
void buscarAlumno(ListaAlumno *lista, int buscar)
{
	
	Alumno *alumno = lista->primero;
	//Inicio de la lista
	alumno = lista->primero;
	//Declaracion de variables para determinar qué alumno se está buscando y si el alumno se encontró
	int encontrado=0;

	//Mientras el alumno actual sea distinto a NULL y si todavia no se ha encontrado el alumno
	while(alumno!=NULL && encontrado==0)
	{
		//Si el alumno actual coincide con el alumno buscado
		if(alumno->carnet==buscar)
		{
			//Impresión de que el alumno ya se encontró
			printf("Alumno encontrado\n");
			printf("\nCarnet: %d",alumno->carnet);
			printf("\nNombres de Alumno: %d",alumno->nombreAlumno);
			printf("\nApellidos de Alumno: %s",alumno->apellidoAlumno);
			printf("\nCarrera: %s",alumno->carrera);
			printf("\nTelefono: %s",alumno->telefono);
			printf("\nCorreo: %s",alumno->correo);
			
			//Bandera para indicar que ya se encontró el alumno
			encontrado=1;
		}
		//El alumno actual apuntará al alumno siguiente
		alumno=alumno->siguiente;
	}
	//Si el alumno no se encuentra
	if(encontrado==0)
	{
		//Impresion de que ningun alumno coincide con la busqueda
		printf("No se encontro el alumno\n");
	}
}

//Funcion para modificar alumno en la lista
 void modificarAlumno(ListaAlumno *lista, int buscar)
{
	//Apuntando a NULL
	Alumno *alumno = lista->primero;
	//Inicio de la lista
	alumno = lista->primero;
	//Declaracion de variables para determinar qué alumno se está buscando y si el alumno se encontró
	int encontrado=0,nodoBuscar=0;

	//Mientras el alumno actual sea distinto a NULL y si todavia no se ha encontrado el alumno
	while(alumno!=NULL && encontrado==0)
	{
		//Si el alumno actual coincide con el alumno buscado
		if(alumno->carnet==buscar)
		{
			//Impresión de que el alumno ya se encontró
			printf("Ingrese nuevos Nombres de Alumno a modificar: ");
			scanf("%s",alumno->nombreAlumno);
			printf("Ingrese nuevos Apellidos de Alumno a modificar: ");
			scanf("%s",alumno->apellidoAlumno);
			printf("Ingrese nueva carrera a modificar: ");
			scanf("%s",alumno->carrera);
			printf("Ingrese nuevo telefono a modificar: ");
			scanf("%s",alumno->telefono);
			printf("Ingrese nuevo correo a modificar: ");
			scanf("%s",alumno->correo);
			//Informando que el alumno ha sido modificado
			printf("Alumno Modificado\n");
			
			//Bandera para indicar que ya se encontró el alumno
			encontrado=1;
		}
		//El alumno actual apuntará al alumno siguiente
		alumno=alumno->siguiente;
	}
	//Si el alumno no se encuentra
	if(encontrado==0)
	{
		//Impresion de que ningun alumno coincide con la busqueda
		printf("No se encontro el alumno\n");
	}
}

//Menu principal
int main()
{
	ListaAlumno *lista = initListAlumno();

	printListAlumno(lista);
    requestNewAlumno(lista);
    //requestNewAlumno(lista);
    //requestNewUsuario(lista);
    //modificarAlumno(lista,2);
    printListAlumno(lista);
    removeAlumno(lista,1);
    printListAlumno(lista);
    /*printListUsuario(lista);
    modificarAlumno(1);
    printListUsuario(lista);
    removeUsuario(lista,1);
    printListUsuario(lista);*/
	return 0;
}
