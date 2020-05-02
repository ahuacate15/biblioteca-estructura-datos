#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//#include "texto.h"

#define TRUE 1
#define FALSE 0

typedef struct usuario { 
    int id;
    char *nombreUsuario;
    char *password;
    char *rol;
    char *sede;
    struct usuario *siguiente;
    struct usuario *anterior;
} Usuario;

typedef struct listaUsuario {
    int total;
    Usuario *primero;
    Usuario *ultimo;
} ListaUsuario;

Usuario *primero = NULL;
Usuario *ultimo = NULL;

ListaUsuario *initListUsuario() {
    ListaUsuario *lista = malloc(sizeof(ListaUsuario));
    lista->total = 0;
    lista->primero = NULL;
    lista->ultimo = NULL;
    return lista;
}

Usuario *initUsuario() {
    Usuario *usuario = malloc(sizeof(Usuario));
    usuario->nombreUsuario = malloc(sizeof(char) * 20); //maximo 60 caracteres
    usuario->password = malloc(sizeof(char) * 20); //maximo 30 caracteres
    usuario->rol = malloc(sizeof(char) * 20); //maximo 10 caracteres
    usuario->sede = malloc(sizeof(char) * 60); //maximo 254 caracteres
    usuario->siguiente = NULL;
    usuario->anterior = NULL;
    return usuario;
}

//Agregar Usuario
Usuario *appendUsuario(ListaUsuario *lista, Usuario *usuario) {
    Usuario *aux;
    usuario->id = lista->total + 1; //asigno ID autoincrementable

    if(lista->total == 0) {
        lista->primero = usuario;
        lista->ultimo = usuario;
        lista->total = 1;
    } else {
        aux = lista->ultimo;
        aux->siguiente = usuario;
        usuario->anterior = aux;
        lista->ultimo = usuario;
        lista->total++;
    }

    return usuario;
}

//Verificar si la lista Usuario está vacia
int isEmptyListUsuario(ListaUsuario *lista) {
    if(lista == NULL || lista->total == 0)
        return TRUE;
    else
        return FALSE;
}

//Impresion de todos los Usuarios en la lista
void printListUsuario(ListaUsuario *lista) {
    Usuario *usuario = lista->primero;

    printf("\nREGISTROS: %d\n", lista->total);
    while(usuario != NULL) {
        printf("id: %d\n", usuario->id);
        printf("Nombre de Usuario: %s\n", usuario->nombreUsuario);
        printf("Password: %s\n", usuario->password);
        printf("Rol: %s\n", usuario->rol);
        printf("Sede: %s\n", usuario->sede);
        printf("\n");

        usuario = usuario->siguiente;
    }
}

//Obtencion de Usuario mediante su ID
Usuario *getUsuario(ListaUsuario *lista, int id) {
    Usuario *primero, *resultado = NULL;
    int cont = 1;
    
    primero = lista->primero;
    while(primero != NULL) {
        if(cont == id) {
            resultado = primero;
            break;
        }

        primero = primero->siguiente;
        cont++;
    }
}

char *getLine(int max) {
    char c, *buffer = malloc(sizeof(char) * max);
    int i = 0;

    while((c = getchar()) != '\n' && i < max - 1) 
        buffer[i++] = c;
    
    buffer[i] = '\0';

    return buffer;

}

//solicito los datos de una sede y la agrego a la lista
void requestNewUsuario(ListaUsuario *lista) {
    Usuario *usuario = initUsuario();
    printf("\nIngrese datos de Nuevo Usuario\n");

    printf("Nombre del Usuario: ");
    usuario->nombreUsuario = getLine(20);

    printf("Password del Usuario: ");
    usuario->password = getLine(20);

    printf("Rol del Usuario: ");
    usuario->rol = getLine(20);

    printf("Sede a la que pertenece el Usuario: ");
    usuario->sede = getLine(60);

    printf("Elemento guardado con el ID: %d\n", appendUsuario(lista, usuario)->id);
}

//Eliminacion de Usuario
int removeUsuario(ListaUsuario *lista, int id) {
    Usuario *usuario = NULL;
    int cont = 0, encontrado = FALSE;

    if(lista == NULL)
        return FALSE;

    usuario = lista->primero;
    
    if(lista->total == 1) { //eliminar el unico elemento de la lista
        free(lista->primero);
        lista = initListUsuario();
    } else {  //la lista contiene mas de un elemento

        usuario = lista->primero;
        for(int i=0; i<lista->total; i++) {
            if(usuario->id == id) { //busco un elemento por ID
                encontrado = TRUE;
                break;
            } 
            usuario = usuario->siguiente;
        }

        if(!encontrado)
            return FALSE;
        
        if(usuario->id == lista->primero->id) { //primer elemento de la lista
            lista->primero = usuario->siguiente;
            lista->total--;
            free(usuario);
        } else if(usuario->id == lista->ultimo->id) { //ultimo elemento de la lista
            usuario->anterior->siguiente = NULL;
            lista->ultimo = usuario->anterior;
            lista->total--;
            free(usuario);
        } else { //elementos que no se ubican en los extremos
            usuario->anterior->siguiente = usuario->siguiente;
            lista->total--;
            free(usuario);
        }

        return TRUE;
    }
    
}

void buscarAlumno(ListaUsuario *lista, int buscar)
{
	//Apuntando a NULL
	Usuario *usuario = lista->primero;
	//Inicio de la lista
	usuario = lista->primero;
	//Declaracion de variables para determinar qué usuario se está buscando y si el usuario se encontró
	int encontrado=0;

	//Mientras el usuario actual sea distinto a NULL y si todavia no se ha encontrado el usuario
	while(usuario!=NULL && encontrado==0)
	{
		//Si el usuario actual coincide con el usuario buscado
		if(usuario->id==buscar)
		{
			//Impresión de que el usuario ya se encontró
			printf("Usuario encontrado\n");
			printf("\nID: %d",usuario->id);
			printf("\nUsuario: %d",usuario->nombreUsuario);
			printf("\nPassword: %s",usuario->password);
			printf("\nRol: %s",usuario->rol);
			printf("\nSede: %s",usuario->sede);
			
			//Bandera para indicar que ya se encontró el usuario
			encontrado=1;
		}
		//El usuario actual apuntará al usuario siguiente
		usuario=usuario->siguiente;
	}
	//Si el usuario no se encuentra
	if(encontrado==0)
	{
		//Impresion de que ningun usuario coincide con la busqueda
		printf("No se encontro el usuario\n");
	}
}


//Funcion para modificar usuario en la lista
 void modificarUsuario(ListaUsuario *lista, int buscar)
{
	//Apuntando a NULL
	Usuario *usuario = lista->primero;
	//Inicio de la lista
	usuario = lista->primero;
	//Declaracion de variables para determinar qué usuario se está buscando y si el usuario se encontró
	int encontrado=0,nodoBuscar=0;

	//Mientras el usuario actual sea distinto a NULL y si todavia no se ha encontrado el usuario
	while(usuario!=NULL && encontrado==0)
	{
		//Si el usuario actual coincide con el usuario buscado
		if(usuario->id==buscar)
		{
			//Impresión de que el usuario ya se encontró
			printf("Ingrese nuevo nombre de usuario a modificar: ");
			scanf("%s",usuario->nombreUsuario);
			printf("Ingrese nuevo password a modificar: ");
			scanf("%s",usuario->password);
			printf("Ingrese nuevo rol a modificar: ");
			scanf("%s",usuario->rol);
			printf("Ingrese nueva sede a modificar: ");
			scanf("%s",usuario->sede);
			//Informando que el usuario ha sido modificado
			printf("Usuario Modificado\n");
			
			//Bandera para indicar que ya se encontró el usuario
			encontrado=1;
		}
		//El usuario actual apuntará al usuario siguiente
		usuario=usuario->siguiente;
	}
	//Si el usuario no se encuentra
	if(encontrado==0)
	{
		//Impresion de que ningun usuario coincide con la busqueda
		printf("No se encontro el usuario\n");
	}
}

//Menu principal
int main()
{
	ListaUsuario *lista = initListUsuario();

    requestNewUsuario(lista);
    requestNewUsuario(lista);
    modificarUsuario(lista,2);
    printListUsuario(lista);
    /*printListUsuario(lista);
    modificarAlumno(1);
    printListUsuario(lista);
    removeUsuario(lista,1);
    printListUsuario(lista);*/
	return 0;
}
