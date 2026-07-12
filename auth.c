#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif


void limpiarPantalla() {
	system("cls"); 
}

/* Lee una contrasena mostrando "*" en vez del caracter real.
NOTA: en Windows usa _getch() de conio.h (funciona en Zinjai/MinGW).
En Linux/Mac se incluyo un modo alterno con termios, pero no fue
probado en este entorno -- si compilas en Linux, verifica que
funcione como esperas. */
void leerContrasenaOculta(char contrasena[], int max) {
	int i = 0;
	int ch;
#ifdef _WIN32
	while (1) {
		ch = _getch();
		if (ch == '\r' || ch == '\n') {
			break;
		} else if (ch == '\b') {
			if (i > 0) {
				i--;
				printf("\b \b");
			}
		} else if (i < max - 1) {
			contrasena[i++] = (char)ch;
			printf("*");
		}
	}
#else
	struct termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	while (1) {
		ch = getchar();
		if (ch == '\n' || ch == '\r') {
			break;
		} else if (ch == 127 || ch == '\b') {
			if (i > 0) {
				i--;
				printf("\b \b");
			}
		} else if (i < max - 1) {
			contrasena[i++] = (char)ch;
			printf("*");
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
	contrasena[i] = '\0';
	printf("\n");
	fflush(stdout);
}

/* Iniciar sistema */
void inicializarSistema() {
	FILE *f = fopen(ARCHIVO_ADMINS, "r");
	if (f != NULL) {
		fclose(f);
		return;
	}
	
	f = fopen(ARCHIVO_ADMINS, "w");
	if (f == NULL) {
		printf(">> Error: no se pudo crear el archivo de admins.\n");
		return;
	}
	fprintf(f, "1|renatosensato|123|0\n");
	fclose(f);
	
	limpiarPantalla();
	printf("\n--------------------------------------------\n");
	printf("   SISTEMA INICIALIZADO\n");
	printf("-----------------------------------------------\n\n");
	printf(">> Presiona Enter para continuar...");
	getchar();
}

/* -Validar c?dula  */
/* Revisa que una cadena contenga unicamente digitos y no este vacia */
static int soloNumeros(char str[]) {
	if (strlen(str) == 0) return 0;
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] < '0' || str[i] > '9') return 0;
	}
	return 1;
}

int validarCedula(char cedula[]) {
	if (strlen(cedula) != 10) return 0;
	
	for (int i = 0; cedula[i] != '\0'; i++) {
		if (cedula[i] < '0' || cedula[i] > '9') return 0;
	}
	
	FILE *f = fopen(ARCHIVO_ESTUDIANTES, "r");
	if (f != NULL) {
		int id;
		char ced[20], nombre[100], carrera[100], correo[100], user[50], pwd[50];
		while (fscanf(f, "%d|%19[^|]|%99[^|]|%99[^|]|%99[^|]|%49[^|]|%49[^\n]\n",
					  &id, ced, nombre, carrera, correo, user, pwd) == 7) {
			if (strcmp(ced, cedula) == 0) {
				fclose(f);
				return 0;
			}
		}
		fclose(f);
	}
	return 1;
}

/* Validar correo  */
int validarCorreo(char correo[]) {
	if (strlen(correo) == 0) return 0;
	for (int i = 0; correo[i] != '\0'; i++) {
		if (correo[i] == '@') return 1;
	}
	return 0;
}

/* Registrar estudiante */
int registrarEstudiante() {
	EstudianteRegistro est;
	est.id = 0;
	
	FILE *f = fopen(ARCHIVO_ESTUDIANTES, "r");
	if (f != NULL) {
		int id;
		char ced[20], nombre[100], carrera[100], correo[100], user[50], pwd[50];
		while (fscanf(f, "%d|%19[^|]|%99[^|]|%99[^|]|%99[^|]|%49[^|]|%49[^\n]\n",
					  &id, ced, nombre, carrera, correo, user, pwd) == 7) {
			if (id > est.id) est.id = id;
		}
		fclose(f);
	}
	est.id++;
	
	limpiarPantalla();
	printf("\n------------------------------------------------\n");
	printf("   REGISTRO DE ESTUDIANTE\n");
	printf("--------------------------------------------------\n");
	
	do {
		printf("Cedula (10 digitos numericos): ");
		fgets(est.cedula, 20, stdin);
		est.cedula[strcspn(est.cedula, "\n")] = '\0';
		if (!validarCedula(est.cedula)) {
			printf(">> Error: la cedula debe tener exactamente 10 digitos numericos, y no debe estar ya registrada.\n");
		}
	} while (!validarCedula(est.cedula));
	
	do {
		printf("Nombre completo: ");
		fgets(est.nombre, 100, stdin);
		est.nombre[strcspn(est.nombre, "\n")] = '\0';
		if (strlen(est.nombre) == 0) {
			printf(">> Error: el nombre no puede estar vacio.\n");
		}
	} while (strlen(est.nombre) == 0);
	
	do {
		printf("Carrera: ");
		fgets(est.carrera, 100, stdin);
		est.carrera[strcspn(est.carrera, "\n")] = '\0';
		if (strlen(est.carrera) == 0) {
			printf(">> Error: la carrera no puede estar vacia.\n");
		}
	} while (strlen(est.carrera) == 0);
	
	do {
		printf("Correo: ");
		fgets(est.correo, 100, stdin);
		est.correo[strcspn(est.correo, "\n")] = '\0';
		if (!validarCorreo(est.correo)) {
			printf(">> Error: correo invalido (debe contener @).\n");
		}
	} while (!validarCorreo(est.correo));
	
	printf("Usuario para login: ");
	fgets(est.usuario, 50, stdin);
	est.usuario[strcspn(est.usuario, "\n")] = '\0';
	
	printf("Contrasena: ");
	leerContrasenaOculta(est.contrasena, 50);
	
	f = fopen(ARCHIVO_ESTUDIANTES, "a");
	if (f == NULL) {
		printf("Error: no se pudo guardar.\n");
		return 0;
	}
	fprintf(f, "%d|%s|%s|%s|%s|%s|%s\n",
			est.id, est.cedula, est.nombre, est.carrera,
			est.correo, est.usuario, est.contrasena);
	fclose(f);
	
	printf("\n--------------------------------------------------\n");
	printf("   REGISTRO EXITOSO\n");
	printf("----------------------------------------------------\n");
	printf(">> Estudiante registrado con ID: %d\n", est.id);
	printf(">> Usuario: %s\n", est.usuario);
	printf("------------------------------------------------------\n");
	return 1;
}

/* -- Registrar docente ----------------------------- */
int registrarDocente() {
	DocenteRegistro doc;
	doc.id = 0;
	
	FILE *f = fopen(ARCHIVO_DOCENTES, "r");
	if (f != NULL) {
		int id;
		char cod[20], nombre[100], area[100], horario[100], user[50], pwd[50];
		while (fscanf(f, "%d|%19[^|]|%99[^|]|%99[^|]|%99[^|]|%49[^|]|%49[^\n]\n",
					  &id, cod, nombre, area, horario, user, pwd) == 7) {
			if (id > doc.id) doc.id = id;
		}
		fclose(f);
	}
	doc.id++;
	
	limpiarPantalla();
	printf("\n----------------------------------------------\n");
	printf("   REGISTRO DE DOCENTE\n");
	printf("------------------------------------------------\n");
	
	do {
		printf("Codigo de docente (solo numeros): ");
		fgets(doc.codigo, 20, stdin);
		doc.codigo[strcspn(doc.codigo, "\n")] = '\0';
		
		int invalido = 0;
		
		if (!soloNumeros(doc.codigo)) {
			printf(">> Error: el codigo debe contener solo numeros.\n");
			invalido = 1;
		} else {
			f = fopen(ARCHIVO_DOCENTES, "r");
			if (f != NULL) {
				int id;
				char cod[20], nombre[100], area[100], horario[100], user[50], pwd[50];
				while (fscanf(f, "%d|%19[^|]|%99[^|]|%99[^|]|%99[^|]|%49[^|]|%49[^\n]\n",
							  &id, cod, nombre, area, horario, user, pwd) == 7) {
					if (strcmp(cod, doc.codigo) == 0) {
						invalido = 1;
						break;
					}
				}
				fclose(f);
			}
			if (invalido) {
				printf(">> Error: codigo ya registrado.\n");
			}
		}
		
		if (invalido) doc.codigo[0] = '\0';
	} while (strlen(doc.codigo) == 0);
	
	do {
		printf("Nombre completo: ");
		fgets(doc.nombre, 100, stdin);
		doc.nombre[strcspn(doc.nombre, "\n")] = '\0';
		if (strlen(doc.nombre) == 0) {
			printf(">> Error: el nombre no puede estar vacio.\n");
		}
	} while (strlen(doc.nombre) == 0);
	
	do {
		printf("Area: ");
		fgets(doc.area, 100, stdin);
		doc.area[strcspn(doc.area, "\n")] = '\0';
		if (strlen(doc.area) == 0) {
			printf(">> Error: el area no puede estar vacia.\n");
		}
	} while (strlen(doc.area) == 0);
	
	do {
		printf("Horario (ej: Lun-Vie 8:00-12:00): ");
		fgets(doc.horario, 100, stdin);
		doc.horario[strcspn(doc.horario, "\n")] = '\0';
		if (strlen(doc.horario) == 0) {
			printf(">> Error: el horario no puede estar vacio.\n");
		}
	} while (strlen(doc.horario) == 0);
	
	printf("Usuario para login: ");
	fgets(doc.usuario, 50, stdin);
	doc.usuario[strcspn(doc.usuario, "\n")] = '\0';
	
	printf("Contrasena: ");
	leerContrasenaOculta(doc.contrasena, 50);
	
	f = fopen(ARCHIVO_DOCENTES, "a");
	if (f == NULL) {
		printf(">> Error: no se pudo guardar.\n");
		return 0;
	}
	fprintf(f, "%d|%s|%s|%s|%s|%s|%s\n",
			doc.id, doc.codigo, doc.nombre, doc.area,
			doc.horario, doc.usuario, doc.contrasena);
	fclose(f);
	
	printf("\n-------------------------------------------\n");
	printf("   REGISTRO EXITOSO\n");
	printf("---------------------------------------------\n");
	printf(">> Docente registrado con ID: %d\n", doc.id);
	printf(">> Usuario: %s\n", doc.usuario);
	printf("---------------------------------------------\n");
	return 1;
}

/* Buscar en archivo  */
static int buscarEnArchivo(char archivo[], char usuario[], char contrasena[], int *idOut, int *rolOut) {
	FILE *f = fopen(archivo, "r");
	if (f == NULL) return 0;
	
	int  id, rol;
	char usr[50], pwd[50];
	
	if (strstr(archivo, "admins") != NULL) {
		while (fscanf(f, "%d|%49[^|]|%49[^|]|%d\n", &id, usr, pwd, &rol) == 4) {
			if (strcmp(usuario, usr) == 0 && strcmp(contrasena, pwd) == 0) {
				*idOut = id;
				*rolOut = rol;
				fclose(f);
				return 1;
			}
		}
	} else if (strstr(archivo, "estudiantes") != NULL) {
		int tmp;
		char ced[20], nombre[100], carrera[100], correo[100];
		while (fscanf(f, "%d|%19[^|]|%99[^|]|%99[^|]|%99[^|]|%49[^|]|%49[^\n]\n",
					  &id, ced, nombre, carrera, correo, usr, pwd) == 7) {
			if (strcmp(usuario, usr) == 0 && strcmp(contrasena, pwd) == 0) {
				*idOut = id;
				*rolOut = ROL_ESTUDIANTE;
				fclose(f);
				return 1;
			}
		}
	} else if (strstr(archivo, "docentes") != NULL) {
		char cod[20], nombre[100], area[100], horario[100];
		while (fscanf(f, "%d|%19[^|]|%99[^|]|%99[^|]|%99[^|]|%49[^|]|%49[^\n]\n",
					  &id, cod, nombre, area, horario, usr, pwd) == 7) {
			if (strcmp(usuario, usr) == 0 && strcmp(contrasena, pwd) == 0) {
				*idOut = id;
				*rolOut = ROL_DOCENTE;
				fclose(f);
				return 1;
			}
		}
	}
	fclose(f);
	return 0;
}

/* Revisa si un nombre de usuario ya existe en admins, estudiantes o
docentes, sin importar la contrasena. Se usa para decidir si, al
fallar el login, se le ofrece al usuario registrarse. */
static int existeUsuario(char usuario[]) {
	FILE *f;
	int id, rol;
	char usr[50], pwd[50];
	
	f = fopen(ARCHIVO_ADMINS, "r");
	if (f != NULL) {
		while (fscanf(f, "%d|%49[^|]|%49[^|]|%d\n", &id, usr, pwd, &rol) == 4) {
			if (strcmp(usr, usuario) == 0) { fclose(f); return 1; }
		}
		fclose(f);
	}
	
	char ced[20], nombre[100], carrera[100], correo[100];
	f = fopen(ARCHIVO_ESTUDIANTES, "r");
	if (f != NULL) {
		while (fscanf(f, "%d|%19[^|]|%99[^|]|%99[^|]|%99[^|]|%49[^|]|%49[^\n]\n",
					  &id, ced, nombre, carrera, correo, usr, pwd) == 7) {
			if (strcmp(usr, usuario) == 0) { fclose(f); return 1; }
		}
		fclose(f);
	}
	
	char cod[20], area[100], horario[100];
	f = fopen(ARCHIVO_DOCENTES, "r");
	if (f != NULL) {
		while (fscanf(f, "%d|%19[^|]|%99[^|]|%99[^|]|%99[^|]|%49[^|]|%49[^\n]\n",
					  &id, cod, nombre, area, horario, usr, pwd) == 7) {
			if (strcmp(usr, usuario) == 0) { fclose(f); return 1; }
		}
		fclose(f);
	}
	
	return 0;
}

/* Login */
SesionActiva login() {
	SesionActiva sesion;
	sesion.rol = ROL_NINGUNO;
	sesion.id = -1;
	
	char usuario[50], contrasena[50];
	int opcion;
	
	while (1) {
		limpiarPantalla();
		printf("\n-------------------------------------------------\n");
		printf("   SISTEMA DE GESTION DE TUTORIAS - EPN\n");
		printf("-----------------GRUPO 1---------------------------\n");
		printf("   1. Iniciar sesion\n");
		printf("   0. Salir\n");
		printf("----------------------------------------------------\n");
		printf("Opcion: ");
		scanf("%d", &opcion);
		while (getchar() != '\n');
		
		if (opcion == 0) {
			sesion.rol = ROL_NINGUNO;
			return sesion;
		}
		
		if (opcion != 1) {
			continue;
		}
		
		int intentos = 0;
		int bloqueado = 0;
		
		while (intentos < 3) {
			limpiarPantalla();
			printf("\n--------------------------------------------\n");
			printf("   INICIO DE SESION\n");
			printf("-----------------------------------------------\n");
			printf("Intentos restantes: %d/3\n", 3 - intentos);
			printf("---------------------------------------------\n");
			
			printf("Usuario   : ");
			fgets(usuario, 50, stdin);
			usuario[strcspn(usuario, "\n")] = '\0';
			
			printf("Contrasena: ");
			leerContrasenaOculta(contrasena, 50);
			
			int id = -1, rol = ROL_NINGUNO;
			
			if (buscarEnArchivo(ARCHIVO_ADMINS, usuario, contrasena, &id, &rol) ||
				buscarEnArchivo(ARCHIVO_ESTUDIANTES, usuario, contrasena, &id, &rol) ||
				buscarEnArchivo(ARCHIVO_DOCENTES, usuario, contrasena, &id, &rol)) {
				sesion.id = id;
				sesion.rol = rol;
				strcpy(sesion.usuario, usuario);
				limpiarPantalla();
				printf("\n--------------------------------------------\n");
				printf("   BIENVENIDO, %s!\n", sesion.usuario);
				printf("-----------------------------------------------\n");
				printf("\n>> Presiona Enter para continuar...");
				getchar();
				return sesion;
			}
				
				if (!existeUsuario(usuario)) {
					printf("\n>> No existe ningun usuario registrado con ese nombre.\n");
					printf(">> Deseas registrarte ahora? (s/n): ");
					char resp[10];
					fgets(resp, 10, stdin);
					
					if (resp[0] == 's' || resp[0] == 'S') {
						int tipo = 0;
						printf("\n1. Registrarme como estudiante\n");
						printf("2. Registrarme como docente\n");
						printf("Opcion: ");
						scanf("%d", &tipo);
						while (getchar() != '\n');
						
						if (tipo == 1) {
							registrarEstudiante();
						} else if (tipo == 2) {
							registrarDocente();
						} else {
							printf(">> Opcion invalida.\n");
						}
						printf("\n>> Presiona Enter para continuar...");
						getchar();
					}
					break;
				}
				
				intentos++;
				printf("\n>> Usuario o contrasena incorrectos.\n");
				printf(">> Presiona Enter para intentar de nuevo...");
				getchar();
		}
		
		if (intentos >= 3) {
			bloqueado = 1;
		}
		
		if (bloqueado) {
			printf("\n>> Acceso bloqueado por demasiados intentos.\n");
			printf(">> Presiona Enter para continuar...");
			getchar();
		}
	}
}
//say no more shoto
/* Registrar admin  */
void registrarAdmin() {
	FILE *f = fopen(ARCHIVO_ADMINS, "r");
	int maxId = 0;
	if (f != NULL) {
		int id, rol;
		char usr[50], pwd[50];
		while (fscanf(f, "%d|%49[^|]|%49[^|]|%d\n", &id, usr, pwd, &rol) == 4) {
			if (id > maxId) maxId = id;
		}
		fclose(f);
	}
	
	char usuario[50], contrasena[50];
	
	limpiarPantalla();
	printf("\n-------------------------------------------\n");
	printf("   REGISTRAR NUEVO ADMIN\n");
	printf("----------------------------------------------\n");
	
	printf("Usuario   : ");
	fgets(usuario, 50, stdin);
	usuario[strcspn(usuario, "\n")] = '\0';
	
	if (strlen(usuario) == 0) {
		printf(">> Error: usuario vacio.\n");
		printf("\n>> Presiona Enter para continuar...");
		getchar();
		return;
	}
	
	f = fopen(ARCHIVO_ADMINS, "r");
	if (f != NULL) {
		int id, rol;
		char usr[50], pwd[50];
		while (fscanf(f, "%d|%49[^|]|%49[^|]|%d\n", &id, usr, pwd, &rol) == 4) {
			if (strcmp(usr, usuario) == 0) {
				printf(">> Error: usuario ya existe.\n");
				fclose(f);
				printf("\n>> Presiona Enter para continuar...");
				getchar();
				return;
			}
		}
		fclose(f);
	}
	
	printf("Contrasena: ");
	leerContrasenaOculta(contrasena, 50);
	
	f = fopen(ARCHIVO_ADMINS, "a");
	if (f == NULL) {
		printf(">> Error: no se pudo guardar.\n");
		printf("\n>> Presiona Enter para continuar...");
		getchar();
		return;
	}
	fprintf(f, "%d|%s|%s|1\n", maxId + 1, usuario, contrasena);
	fclose(f);
	
	printf("\n--------------------------------------------\n");
	printf("   NUEVO ADMINISTRADOR REGISTRADO\n");
	printf("----------------------------------------------\n");
	printf(">> Usuario: %s\n", usuario);
	printf("----------------------------------------------\n");
	printf("\n>> Presiona Enter para continuar...");
	getchar();
}
