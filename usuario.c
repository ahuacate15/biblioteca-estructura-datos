#include <stdio.h>
#include <string.h>

#define ALUMNO 1
#define BIBLIOTECARIO 2
#define ADMINISTRADOR 3

typedef struct usuario {
    char *usuario;
    char *password;
    int role;
    int idSede;
    struct usuario *izquierda;
    struct usuario *derecha;
} Usuario;

typedef struct arbolUsuario {
    Usuario *raiz;
    int total;
} ArbolUsuario;

/*----------------- prototipo de funciones estandar ----------------*/
Usuario *initUsuario();
ArbolUsuario *initArbolUsuario();
Usuario *insertarUsuario(ArbolUsuario *ptrArbol, Usuario *ptrUsuario, char *usuario, char *password, int role, int idSede);
Usuario *buscarUsuario(Usuario *ptrUsuario, char *usuario);
Usuario *iniciarSesion(ArbolUsuario *ptrArbol, char *usuario, char *password);

void cargarUsuariosPrueba(ArbolUsuario *ptrArbol);
void printUsuarios(Usuario *ptrUsuario, int contador);

//retornal el usuario encontrado, NULL si las credenciales son incorrectas
Usuario *iniciarSesionMENU(const Usuario const *ptrUsuarioRaiz);

Usuario *initUsuario() {
    Usuario *ptrUsuario = malloc(sizeof(Usuario));
    ptrUsuario->usuario = malloc(sizeof(char) * 20);
    ptrUsuario->password = malloc(sizeof(char) * 30);
    ptrUsuario->role = ALUMNO;
    ptrUsuario->izquierda = NULL;
    ptrUsuario->derecha = NULL;
    return ptrUsuario;
}

ArbolUsuario *initArbolUsuario() {
    ArbolUsuario *ptrArbol = malloc(sizeof(ArbolUsuario));
    ptrArbol->raiz = NULL;
    ptrArbol->total = 0;
}

Usuario *insertarUsuario(ArbolUsuario *ptrArbol, Usuario *ptrUsuario, char *usuario, char *password, int role, int idSede) {
    if(ptrUsuario == NULL) {
        //ingresar usuario en la raiz del arbol
        ptrUsuario = initUsuario();
        ptrUsuario->usuario = usuario;
        ptrUsuario->password = password;
        ptrUsuario->role = role;
        ptrUsuario->idSede = idSede;
        ptrUsuario->izquierda = NULL;
        ptrUsuario->derecha = NULL;
        
        if(ptrArbol->raiz == NULL)
            ptrArbol->raiz = ptrUsuario;

        ptrArbol->total++;
        return ptrUsuario;
        
    } else {
        if(strcmp(usuario, ptrUsuario->usuario) == 0) {
            return NULL;
        } else if(strcmp(usuario, ptrUsuario->usuario) > 0) {
            ptrUsuario->derecha = insertarUsuario(ptrArbol, ptrUsuario->derecha, usuario, password, role, idSede);
        } else {
            ptrUsuario->izquierda = insertarUsuario(ptrArbol, ptrUsuario->izquierda, usuario, password, role, idSede);
        }
    }
}

Usuario *buscarUsuario(Usuario *ptrUsuario, char *usuario) {
    if(ptrUsuario == NULL)  {
        return NULL;
    }
        

    int comparacion = strcmp(usuario, ptrUsuario->usuario);
    if(comparacion == 0) {
        return ptrUsuario;
    } else if(comparacion < 0) {
        buscarUsuario(ptrUsuario->izquierda, usuario);
    } else {
        buscarUsuario(ptrUsuario->derecha, usuario);
    }
}

Usuario *iniciarSesion(ArbolUsuario *ptrArbol, char *usuario, char *password) {
    if(ptrArbol == NULL)
        return NULL;

    Usuario *ptrUsuario = buscarUsuario(ptrArbol->raiz, usuario);

    if(ptrUsuario == NULL) 
        return NULL;
    
    if(strcmp(password, ptrUsuario->password) == 0) {
        return ptrUsuario;
    } else {
        return NULL;
    }
}

void cargarUsuariosPrueba(ArbolUsuario *ptrArbol) {
    insertarUsuario(ptrArbol, ptrArbol->raiz, "bibliotecario", "12345", BIBLIOTECARIO, NULL);
    insertarUsuario(ptrArbol, ptrArbol->raiz, "admin", "admin123", ADMINISTRADOR, NULL);    
}

void printUsuarios(Usuario *ptrUsuario, int contador) {
    char *roleName = malloc(sizeof(char) * 15);
    if(ptrUsuario != NULL) {
        if(contador == 0) {
            printf(" ------------------------------------ \n");
            printf("|ROL\t\t|Nombre de usuario\n");
            printf(" ------------------------------------ \n");
        }
           
        roleName = ptrUsuario->role == ADMINISTRADOR ? "admin" : ptrUsuario->role == BIBLIOTECARIO ? "biblioteca" : "alumno";
        if(strlen(roleName) >= 10) {
            printf("|%s\t|%s\t\t\n", roleName, ptrUsuario->usuario);
        } else {
            printf("|%s\t\t|%s\t\t\n", roleName, ptrUsuario->usuario);
        }
        
        printUsuarios(ptrUsuario->izquierda, ++contador);
        printUsuarios(ptrUsuario->derecha, ++contador);
    }
}

Usuario *iniciarSesionMENU(const Usuario const *ptrUsuarioRaiz) {
    char *usuario = malloc(sizeof(char) * 30);
    char *password = malloc(sizeof(char) * 40), c = ' ';
    int cont = 0;

    printf(" ----------------------------------------------------------- \n");
    printf("|                  SISTEMA BIBLIOTECARIO                    |\n");
    printf(" ----------------------------------------------------------- \n\n");
    fflush(stdin);

    printf("usuario >> ");
    scanf("%s", usuario);

    printf("contraseña >> ");
    while(cont < 40) {
        password[cont] = getch();
        c = password[cont];
    
        if(c == 13)
            break;
        else
            printf("*");

        cont++;
    }
    printf("\n");
    password[cont] = '\0';

    Usuario *ptrUsuarioEncontrado = buscarUsuario(ptrUsuarioRaiz, usuario);
    if(ptrUsuarioEncontrado == NULL) 
        return NULL;
    
    if(strcmp(password, ptrUsuarioEncontrado->password) == 0) {
        return ptrUsuarioEncontrado;
    } else {
        return NULL;
    }

}
