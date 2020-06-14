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

Usuario *initUsuario();
ArbolUsuario *initArbolUsuario();
Usuario *insertarUsuario(ArbolUsuario *ptrArbol, Usuario *ptrUsuario, char *usuario, char *password, int role, int idSede);
Usuario *buscarUsuario(Usuario *ptrUsuario, char *usuario);
Usuario *iniciarSesion(ArbolUsuario *ptrArbol, char *usuario, char *password);
void cargarUsuariosPrueba(ArbolUsuario *ptrArbol);
void printUsuarios(Usuario *usuario, int contador);
int iniciarSesionMENU(const Usuario const *ptrUsuarioRaiz);
