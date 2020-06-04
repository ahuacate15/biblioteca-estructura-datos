#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "texto.h"

//Definiendo estructura Alumno
typedef struct {
    int carnet;
    //estas son las linesa originales de tu archivo
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
/*Alumno *primero = NULL;
Alumno *ultimo = NULL;*/

//prototipos de funciones
Alumno *initAlumno();
ListaAlumno *initListaAlumno();
ListaAlumno *cargarAlumnoDefecto(ListaAlumno *lista);

//Declaracion de variables globales
int h;

ListaAlumno *initListaAlumno() {
    ListaAlumno *lista = malloc(sizeof(ListaAlumno));
    lista->total = 0;
    lista->primero = NULL;
    lista->ultimo = NULL;
    return lista;
}

Alumno *initAlumno() {
    Alumno *alumno = malloc(sizeof(Alumno));
    
    
    alumno->siguiente = NULL;
    return alumno;
}


//Carga inicial de registros de Alumnos
void cargaInicialAlumnos(ListaAlumno *listaAlumno)
{
	//Ingreso de Alumno 1
	Alumno *alumno1 = malloc(sizeof(Alumno));
    alumno1->carnet=1;
    strcpy(alumno1->nombreAlumno,"Carlos Daniel");
    strcpy(alumno1->apellidoAlumno,"Quintanilla");
    strcpy(alumno1->carrera,"Quimica y Farmacia");
    strcpy(alumno1->telefono,"77984632");
    strcpy(alumno1->correo,"cquintanilla@gmail.com");
    alumno1->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno1;
		listaAlumno->ultimo = alumno1;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno1;
		listaAlumno->ultimo = alumno1;
	}
	
	//Ingreso de Alumno 2
	Alumno *alumno2 = malloc(sizeof(Alumno));
    alumno2->carnet=2;
    strcpy(alumno2->nombreAlumno,"Francisco David");
    strcpy(alumno2->apellidoAlumno,"Navas Borja");
    strcpy(alumno2->carrera,"Gastronomia");
    strcpy(alumno2->telefono,"78493651");
    strcpy(alumno2->correo,"fnavas@gmail.com");
    alumno2->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno2;
		listaAlumno->ultimo = alumno2;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno2;
		listaAlumno->ultimo = alumno2;
	}
	
	//Ingreso de Alumno 3
	Alumno *alumno3 = malloc(sizeof(Alumno));
    alumno3->carnet=3;
    strcpy(alumno3->nombreAlumno,"Lola Raquel");
    strcpy(alumno3->apellidoAlumno,"Espinosa Fuentes");
    strcpy(alumno3->carrera,"Arquitectura");
    strcpy(alumno3->telefono,"68475832");
    strcpy(alumno3->correo,"lespinosa@gmail.com");
    alumno3->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno3;
		listaAlumno->ultimo = alumno3;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno3;
		listaAlumno->ultimo = alumno3;
	}
	
	//Ingreso de Alumno 4
	Alumno *alumno4 = malloc(sizeof(Alumno));
    alumno4->carnet=4;
    strcpy(alumno4->nombreAlumno,"Roman Rufino");
    strcpy(alumno4->apellidoAlumno,"Llorente Sanmartin");
    strcpy(alumno4->carrera,"Mecanica");
    strcpy(alumno4->telefono,"74927521");
    strcpy(alumno4->correo,"rllorente@gmail.com");
    alumno4->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno4;
		listaAlumno->ultimo = alumno4;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno4;
		listaAlumno->ultimo = alumno4;
	}
	
	//Ingreso de Alumno 5
	Alumno *alumno5 = malloc(sizeof(Alumno));
    alumno5->carnet=5;
    strcpy(alumno5->nombreAlumno,"Jesus Miguel");
    strcpy(alumno5->apellidoAlumno,"LaTorre Funes");
    strcpy(alumno5->carrera,"Redes");
    strcpy(alumno5->telefono,"71953235");
    strcpy(alumno5->correo,"jlatorre@gmail.com");
    alumno5->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno5;
		listaAlumno->ultimo = alumno5;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno5;
		listaAlumno->ultimo = alumno5;
	}
	
	//Ingreso de Alumno 6
	Alumno *alumno6 = malloc(sizeof(Alumno));
    alumno6->carnet=6;
    strcpy(alumno6->nombreAlumno,"Maria Adelina");
    strcpy(alumno6->apellidoAlumno,"Concepcion Bermudez");
    strcpy(alumno6->carrera,"Literatura");
    strcpy(alumno6->telefono,"69471533");
    strcpy(alumno6->correo,"mconcepcion@gmail.com");
    alumno6->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno6;
		listaAlumno->ultimo = alumno6;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno6;
		listaAlumno->ultimo = alumno6;
	}
	
	//Ingreso de Alumno 7
	Alumno *alumno7 = malloc(sizeof(Alumno));
    alumno6->carnet=7;
    strcpy(alumno7->nombreAlumno,"Laura Maria");
    strcpy(alumno7->apellidoAlumno,"Benito Tobar");
    strcpy(alumno7->carrera,"Sistemas");
    strcpy(alumno7->telefono,"70913464");
    strcpy(alumno7->correo,"lbenito@gmail.com");
    alumno7->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno7;
		listaAlumno->ultimo = alumno7;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno7;
		listaAlumno->ultimo = alumno7;
	}
	
	//Ingreso de Alumno 8
	Alumno *alumno8 = malloc(sizeof(Alumno));
    alumno8->carnet=8;
    strcpy(alumno8->nombreAlumno,"Angel Manuel");
    strcpy(alumno8->apellidoAlumno,"Mayor");
    strcpy(alumno8->carrera,"Mecanica");
    strcpy(alumno8->telefono,"75038134");
    strcpy(alumno8->correo,"amayor@gmail.com");
    alumno8->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno8;
		listaAlumno->ultimo = alumno8;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno8;
		listaAlumno->ultimo = alumno8;
	}
	
	//Ingreso de Alumno 9
	Alumno *alumno9 = malloc(sizeof(Alumno));
    alumno9->carnet=9;
    strcpy(alumno9->nombreAlumno,"Mauricio Vldimir");
    strcpy(alumno9->apellidoAlumno,"Otero");
    strcpy(alumno9->carrera,"Administracion de Empresas");
    strcpy(alumno9->telefono,"76500234");
    strcpy(alumno9->correo,"motero@gmail.com");
    alumno9->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno9;
		listaAlumno->ultimo = alumno9;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno9;
		listaAlumno->ultimo = alumno9;
	}
	
	//Ingreso de Alumno 10
	Alumno *alumno10 = malloc(sizeof(Alumno));
    alumno10->carnet=10;
    strcpy(alumno10->nombreAlumno,"Jana Mercedes");
    strcpy(alumno10->apellidoAlumno,"Gallego Andrade");
    strcpy(alumno10->carrera,"Quimica y Farmacia");
    strcpy(alumno10->telefono,"79125639");
    strcpy(alumno10->correo,"jgallego@gmail.com");
    alumno10->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno10;
		listaAlumno->ultimo = alumno10;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno10;
		listaAlumno->ultimo = alumno10;
	}
	
	//Ingreso de Alumno 11
	Alumno *alumno11 = malloc(sizeof(Alumno));
    alumno11->carnet=11;
    strcpy(alumno11->nombreAlumno,"Noemi Emma");
    strcpy(alumno11->apellidoAlumno,"Moreno Carmona");
    strcpy(alumno11->carrera,"Mercadeo");
    strcpy(alumno11->telefono,"79475581");
    strcpy(alumno11->correo,"nmoreno@gmail.com");
    alumno11->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno11;
		listaAlumno->ultimo = alumno11;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno11;
		listaAlumno->ultimo = alumno11;
	}
	
	//Ingreso de Alumno 12
	Alumno *alumno12 = malloc(sizeof(Alumno));
    alumno12->carnet=12;
    strcpy(alumno12->nombreAlumno,"Ramona Paloma");
    strcpy(alumno12->apellidoAlumno,"Matos Alcalde");
    strcpy(alumno12->carrera,"Enfermeria");
    strcpy(alumno12->telefono,"65893954");
    strcpy(alumno12->correo,"rmatos@gmail.com");
    alumno12->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno12;
		listaAlumno->ultimo = alumno12;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno12;
		listaAlumno->ultimo = alumno12;
	}
	
	//Ingreso de Alumno 13
	Alumno *alumno13 = malloc(sizeof(Alumno));
    alumno13->carnet=13;
    strcpy(alumno13->nombreAlumno,"Marti Marcelo");
    strcpy(alumno13->apellidoAlumno,"Agullo Novoa");
    strcpy(alumno13->carrera,"Psicologia");
    strcpy(alumno13->telefono,"74119430");
    strcpy(alumno13->correo,"magullo@gmail.com");
    alumno13->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno13;
		listaAlumno->ultimo = alumno13;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno13;
		listaAlumno->ultimo = alumno13;
	}
	
	//Ingreso de Alumno 14
	Alumno *alumno14 = malloc(sizeof(Alumno));
    alumno14->carnet=14;
    strcpy(alumno14->nombreAlumno,"Armando Gerardo");
    strcpy(alumno14->apellidoAlumno,"Zamora Salas");
    strcpy(alumno14->carrera,"Comunicaciones");
    strcpy(alumno14->telefono,"66847284");
    strcpy(alumno14->correo,"azamora@gmail.com");
    alumno14->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno14;
		listaAlumno->ultimo = alumno14;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno14;
		listaAlumno->ultimo = alumno14;
	}
	
	//Ingreso de Alumno 15
	Alumno *alumno15 = malloc(sizeof(Alumno));
    alumno15->carnet=15;
    strcpy(alumno15->nombreAlumno,"Rafael Domingo");
    strcpy(alumno15->apellidoAlumno,"Quiles Mejia");
    strcpy(alumno15->carrera,"Relaciones Internacionales");
    strcpy(alumno15->telefono,"66847284");
    strcpy(alumno15->correo,"rquiles@gmail.com");
    alumno15->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno15;
		listaAlumno->ultimo = alumno15;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno15;
		listaAlumno->ultimo = alumno15;
	}
	
	//Ingreso de Alumno 16
	Alumno *alumno16 = malloc(sizeof(Alumno));
    alumno16->carnet=16;
    strcpy(alumno16->nombreAlumno,"Vanessa Liliana");
    strcpy(alumno16->apellidoAlumno,"Bastida Bellino");
    strcpy(alumno16->carrera,"Negocios");
    strcpy(alumno16->telefono,"76849321");
    strcpy(alumno16->correo,"vbastida@gmail.com");
    alumno16->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno16;
		listaAlumno->ultimo = alumno16;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno16;
		listaAlumno->ultimo = alumno16;
	}
	
	//Ingreso de Alumno 17
	Alumno *alumno17 = malloc(sizeof(Alumno));
    alumno17->carnet=17;
    strcpy(alumno17->nombreAlumno,"Carmen Andrea");
    strcpy(alumno17->apellidoAlumno,"Cabezas Gaspar");
    strcpy(alumno17->carrera,"Telecomunicaciones");
    strcpy(alumno17->telefono,"76300134");
    strcpy(alumno17->correo,"ccabezas@gmail.com");
    alumno17->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno17;
		listaAlumno->ultimo = alumno17;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno17;
		listaAlumno->ultimo = alumno17;
	}
	
	//Ingreso de Alumno 18
	Alumno *alumno18 = malloc(sizeof(Alumno));
    alumno18->carnet=18;
    strcpy(alumno18->nombreAlumno,"Jamal Jacinto");
    strcpy(alumno18->apellidoAlumno,"Garca Campos");
    strcpy(alumno18->carrera,"Sistemas");
    strcpy(alumno18->telefono,"79375611");
    strcpy(alumno18->correo,"jgarca@gmail.com");
    alumno18->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno18;
		listaAlumno->ultimo = alumno18;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno18;
		listaAlumno->ultimo = alumno18;
	}
	
	//Ingreso de Alumno 19
	Alumno *alumno19 = malloc(sizeof(Alumno));
    alumno19->carnet=19;
    strcpy(alumno19->nombreAlumno,"Florencio Sergi");
    strcpy(alumno19->apellidoAlumno,"Bravo Roman");
    strcpy(alumno19->carrera,"Redes");
    strcpy(alumno19->telefono,"71133579");
    strcpy(alumno19->correo,"fbravo@gmail.com");
    alumno19->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno19;
		listaAlumno->ultimo = alumno19;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno19;
		listaAlumno->ultimo = alumno19;
	}
	
	//Ingreso de Alumno 20
	Alumno *alumno20 = malloc(sizeof(Alumno));
    alumno20->carnet=20;
    strcpy(alumno20->nombreAlumno,"Marcela Rosa");
    strcpy(alumno20->apellidoAlumno,"Guevara Sobrino");
    strcpy(alumno20->carrera,"Gastronomia");
    strcpy(alumno20->telefono,"77992656");
    strcpy(alumno20->correo,"mguevara@gmail.com");
    alumno20->siguiente=NULL;
    if(listaAlumno->primero == NULL)
	{
		listaAlumno->primero = alumno20;
		listaAlumno->ultimo = alumno20;
	}
	else
	{
		listaAlumno->ultimo->siguiente = alumno20;
		listaAlumno->ultimo = alumno20;
	}
}


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

	if(existeAlumno(numCarnet,listaAlumno)==0 && numCarnet>=0 && numCarnet<=99999999)

	{
		fflush(stdin);
		alumno->carnet=numCarnet;
		printf("Ingrese nombres del alumno: ");
		scanf("%s",&alumno->nombreAlumno);
		printf("Ingrese apellidos del alumno: ");
		scanf("%s",&alumno->apellidoAlumno);
		printf("Ingrese carrera del alumno: ");
		scanf("%s",&alumno->carrera);
		//printf("Ingrese telefono del alumno: ");
		//scanf("%s",&verificarTelefono);
		//Validar estructura de telefono
		while(exitTelefono==0)
		{
			printf("Ingrese telefono del alumno(sin guiones): ");
			scanf("%s",&verificarTelefono);
			int respuesta=0,i=0;
	
			for(i=0;i<strlen(verificarTelefono);i++)
			{
				if((isdigit(verificarTelefono[i])))
				{
					respuesta=respuesta;
				}
				else
				{
					respuesta=respuesta+1;
				}
			}
			
			if(respuesta==0)
			{
				strcpy(alumno->telefono,verificarTelefono);
				exitTelefono=1;
			}
		}

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
		printf("El alumno existe o no es valido\n");
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
	if(listaAlumno->primero!=NULL)
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
	char email[25],verificarTelef[25];

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
						/*printf("Ingrese telefono del alumno: ");
						scanf("%s",&actual->telefono);*/
						printf("Ingrese telefono del alumno(sin guiones): ");
						scanf("%s",&verificarTelef);
						int respuesta=0,i=0;
				
						for(i=0;i<strlen(verificarTelef);i++)
						{
							if((isdigit(verificarTelef[i])))
							{
								respuesta=respuesta;
							}
							else
							{
								respuesta=respuesta+1;
							}
						}
						
						if(respuesta==0)
						{
							strcpy(actual->telefono,verificarTelef);
							//exitTelefono=1;
							printf("DATO MODIFICADO\n");
						}
						else
						{
							printf("DATO NO MODIFICADO\n");
						}
						
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
