#ifndef DOCENTES_H
#define DOCENTES_H

#include "auth.h"

typedef struct Docente {
	int  id;
	char codigo[20];
	char nombre[100];
	char area[100];
	char horario[100];
	struct Docente *siguiente;
} Docente;

Docente* cargarDocentes();
void listarDocentes(Docente *lista);
void listarDocentesSinCodigo(Docente *lista);
void buscarDocente(Docente *lista);
void liberarDocentes(Docente *lista);
Docente* buscarDocentePorCodigo(Docente *lista, char codigo[]);
Docente* buscarDocentePorId(Docente *lista, int id);

#endif
