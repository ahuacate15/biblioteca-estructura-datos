#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//Definiendo estructura Alumno
typedef struct{ 
    int carnet;
    char nombreAlumno[30];
    char apellidoAlumno[30];
    char carrera[50];
    char telefono[10];
    char correo[25];
    struct Alumno *siguiente;
} Alumno;

//Crear punteros para el primero y ultimo elemento de la lista
Alumno *primero = NULL;
Alumno *ultimo = NULL;

//Declaracion de variables globales
int h;
//Funcion para mostrar menú sobre las opciones
int main()
{
	int salir=0;
	while(salir==0)
	{
		int opcion=0;
		printf("\n----------MENU-----------\n");
		printf("OPCION 1: Mostrar Alumnos\n");
		printf("OPCION 2: Ingresar Datos del Alumno\n");
		printf("OPCION 3: Buscar Alumno\n");
		printf("OPCION 4: Modificar Datos del Alumno\n");
		printf("OPCION 5: Eliminar Alumno\n");
		printf("OPCION 6: Salir\n");
		printf("Ingrese opcion: ");
		scanf("%d",&opcion);
		switch(opcion)
		{
			case 1:
				mostrarAlumnos();
				break;
			case 2:
				insertarAlumno();
				break;
			case 3:
				BusquedaAlumno();
				break;
			case 4:
				modificarAlumno();
				break;
			case 5:
				eliminarAlumno();
				break;
			case 6:
				salir=1;
				break;
		    default:
		    	printf("Opcion no valida");
		    	break;
		}
	}
}

//Funcion para agregar elementos a la lista
void insertarAlumno(void){
	//Reservar en memoria el nuevo nodo
	Alumno *alumno = malloc(sizeof(Alumno));
	//Declaracion de variable
	int numCarnet=0,exit=0;
	char verificarCorreo[25],email[25];
	//Limpieza de pantalla
	system("cls");
	printf("\nIngrese datos del Alumno\n");
	//Peticion y almacenamiento de datos
	for(h=0;h<1;h++)
	{
		//Peticion de nuevo elemento y validacion de entero
		printf("Ingrese carnet: ");	
		if(scanf("%d",&numCarnet)==0)
		{
			fflush(stdin);
			h--;
		}
	}
	if(existeAlumno(numCarnet)==0)
	{
		alumno->carnet=numCarnet;	
		printf("Ingrese nombres del alumno: ");		
		scanf("%s",&alumno->nombreAlumno);
		printf("Ingrese apellidos del alumno: ");			
		scanf("%s",&alumno->apellidoAlumno);
		printf("Ingrese carrera del alumno: ");			
		scanf("%s",&alumno->carrera);
		printf("Ingrese telefono del alumno: ");			
		scanf("%s",&alumno->telefono);
        //Validar estructura de correo
		while(exit==0)
		{
			printf("Ingrese correo del alumno: ");			
			scanf("%s",&email);
			if(strchr(email, '@') != NULL && strchr(email, '.') != NULL)
			{
				strcpy(alumno->correo,email);
			    exit = 1;
			}
		}
		
		alumno->siguiente = NULL;
		//Verificacion si la lista está vacia o no
		if(primero == NULL)
		{
			primero = alumno; 		
			ultimo = alumno;
		}
		else
		{
			ultimo->siguiente = alumno; 	
			ultimo = alumno;
		}
	}
	else
	{
		printf("El alumno existe. No se puede repetir\n");
	} 
}

//Verificando si el alumno ya existe mediante la busqueda del carnet
int existeAlumno(int carnet)
{
	//Rserva de memoria
	Alumno* actual=malloc(sizeof(Alumno));
	//Establecer el primer valor de la lista
	actual=primero;
	//Nodo que identifica al nodo anterior 
	Alumno* anterior=malloc(sizeof(Alumno));
	anterior=NULL;
	//Declaracion de variables para determinar qué nodo se está buscando y si el nodo se encontró
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
				//El alumno ya se encontró
				encontrado=1;
			}
			//Se guarda el nodo actual al nodo anterior
			anterior=actual;
			//El nodo actual apuntará al nodo siguiente
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
void mostrarAlumnos(void){
	//Limpieza pantalla
	system("cls");
	//Crear puntero para el recorrido de la lista
	Alumno *i = primero;
	//Preguntar si la lista esta vacia
	if(i != NULL){
		printf("\nAlumnos\n");
		//Mientras existan valores dentro de la lista seguirá mostrando
		while(i != NULL){
			printf("\nCarnet: %d",i->carnet);
			printf("\nNombres: %s",i->nombreAlumno);
			printf("\nApellidos: %s",i->apellidoAlumno);
			printf("\nCarrera: %s",i->carrera);
			printf("\nTelefono: %s",i->telefono);
			printf("\nCorreo: %s",i->correo);
			printf("\n-------------------------------------\n");
			//Apuntar al siguiente nodo del actual
			i = i->siguiente;
		}//Fin de while
	}
	//Si la lista está vacia
	else
	{
		printf("\n\n<<NO HAY ELEMENTOS PARA MOSTRAR>>\n");
	}
	system("pause");
}

//Menu para la busqueda de Alumno
void BusquedaAlumno()
{
	int salirBusquedaAlumno=0;
	while(salirBusquedaAlumno==0)
	{
		int opcion=0;
		printf("\n----------BUSQUEDA DE ALUMNO-----------\n");
		printf("OPCION 1: Busqueda por Carnet\n");
		printf("OPCION 2: Busqueda por Nombre\n");
		printf("OPCION 3: Busqueda por Apellidos\n");
		printf("OPCION 4: Busqueda por Carrera\n");
		printf("OPCION 5: Busqueda por Telefono\n");
		printf("OPCION 6: Busqueda por Correo\n");
		printf("OPCION 7: Salir\n");
		printf("Ingrese opcion: ");
		scanf("%d",&opcion);
		switch(opcion)
		{
			case 1:
				busquedaCarnet();
				break;
			case 2:
				busquedaNombre();
				break;
			case 3:
				busquedaApellido();
				break;
			case 4:
				busquedaCarrera();
				break;
			case 5:
				busquedaTelefono();
				break;
			case 6:
				busquedaCorreo();
				break;
			case 7:
				salirBusquedaAlumno=1;
				break;
		    default:
		    	printf("Opcion no valida");
		    	break;
		}
	}
}

//Funcion para buscar un elemento en la lista mientras sea nombre
void busquedaNombre(void)
{
	system("cls");
	printf("BUSCAR ALUMNO\n");
	//Rserva de memoria
	Alumno* actual=malloc(sizeof(Alumno));
	//Establecer el primer valor de la lista
	actual=primero;
	//Nodo que identifica al nodo anterior 
	Alumno* anterior=malloc(sizeof(Alumno));
	anterior=NULL;
	//Declaracion de variables para determinar qué nodo se está buscando y si el nodo se encontró
	int encontrado=0;
	char nodoBuscar[100];
	printf("Ingrese nombre a buscar: ");
	scanf(" %s",nodoBuscar);
	//Si la lista tiene elementos
	if(primero!=NULL)
	{
		//Mientras el nodo actual sea distinto a NULL y si todavia no se ha encontrado el nodo
		while(actual!=NULL)//&& encontrado==0)
		{
			//Si el nodo actual coincide con el nodo buscado
			if(strstr(actual->nombreAlumno, nodoBuscar) != NULL)
			//if(strcmp(actual->correo,nodoBuscar)==0)//if(actual->nombre==nodoBuscar)
			{
				//Impresión de que el nodo ya se encontró
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
			//El nodo actual apuntará al nodo siguiente
			actual=actual->siguiente;
		}
		//Si el nodo no se encuentra
		if(encontrado==0)
		{
			//Impresion de que ningun nodo coincide con la busqueda
			printf("No se encontro el alumno\n");
		}
	}
	//Si no hay elementos en la lista
	else
	{
		printf("La lista no contiene elementos\n");
	}
	system("pause");
}

//Funcion para buscar un elemento en la lista mientras sea apellido
void busquedaApellido(void)
{
	system("cls");
	printf("BUSCAR ALUMNO\n");
	//Rserva de memoria
	Alumno* actual=malloc(sizeof(Alumno));
	//Establecer el primer valor de la lista
	actual=primero;
	//Nodo que identifica al nodo anterior 
	Alumno* anterior=malloc(sizeof(Alumno));
	anterior=NULL;
	//Declaracion de variables para determinar qué nodo se está buscando y si el nodo se encontró
	int encontrado=0;
	char nodoBuscar[100];
	printf("Ingrese apellido a buscar: ");
	scanf(" %s",nodoBuscar);
	//Si la lista tiene elementos
	if(primero!=NULL)
	{
		//Mientras el nodo actual sea distinto a NULL y si todavia no se ha encontrado el nodo
		while(actual!=NULL)//&& encontrado==0)
		{
			//Si el nodo actual coincide con el nodo buscado
			if(strstr(actual->apellidoAlumno, nodoBuscar) != NULL)
			//if(strcmp(actual->correo,nodoBuscar)==0)//if(actual->nombre==nodoBuscar)
			{
				//Impresión de que el nodo ya se encontró
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
			//El nodo actual apuntará al nodo siguiente
			actual=actual->siguiente;
		}
		//Si el nodo no se encuentra
		if(encontrado==0)
		{
			//Impresion de que ningun nodo coincide con la busqueda
			printf("No se encontro el alumno\n");
		}
	}
	//Si no hay elementos en la lista
	else
	{
		printf("La lista no contiene elementos\n");
	}
	system("pause");
}

//Funcion para buscar un elemento en la lista mientras sea carrera
void busquedaCarrera(void)
{
	system("cls");
	printf("BUSCAR ALUMNO\n");
	//Rserva de memoria
	Alumno* actual=malloc(sizeof(Alumno));
	//Establecer el primer valor de la lista
	actual=primero;
	//Nodo que identifica al nodo anterior 
	Alumno* anterior=malloc(sizeof(Alumno));
	anterior=NULL;
	//Declaracion de variables para determinar qué nodo se está buscando y si el nodo se encontró
	int encontrado=0;
	char nodoBuscar[100];
	printf("Ingrese carrera a buscar: ");
	scanf(" %s",nodoBuscar);
	//Si la lista tiene elementos
	if(primero!=NULL)
	{
		//Mientras el nodo actual sea distinto a NULL y si todavia no se ha encontrado el nodo
		while(actual!=NULL)//&& encontrado==0)
		{
			//Si el nodo actual coincide con el nodo buscado
			if(strstr(actual->carrera, nodoBuscar) != NULL)
			//if(strcmp(actual->correo,nodoBuscar)==0)//if(actual->nombre==nodoBuscar)
			{
				//Impresión de que el nodo ya se encontró
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
			//El nodo actual apuntará al nodo siguiente
			actual=actual->siguiente;
		}
		//Si el nodo no se encuentra
		if(encontrado==0)
		{
			//Impresion de que ningun nodo coincide con la busqueda
			printf("No se encontro el alumno\n");
		}
	}
	//Si no hay elementos en la lista
	else
	{
		printf("La lista no contiene elementos\n");
	}
	system("pause");
}

//Funcion para buscar un elemento en la lista mientras sea telefono
void busquedaTelefono(void)
{
	system("cls");
	printf("BUSCAR ALUMNO\n");
	//Rserva de memoria
	Alumno* actual=malloc(sizeof(Alumno));
	//Establecer el primer valor de la lista
	actual=primero;
	//Nodo que identifica al nodo anterior 
	Alumno* anterior=malloc(sizeof(Alumno));
	anterior=NULL;
	//Declaracion de variables para determinar qué nodo se está buscando y si el nodo se encontró
	int encontrado=0;
	char nodoBuscar[100];
	printf("Ingrese telefono a buscar: ");
	scanf(" %s",nodoBuscar);
	//Si la lista tiene elementos
	if(primero!=NULL)
	{
		//Mientras el nodo actual sea distinto a NULL y si todavia no se ha encontrado el nodo
		while(actual!=NULL)//&& encontrado==0)
		{
			//Si el nodo actual coincide con el nodo buscado
			if(strstr(actual->correo, nodoBuscar) != NULL)
			//if(strcmp(actual->correo,nodoBuscar)==0)//if(actual->nombre==nodoBuscar)
			{
				//Impresión de que el nodo ya se encontró
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
			//El nodo actual apuntará al nodo siguiente
			actual=actual->siguiente;
		}
		//Si el nodo no se encuentra
		if(encontrado==0)
		{
			//Impresion de que ningun nodo coincide con la busqueda
			printf("No se encontro el alumno\n");
		}
	}
	//Si no hay elementos en la lista
	else
	{
		printf("La lista no contiene elementos\n");
	}
	system("pause");
}

//Funcion para buscar un elemento en la lista mientras sea correo
void busquedaCorreo(void)
{
	system("cls");
	printf("BUSCAR ALUMNO\n");
	//Rserva de memoria
	Alumno* actual=malloc(sizeof(Alumno));
	//Establecer el primer valor de la lista
	actual=primero;
	//Nodo que identifica al nodo anterior 
	Alumno* anterior=malloc(sizeof(Alumno));
	anterior=NULL;
	//Declaracion de variables para determinar qué nodo se está buscando y si el nodo se encontró
	int encontrado=0;
	char nodoBuscar[100];
	printf("Ingrese correo a buscar: ");
	scanf(" %s",nodoBuscar);
	//Si la lista tiene elementos
	if(primero!=NULL)
	{
		//Mientras el nodo actual sea distinto a NULL y si todavia no se ha encontrado el nodo
		while(actual!=NULL)//&& encontrado==0)
		{
			//Si el nodo actual coincide con el nodo buscado
			if(strstr(actual->correo, nodoBuscar) != NULL)
			//if(strcmp(actual->correo,nodoBuscar)==0)//if(actual->nombre==nodoBuscar)
			{
				//Impresión de que el nodo ya se encontró
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
			//El nodo actual apuntará al nodo siguiente
			actual=actual->siguiente;
		}
		//Si el nodo no se encuentra
		if(encontrado==0)
		{
			//Impresion de que ningun nodo coincide con la busqueda
			printf("No se encontro el alumno\n");
		}
	}
	//Si no hay elementos en la lista
	else
	{
		printf("La lista no contiene elementos\n");
	}
	system("pause");
}

//Funcion para buscar un elemento en la lista
void busquedaCarnet(void)
{
	system("cls");
	printf("BUSCAR ALUMNO\n");
	//Rserva de memoria
	Alumno* actual=malloc(sizeof(Alumno));
	//Establecer el primer valor de la lista
	actual=primero;
	//Nodo que identifica al nodo anterior 
	Alumno* anterior=malloc(sizeof(Alumno));
	anterior=NULL;
	//Declaracion de variables para determinar qué nodo se está buscando y si el nodo se encontró
	int encontrado=0,alumnoBuscar=0;

	//Peticion y almacenamiento de datos
	for(h=0;h<1;h++)
	{
		//Peticion de carnet de alumno y validacion de entero
		printf("Ingrese carnet de Alumno: ");	
		if(scanf("%d",&alumnoBuscar)==0)
		{
			fflush(stdin);
			h--;
		}
	}
	//Si la lista tiene elementos
	if(primero!=NULL)
	{
		//Mientras el nodo actual sea distinto a NULL y si todavia no se ha encontrado el nodo
		while(actual!=NULL && encontrado==0)
		{
			//Si el nodo actual coincide con el nodo buscado
			if(actual->carnet==alumnoBuscar)
			{
				//Impresión de que el nodo ya se encontró
				printf("ALUMNO ENCONTRADO\n");
				//printf("\nNombre: %s",actual->nombre);
				printf("\nCarnet: %d",actual->carnet);
				printf("\nNombres: %s",actual->nombreAlumno);
				printf("\nApellidos: %s",actual->apellidoAlumno);
				printf("\nCarrera: %s",actual->carrera);
				printf("\nTelefono: %s",actual->telefono);
				printf("\nCorreo: %s",actual->correo);
				encontrado=1;
			}
			//Se guarda el nodo actual al nodo anterior
			anterior=actual;
			//El nodo actual apuntará al nodo siguiente
			actual=actual->siguiente;
		}
		//Si el nodo no se encuentra
		if(encontrado==0)
		{
			//Impresion de que ningun nodo coincide con la busqueda
			printf("No se encontro el alumno\n");
		}
	}
	//Si no hay elementos en la lista
	else
	{
		printf("La lista no contiene elementos\n");
	}
}

//Funcion para eliminar alumno de la lista
void eliminarAlumno()
{
	system("cls");
	printf("ELIMINAR ALUMNO\n");
	//Rserva de memoria
	Alumno* actual=malloc(sizeof(Alumno));
	//Establecer el primer valor de la lista
	actual=primero;
	//Nodo que identifica al nodo anterior 
	Alumno* anterior=malloc(sizeof(Alumno));
	anterior=NULL;
	//Declaracion de variables para determinar qué nodo se está buscando y si el nodo se encontró
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
	if(primero!=NULL)
	{
		//Mientras el nodo actual sea distinto a NULL y si todavia no se ha encontrado el nodo
		while(actual!=NULL && encontrado==0)
		{
			//Si el nodo actual coincide con el nodo buscado
			if(actual->carnet==alumnoEliminar)
			{
				//Impresión de que el nodo ya se encontró
				printf("ALUMNO ENCONTRADO\n");
				//Si el nodo a eliminar es el primero de la lista entonces el primer pasará a estar despues
				if(actual==primero)
				{
					primero=primero->siguiente;
				}
				//Si no es el caso anterior entonces el nodo anterior del nodo actual apuntará al nodo siguiente del actual
				else
				{
					anterior->siguiente=actual->siguiente;
				}
				//Impresión de que ya se modificó el valor del nodo
				printf("ALUMNO ELIMINADO\n");
				//Bandera para indicar que ya se encontró el nodo
				encontrado=1;
			}
			//Se guarda el nodo actual al nodo anterior
			anterior=actual;
			//El nodo actual apuntará al nodo siguiente
			actual=actual->siguiente;
		}
		//Si el nodo no se encuentra
		if(encontrado==0)
		{
			//Impresion de que ningun nodo coincide con la busqueda
			printf("No se encontro el carnet del alumno\n");
		}
	}
	//Si no hay elementos en la lista
	else
	{
		printf("La lista no contiene elementos\n");
	}
}

//Funcion para modificar alumno de la lista
void modificarAlumno()
{
	system("cls");
	printf("MODIFICAR ALUMNO\n");
	//Nodo para recorrer la lista
	Alumno* actual=malloc(sizeof(Alumno));
	//Establecer el primer valor de la pila
	actual=primero;
	//Declaracion de variables para determinar qué alumno se está buscando y si el alumno se encontró
	int encontrado=0,alumnoBuscar=0,datoModificar=0,opcionModificarAlumno=0,exit=0;
	char email[25];
	//printf("Ingrese nodo a modificar: ");
	for(h=0;h<1;h++)
	{
		//Petición del alumno a buscar
		printf("Ingrese carnet a buscar: ");
		//Almacenamiento de alumno a buscar y verificando que sea entero
		if(scanf("%d",&alumnoBuscar)==0)
		{
			fflush(stdin);
			h--;
		}
	}
	//Si la lista tiene elementos
	if(primero!=NULL)
	{
		//Mientras el alumno actual sea distinto a NULL y si todavia no se ha encontrado el alumno
		while(actual!=NULL && encontrado==0)
		{
			//Si el alumno actual coincide con el alumno buscado
			if(actual->carnet==alumnoBuscar)
			{
				//Impresión de que el alumno ya se encontró
				printf("ALUMNO ENCONTRADO\n");
				printf("¿Que dato quiere modificar?\n");
				printf("OPCION 1: Nombre\n");
				printf("OPCION 2: Apellidos\n");
				printf("OPCION 3: Carrera\n");
				printf("OPCION 4: Telefono\n");
				printf("OPCION 5: Correo\n");
				printf("Ingrese opcion: ");
				scanf("%d",&opcionModificarAlumno);
				switch(opcionModificarAlumno)
				{
					case 1:
						printf("Ingrese nombres del alumno: ");		
						scanf("%s",&actual->nombreAlumno);
						printf("DATO MODIFICADO\n");
						break;
					case 2:
						printf("Ingrese apellidos del alumno: ");			
						scanf("%s",&actual->apellidoAlumno);
						printf("DATO MODIFICADO\n");
						break;
					case 3:
						printf("Ingrese carrera del alumno: ");			
						scanf("%s",&actual->carrera);
						printf("DATO MODIFICADO\n");
						break;
					case 4:
						printf("Ingrese telefono del alumno: ");			
						scanf("%s",&actual->telefono);
						printf("DATO MODIFICADO\n");
						break;
					case 5:
						/*printf("Ingrese correo del alumno: ");			
						scanf("%s",&actual->correo);*/
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
						printf("DATO MODIFICADO\n");
						break;
				    default:
				    	printf("Opcion no valida");
				    	break;
				}
				//Bandera para indicar que ya se encontró el alumno
				encontrado=1;
			}
			//El nodo actual apuntará al alumno siguiente
			actual=actual->siguiente;
		}
		//Si el alumno no se encuentra
		if(encontrado==0)
		{
			//Impresion de que ningun alumno coincide con la busqueda
			printf("No se encontro el nodo\n");
		}
	}
	//Si no hay elementos en la lista
	else
	{
		printf("La lista no contiene elementos\n");
	}
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
