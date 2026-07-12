#ifndef TUTORIAS_H
#define TUTORIAS_H

#include "estudiantes.h"
#include "docentes.h"

#define ARCHIVO_TUTORIAS "data/tutorias.txt"

typedef struct Tutoria {
	int  id;
	int  id_estudiante;
	int  id_docente;
	char fecha[20];
	char hora[10];
	char tema[100];
	char estado[20];  // activa, cancelada, reprogramada
	struct Tutoria *siguiente;
} Tutoria;

Tutoria* cargarTutorias();
void guardarTutorias(Tutoria *lista);
void mostrarHorarioDocente(Docente *docente, Tutoria *tutorias);
void listarTutorias(Tutoria *lista);
void listarTutoriasActivas(Tutoria *lista);
void asignarTutoria(Tutoria **lista, Estudiante *estudiantes, Docente *docentes);
void cancelarTutoria(Tutoria *lista);
void reprogramarTutoria(Tutoria *lista);
int cancelarTutoriaPropia(Tutoria *lista, int id_tutoria, int id_usuario, int esDocente);
int reprogramarTutoriaPropia(Tutoria *lista, int id_tutoria, int id_usuario, int esDocente);
void consultarPorEstudiante(Tutoria *lista, Estudiante *estudiantes);
void consultarPorDocente(Tutoria *lista, Docente *docentes);
void reporteTutoriasPorDocente(Tutoria *lista, Docente *docentes);
void reporteEstudiantesMultiples(Tutoria *lista);
void reporteDocentesMasTutorias(Tutoria *lista);
void liberarTutorias(Tutoria *lista);
int validarDisponibilidadDocente(Tutoria *lista, int id_docente, char fecha[], char hora[]);

#endif
