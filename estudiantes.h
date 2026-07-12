#ifndef ESTUDIANTES_H
#define ESTUDIANTES_H

#include "auth.h"

typedef struct Estudiante {
	int  id;
	char cedula[20];
	char nombre[100];
	char carrera[100];
	char correo[100];
	struct Estudiante *siguiente;
} Estudiante;

Estudiante* cargarEstudiantes();
void listarEstudiantes(Estudiante *lista);
void buscarEstudiante(Estudiante *lista);
void liberarEstudiantes(Estudiante *lista);
Estudiante* buscarEstudiantePorCedula(Estudiante *lista, char cedula[]);
Estudiante* buscarEstudiantePorId(Estudiante *lista, int id);

#endif
