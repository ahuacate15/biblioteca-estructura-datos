typedef struct {
    int carnet;
    //estas son las linesa originales de tu archivo
    char *nombreAlumno;
    char *apellidoAlumno;
    char *carrera;
    char *telefono;
    char *correo;
    int idSede;
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
Alumno *retornaAlumnoPrestamo(int carnet, ListaAlumno *listaAlumno);
