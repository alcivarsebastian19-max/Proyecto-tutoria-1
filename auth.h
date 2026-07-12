#ifndef AUTH_H
#define AUTH_H

#define ARCHIVO_ADMINS      "data/admins.txt"
#define ARCHIVO_ESTUDIANTES "data/estudiantes.txt"
#define ARCHIVO_DOCENTES    "data/docentes.txt"

#define ROL_SUPERADMIN  0
#define ROL_ADMIN       1
#define ROL_DOCENTE     2
#define ROL_ESTUDIANTE  3
#define ROL_NINGUNO    -1

typedef struct {
	int  id;
	char usuario[50];
	char contrasena[50];
	int  rol;
} SesionActiva;

typedef struct {
	int  id;
	char cedula[20];
	char nombre[100];
	char carrera[100];
	char correo[100];
	char usuario[50];
	char contrasena[50];
} EstudianteRegistro;

typedef struct {
	int  id;
	char codigo[20];
	char nombre[100];
	char area[100];
	char horario[100];
	char usuario[50];
	char contrasena[50];
} DocenteRegistro;

void limpiarPantalla();
SesionActiva login();
void registrarAdmin();
void inicializarSistema();
int registrarEstudiante();
int registrarDocente();
int validarCedula(char cedula[]);
int validarCorreo(char correo[]);
void leerContrasenaOculta(char contrasena[], int max);

#endif
