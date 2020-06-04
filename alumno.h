//Definiendo estructura Alumno
typedef struct {
    int carnet;
    char nombreAlumno[30];
    char apellidoAlumno[30];
    char carrera[50];
    char telefono[10];
    char correo[25];
    struct Alumno *siguiente;
} Alumno;

typedef struct listaAlumno {
    int total;
    Alumno *primero;
    Alumno *ultimo;
} ListaAlumno;

ListaAlumno *initListaAlumno();
void insertarAlumno(ListaAlumno *listaAlumno);
void mostrarAlumnos(ListaAlumno *listaAlumno);
void BusquedaAlumno(ListaAlumno *listaAlumno);
void modificarAlumno(ListaAlumno *listaAlumno);
void eliminarAlumno(ListaAlumno *listaAlumno);
void cargaInicialAlumnos(ListaAlumno *listaAlumno);
