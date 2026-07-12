#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "docentes.h"

Docente* cargarDocentes() {
	FILE *f = fopen(ARCHIVO_DOCENTES, "r");
	if (f == NULL) return NULL;
	
	Docente *lista = NULL, *ultimo = NULL;
	int id;
	char codigo[20], nombre[100], area[100], horario[100], user[50], pwd[50];
	
	while (fscanf(f, "%d|%19[^|]|%99[^|]|%99[^|]|%99[^|]|%49[^|]|%49[^\n]\n",
				  &id, codigo, nombre, area, horario, user, pwd) == 7) {
		Docente *nuevo = (Docente*)malloc(sizeof(Docente));
		nuevo->id = id;
		strcpy(nuevo->codigo, codigo);
		strcpy(nuevo->nombre, nombre);
		strcpy(nuevo->area, area);
		strcpy(nuevo->horario, horario);
		nuevo->siguiente = NULL;
		
		if (lista == NULL) {
			lista = nuevo;
		} else {
			ultimo->siguiente = nuevo;
		}
		ultimo = nuevo;
	}
	fclose(f);
	return lista;
}

void listarDocentes(Docente *lista) {
	if (lista == NULL) {
		printf(">> No hay docentes registrados.\n");
		return;
	}
	
	printf("\n%-5s %-15s %-30s %-25s %-20s\n",
		   "ID", "Codigo", "Nombre", "Area", "Horario");
	printf("%-5s %-15s %-30s %-25s %-20s\n",
		   "-----", "---------------", "------------------------------",
		   "-------------------------", "--------------------");
	
	Docente *temp = lista;
	while (temp != NULL) {
		printf("%-5d %-15s %-30s %-25s %-20s\n",
			   temp->id, temp->codigo, temp->nombre,
			   temp->area, temp->horario);
		temp = temp->siguiente;
	}
}


void listarDocentesSinCodigo(Docente *lista) {
	if (lista == NULL) {
		printf(">> No hay docentes registrados.\n");
		return;
	}
	
	printf("\n%-5s %-30s %-25s %-20s\n",
		   "ID", "Nombre", "Area", "Horario");
	printf("%-5s %-30s %-25s %-20s\n",
		   "-----", "------------------------------",
		   "-------------------------", "--------------------");
	
	Docente *temp = lista;
	while (temp != NULL) {
		printf("%-5d %-30s %-25s %-20s\n",
			   temp->id, temp->nombre, temp->area, temp->horario);
		temp = temp->siguiente;
	}
}

void buscarDocente(Docente *lista) {
	char codigo[20];
	printf("Codigo del docente: ");
	fgets(codigo, 20, stdin);
	codigo[strcspn(codigo, "\n")] = '\0';
	
	Docente *d = buscarDocentePorCodigo(lista, codigo);
	if (d == NULL) {
		printf(">> Docente no encontrado.\n");
		return;
	}
	
	printf("\n%-5s %-15s %-30s %-25s %-20s\n",
		   "ID", "Codigo", "Nombre", "Area", "Horario");
	printf("%-5d %-15s %-30s %-25s %-20s\n",
		   d->id, d->codigo, d->nombre, d->area, d->horario);
}

Docente* buscarDocentePorCodigo(Docente *lista, char codigo[]) {
	while (lista != NULL) {
		if (strcmp(lista->codigo, codigo) == 0) {
			return lista;
		}
		lista = lista->siguiente;
	}
	return NULL;
}

Docente* buscarDocentePorId(Docente *lista, int id) {
	while (lista != NULL) {
		if (lista->id == id) {
			return lista;
		}
		lista = lista->siguiente;
	}
	return NULL;
}

void liberarDocentes(Docente *lista) {
	while (lista != NULL) {
		Docente *aux = lista->siguiente;
		free(lista);
		lista = aux;
	}
}
