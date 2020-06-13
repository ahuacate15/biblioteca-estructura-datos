#include <stdio.h>
#include "alumno.h"
#include "libro.h"
#include "sede.h"
#include "date.h"
#include "texto.h"
#include <stdlib.h>
#include <time.h>

#define CAMPO_FECHA 1
#define CAMPO_ALUMNO 2
#define PENDIENTE 1
#define DEVUELTO 0
#define TRUE 1
#define FALSE 2

typedef struct prestamo {
    Alumno *alumno;
    CustomDate *date;
    Libro *libro;
    int estado;
    struct Prestamo *siguiente;
} Prestamo;


typedef struct nodoPrestamo {
    int clave;
    Prestamo *prestamo;
    Prestamo *ultimoPrestamo;
    struct nodoPrestamo *izquierda;
    struct nodo *derecha;
} NodoPrestamo;


typedef struct arbolPrestamo {
    NodoPrestamo *raiz; //ordenado por fecha
    NodoPrestamo *raizAlumno; //ordenado por alumno
    int total;
} ArbolPrestamo;


/*--------------prototipo de funciones estandar----------------*/
ArbolPrestamo *initArbolPrestamo();
Prestamo *initPrestamo();
NodoPrestamo *initNodoPrestamo();
NodoPrestamo *insertarNodoPrestamo(ArbolPrestamo *arbol, NodoPrestamo *nodo, Prestamo *prestamo, int campo);
NodoPrestamo *buscarPrestamo(NodoPrestamo *nodo, int clave);

/*-------------prototipo de funciones para interfaces----------*/
void agregarPrestamoMENU(ArbolPrestamo *arbol, ListaAlumno *listaAlumno, Arbol *arbolLibro);
void buscarPrestamosMENU(ArbolPrestamo *arbol);
void imprimirPrestamo(NodoPrestamo *ptrPrestamo);
void cargarPrestamosPrueba(ArbolPrestamo *arbol, ListaAlumno *listaAlumno, Arbol *arbolLibro);

ArbolPrestamo *initArbolPrestamo() {
    ArbolPrestamo *arbol = malloc(sizeof(ArbolPrestamo));
    arbol->raiz = NULL;
    arbol->raizAlumno = NULL;
}

Prestamo *initPrestamo() {
    Prestamo *prestamo = malloc(sizeof(prestamo));
    prestamo->alumno = NULL;
    prestamo->date = NULL;
    prestamo->libro = NULL;
    prestamo->siguiente = NULL;
    prestamo->estado = PENDIENTE;
    return prestamo;
}

NodoPrestamo *initNodoPrestamo() {
    NodoPrestamo *nodo = malloc(sizeof(NodoPrestamo));
    nodo->clave = NULL;
    nodo->prestamo = NULL;
    nodo->ultimoPrestamo = NULL;
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
    return nodo;
}

NodoPrestamo *insertarNodoPrestamo(ArbolPrestamo *arbol, NodoPrestamo *nodo, Prestamo *ptrPrestamo, int campo) {
    int clave = NULL;
	clave = 10;
	
	CustomDate *customDate = ptrPrestamo->date;
	Alumno *alumno = ptrPrestamo->alumno;
    if(campo == CAMPO_FECHA) {
        clave = ptrPrestamo->date->hash;
    } else {
        clave  =ptrPrestamo->alumno->carnet;
    }
        
    //arbol vacio
    if(nodo == NULL) {
        nodo = initNodoPrestamo();
		nodo->clave = clave;
        ptrPrestamo->siguiente = NULL;
        nodo->prestamo = ptrPrestamo;
        nodo->ultimoPrestamo = ptrPrestamo;

        if(campo == CAMPO_FECHA && arbol->raiz == NULL)
            arbol->raiz = nodo;
        else if(campo == CAMPO_ALUMNO && arbol->raizAlumno == NULL)
            arbol->raizAlumno = nodo;

        arbol->total;
        return nodo;
    } else {
    	//cuando la clave del nodo ya existe, se envia al fondo de la lista
        if(clave == nodo->clave) {
            nodo->ultimoPrestamo->siguiente = ptrPrestamo;
            nodo->ultimoPrestamo = ptrPrestamo;
            free(ptrPrestamo->siguiente);
            ptrPrestamo->siguiente = NULL;
            return NULL;
        } else if(clave > nodo->clave) {
           nodo->derecha = insertarNodoPrestamo(arbol, nodo->derecha, ptrPrestamo, campo);
        } else {
            nodo->izquierda = insertarNodoPrestamo(arbol, nodo->izquierda, ptrPrestamo, campo);
        }
    }
}

NodoPrestamo *buscarPrestamo(NodoPrestamo *nodo, int clave) {
    if(nodo == NULL)
        return NULL;

    if(clave == nodo->clave)
        return nodo;
    else if(clave < nodo->clave)
        buscarPrestamo(nodo->izquierda, clave);
    else
        buscarPrestamo(nodo->derecha, clave);
}

void agregarPrestamoMENU(ArbolPrestamo *arbolPrestamo, ListaAlumno *listaAlumno, Arbol *arbolLibro) {
    CustomDate *date = NULL;
    char *stringDate = malloc(sizeof(char) * 10);
    char *isbn = malloc(sizeof(char) * 20);
    char *respuesta = malloc(sizeof(char));
    int carnet = 0;

    system("cls");
	printf(" ----------------------------------------------------------- \n");
	printf("|                    PRESTAMOS->agregar                     |\n");
	printf(" ----------------------------------------------------------- \n\n");
	fflush(stdin);

    date = now();
    printf("fecha: %s\n", date->naturalDate);

    stateCarnet:;
    printf("carnet del alumno: ");
    if(scanf("%d", &carnet) == 0) {
        printf("el valor ingresado no puede llevar letras\n");
        fflush(stdin);
        goto stateCarnet;
    }

    Alumno *alumno = listaAlumno->primero;
    Alumno *resultadoAlumno = NULL;
    while(alumno != NULL) {
        if(alumno->carnet == carnet) {
            resultadoAlumno = alumno;
            break;
        }
        alumno = alumno->siguiente;
    }

    if(resultadoAlumno == NULL) {
        printf("el alumno ingresado no existe\n");
        goto stateCarnet;
    }
    printf("\n");

    stateISBN:;
    printf("ISBN: ");
    scanf("%s", isbn);
    Nodo *nodoLibro = buscarLibroPorClave(arbolLibro->raizISBN, isbn);
    if(nodoLibro == NULL) {
        printf("el libro no existe\n");
        goto  stateISBN;
    } else {
        printf("titulo de libro: %s\n", nodoLibro->libro->titulo);
    }

    Prestamo *prestamo = malloc(sizeof(Prestamo));
    prestamo->alumno = resultadoAlumno;
    prestamo->date = date;
    prestamo->libro = nodoLibro->libro;
    prestamo->siguiente = NULL;
    prestamo->estado = PENDIENTE;

    //resto la existencia de la sede del alumno
    LibroSede *libroSede = nodoLibro->libro->libroSede;
    Sede *ptrSedeAlumno = NULL;
	int copiasDisponibles = TRUE;

    while(libroSede != NULL) {
        if(libroSede->sede->id == alumno->idSede) {
            //copias disponibles
            if(libroSede->copias > 0) {
                libroSede->copias--;
            } else {
                //no quedan copias en la sede
                printf("El libro que necesitas no se encuentra disponible.\n\n");
                copiasDisponibles = FALSE;
            }
            break;
        }
        libroSede = libroSede->siguiente;
    }

    //no se ha registrado en ninguna sede
    if(!copiasDisponibles) {
        printf("El libro que necesitas no se encuentra disponible.\n\n");
    } else {
        //arbol binario organizado por fechas de prestamo
        insertarNodoPrestamo(arbolPrestamo, arbolPrestamo->raiz, prestamo, CAMPO_FECHA);
        //arbol binario organizado por carnet de alumno
        insertarNodoPrestamo(arbolPrestamo, arbolPrestamo->raizAlumno, prestamo, CAMPO_ALUMNO);
    }
    

    stateAgregarOtro:;
    printf("\ndeseas agregar otro libro? (s/n) \n");
    printf(">> ");
    scanf("%s", respuesta);

    if(strcmp(respuesta, "s") == 0) {
        goto stateISBN;
    } else if(strcmp(respuesta, "n") != 0) {
        printf("respuesta incorrecta\n");
        goto stateAgregarOtro;
    }

    printf("\n***prestamo registrado***\n");
    system("pause");
}

void buscarPrestamosMENU(ArbolPrestamo *arbol) {
    int campoBusqueda = 0;
    int clave = 0;
    char *fecha = malloc(sizeof(char) * 10);
    NodoPrestamo *raiz = NULL;
    CustomDate *customDate = NULL;

    if(arbol == NULL) {
        printf("no hay prestamos registrado\n");
        return;
    }
    stateInicio:;
    printf("por cual campo deseas realizar la busqueda? \n");
    printf("1)fecha \t2)alumno\n");
    printf("\ncampo >> ");

    if(scanf("%d", &campoBusqueda) == 0) {
        printf("la opcion ingresada en incorrecta\n");
        fflush(stdin);
        goto stateInicio;
    }

    if(campoBusqueda < 1 || campoBusqueda > 2) {
        printf("la opcion ignresada es incorrecta\n");
        goto stateInicio;
    }

    stateSolicitudFiltro:;
    //busqueda por fecha
    if(campoBusqueda == 1) {
        printf("ingresa la fecha (dd-mm-yyyy): ");
        scanf("%s", fecha);

        customDate = convertDate(fecha);

        if(customDate == NULL) {
            printf("la fecha ingresada es incorrecta\n");
            goto stateSolicitudFiltro;
        } 
        clave = customDate->hash;
        raiz = arbol->raiz; 
    } 
    //busqueda por alumno
    else {
        printf("ingresa el carnet del alumno: ");
        if(scanf("%d", &clave) == 0) {
            printf("el carnet no puede contener letras\n");
            fflush(stdin);
            goto stateSolicitudFiltro;
        }
        raiz = arbol->raizAlumno; 

        printf("busqueda por alumno: clave->%d\n", clave);
    }

    NodoPrestamo *ptrResultado = buscarPrestamo(raiz, clave);
    if(ptrResultado == NULL) {
        printf("***no se encontraron resultados***\n");
    } else {
        imprimirPrestamo(ptrResultado);
    }

    system("pause");
}

void imprimirPrestamo(NodoPrestamo *ptrPrestamo) {
    if(ptrPrestamo != NULL) {
        printf("fecha de prestamo: %s\n", ptrPrestamo->prestamo->date->naturalDate);

        Prestamo *prestamo = ptrPrestamo->prestamo;
        Prestamo *ptrAnterior = NULL;
        while(prestamo != NULL) {

            //un alumno realiza muchos prestamos, imprimo sus datos una vez
            //como un encabezado
            if(ptrAnterior == NULL || ptrAnterior->alumno->carnet != prestamo->alumno->carnet) {
                printf("\n -------------------------------------------------\n");
                printf(
                    "|%d - %s %s\n", 
                    prestamo->alumno->carnet, 
                    prestamo->alumno->nombreAlumno,
                    prestamo->alumno->apellidoAlumno
                );
                printf(" -------------------------------------------------\n");

                printf("|Estado\t\t|ISBN\t\t|titulo\n");
                printf(" -------------------------------------------------\n");
            }
            
            printf(
                "|%s\t|%s\t|%s\n",
                prestamo->estado ? "Prestado" : "Devuelto",
                prestamo->libro->isbn,
                prestamo->libro->titulo
            );

            ptrAnterior = prestamo;
            prestamo = prestamo->siguiente;

        }
        
        
    }
}

//Buscar
void buscarRegistrosPrestamos(ArbolPrestamo *arbol) {
    int campoBusqueda = 1;
    int clave = 0;
    char *fecha = malloc(sizeof(char) * 10);
    NodoPrestamo *raiz = NULL;
    CustomDate *customDate = NULL;

    if(arbol == NULL) {
        printf("no hay prestamos registrado\n");
        return;
    }

    stateSolicitudFiltro:;
    //busqueda por fecha
    if(campoBusqueda == 1) {
        printf("ingresa la fecha (dd-mm-yyyy): ");
        scanf("%s", fecha);

        customDate = convertDate(fecha);

        if(customDate == NULL) {
            printf("la fecha ingresada es incorrecta\n");
            goto stateSolicitudFiltro;
        } 
        clave = customDate->hash;
        raiz = arbol->raiz; 
    }

    NodoPrestamo *ptrResultado = buscarPrestamo(raiz, clave);
    if(ptrResultado == NULL) {
        printf("***no se encontraron resultados***\n");
    } else {
        generarArchivo(ptrResultado);
    }

    system("pause");
}

//Impresion de archivo txt
void generarArchivo(NodoPrestamo *ptrPrestamo) {
	//Si existen prestamos
    if(ptrPrestamo != NULL) {
    	//Declaracion de variables para almacenar fecha y sus datos individuales
    	char fecha[50];
    	int dia,mes, anio, contador=0;
    	dia=ptrPrestamo->prestamo->date->day;
    	mes=ptrPrestamo->prestamo->date->month;
    	anio=ptrPrestamo->prestamo->date->year;
    	//Almacenamiento de texto junto con datos de fecha
    	sprintf(fecha,"Prestamos %d-%d-%d.txt",dia,mes,anio);
    	//Declaracion de archivo
		FILE *file;
		//Apertura de archivo con nombre
		file = fopen(fecha, "w");
		
		//Titulo de archivo
        fprintf(file,"Fecha de generacion de archivo: %s\n", ptrPrestamo->prestamo->date->naturalDate);
        //Apuntando al prestamo siguiente
        Prestamo *prestamo = ptrPrestamo->prestamo;
        //Apuntando al prestamo anterior=NULL
        Prestamo *ptrAnterior = NULL;
        while(prestamo != NULL) 
		{
            //un alumno realiza muchos prestamos, imprimo sus datos una vez
            //como un encabezado
            if(ptrAnterior == NULL || ptrAnterior->alumno->carnet != prestamo->alumno->carnet) {
            	//Impresion de datos en el archivo(Carnet, Nombres y Apellidos de Alumno)
                fprintf(file,"\n -------------------------------------------------\n");
                fprintf(file,"Carnet de Alumno: %d\n",prestamo->alumno->carnet);
                fprintf(file,"Nombres de Alumno: %s\n",prestamo->alumno->nombreAlumno);
                fprintf(file,"Apellidos de Alumno: %s\n",prestamo->alumno->apellidoAlumno);
            }
            //Impresion en archivo de ISBN y Titulo de libro prestado
            fprintf(file,"ISBN de libro prestado: %s\n",prestamo->libro->isbn);
            fprintf(file,"Titulo de libro prestado: %s\n",prestamo->libro->titulo);
            
            contador=contador+1;
            ptrAnterior = prestamo;
            prestamo = prestamo->siguiente;
        }
        
        fprintf(file,"\nTotal de prestamos: %d",contador);
        //Cierre de archivo
        fclose(file);
        //Mensaje de archivo generado
        printf("ARCHIVO GENERADO\n");
    }
}

void cargarPrestamosPrueba(ArbolPrestamo *arbol, ListaAlumno *listaAlumno, Arbol *arbolLibro) {

    Nodo *libro[15] = {};
    libro[0] = buscarLibroPorClave(arbolLibro->raizISBN, "9788483835241");
    libro[1] = buscarLibroPorClave(arbolLibro->raizISBN, "9781365425806");
    libro[2] = buscarLibroPorClave(arbolLibro->raizISBN, "9780451524935");
    libro[3] = buscarLibroPorClave(arbolLibro->raizISBN, "9780142437230");
    libro[4] = buscarLibroPorClave(arbolLibro->raizISBN, "9786073112086");
    libro[5] = buscarLibroPorClave(arbolLibro->raizISBN, "9789875667334");
    libro[6] = buscarLibroPorClave(arbolLibro->raizISBN, "9781514339060");
    libro[7] = buscarLibroPorClave(arbolLibro->raizISBN, "9786073128834");
    libro[8] = buscarLibroPorClave(arbolLibro->raizISBN, "9780307454737");
    libro[9] = buscarLibroPorClave(arbolLibro->raizISBN, "9780143035794");
    libro[10] = buscarLibroPorClave(arbolLibro->raizISBN, "9786074296730");
    libro[11] = buscarLibroPorClave(arbolLibro->raizISBN, "9786074293258");
    libro[12] = buscarLibroPorClave(arbolLibro->raizISBN, "9780786181483");
    libro[13] = buscarLibroPorClave(arbolLibro->raizISBN, "9788494994616");
    libro[14] = buscarLibroPorClave(arbolLibro->raizISBN, "9788412157772");
	
    Alumno *alumno[10] = {};
    alumno[0] = retornaAlumnoPrestamo(157416, listaAlumno);
    alumno[1] = retornaAlumnoPrestamo(167819, listaAlumno);
    alumno[2] = retornaAlumnoPrestamo(58418, listaAlumno);
    alumno[3] = retornaAlumnoPrestamo(58520, listaAlumno);
    alumno[4] = retornaAlumnoPrestamo(104720, listaAlumno);
    alumno[5] = retornaAlumnoPrestamo(105816, listaAlumno);
    alumno[6] = retornaAlumnoPrestamo(179718, listaAlumno);
    alumno[7] = retornaAlumnoPrestamo(29620, listaAlumno);
    alumno[8] = retornaAlumnoPrestamo(98314, listaAlumno);
    alumno[9] = retornaAlumnoPrestamo(130617, listaAlumno);

    Prestamo *prestamo[300] = {};
    char *listDate[5] = {"15-1-2020", "10-2-2020", "8-3-2020", "29-4-2020", "2-5-2020", "14-6-2020"};

    int cont = 0;
    srand(time(NULL));

    for(int i=0; i<10*2; i++) { //recorro los alumnos
        for(int j=0; j<15*2; j++) { //recorro el total de libros
            if(alumno[i] == NULL && libro[j] == NULL)
                continue;
 
            prestamo[cont] = malloc(sizeof(prestamo));
            prestamo[cont]->alumno = alumno[i % 10];
            prestamo[cont]->libro = libro[j % 15]->libro;
            //guardo las fechas de manera circular, para que los registros sear variados
            prestamo[cont]->date = convertDate(listDate[i % 5]);
            prestamo[cont]->estado = PENDIENTE;
            prestamo[cont]->siguiente = NULL;
            insertarNodoPrestamo(arbol, arbol->raiz, prestamo[cont], CAMPO_FECHA); 
            insertarNodoPrestamo(arbol, arbol->raizAlumno, prestamo[cont], CAMPO_ALUMNO);
            arbol->total++;
            cont++;      

            //cuando el numero aleatoreo es multiplo de 7, detengo la ejecucion del programa
            if(rand() % 11 == 0) 
                break;
        }
    }
 
}
