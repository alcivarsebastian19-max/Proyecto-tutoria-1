#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estudiantes.h"

Estudiante* cargarEstudiantes() {
	FILE *f = fopen(ARCHIVO_ESTUDIANTES, "r");
	if (f == NULL) return NULL;
	
	Estudiante *lista = NULL, *ultimo = NULL;
	int id;
	char cedula[20], nombre[100], carrera[100], correo[100], user[50], pwd[50];
	
	while (fscanf(f, "%d|%19[^|]|%99[^|]|%99[^|]|%99[^|]|%49[^|]|%49[^\n]\n",
				  &id, cedula, nombre, carrera, correo, user, pwd) == 7) {
		Estudiante *nuevo = (Estudiante*)malloc(sizeof(Estudiante));
		nuevo->id = id;
		strcpy(nuevo->cedula, cedula);
		strcpy(nuevo->nombre, nombre);
		strcpy(nuevo->carrera, carrera);
		strcpy(nuevo->correo, correo);
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

void listarEstudiantes(Estudiante *lista) {
	if (lista == NULL) {
		printf(">> No hay estudiantes registrados.\n");
		return;
	}
	
	printf("\n%-5s %-15s %-30s %-25s %-30s\n",
		   "ID", "Cedula", "Nombre", "Carrera", "Correo");
	printf("%-5s %-15s %-30s %-25s %-30s\n",
		   "-----", "---------------", "------------------------------",
		   "-------------------------", "------------------------------");
	
	Estudiante *temp = lista;
	while (temp != NULL) {
		printf("%-5d %-15s %-30s %-25s %-30s\n",
			   temp->id, temp->cedula, temp->nombre,
			   temp->carrera, temp->correo);
		temp = temp->siguiente;
	}
}

void buscarEstudiante(Estudiante *lista) {
	char cedula[20];
	printf("Cedula del estudiante: ");
	fgets(cedula, 20, stdin);
	cedula[strcspn(cedula, "\n")] = '\0';
	
	Estudiante *e = buscarEstudiantePorCedula(lista, cedula);
	if (e == NULL) {
		printf(">> Estudiante no encontrado.\n");
		return;
	}
	
	printf("\n%-5s %-15s %-30s %-25s %-30s\n",
		   "ID", "Cedula", "Nombre", "Carrera", "Correo");
	printf("%-5d %-15s %-30s %-25s %-30s\n",
		   e->id, e->cedula, e->nombre, e->carrera, e->correo);
}

Estudiante* buscarEstudiantePorCedula(Estudiante *lista, char cedula[]) {
	while (lista != NULL) {
		if (strcmp(lista->cedula, cedula) == 0) {
			return lista;
		}
		lista = lista->siguiente;
	}
	return NULL;
}

Estudiante* buscarEstudiantePorId(Estudiante *lista, int id) {
	while (lista != NULL) {
		if (lista->id == id) {
			return lista;
		}
		lista = lista->siguiente;
	}
	return NULL;
}

void liberarEstudiantes(Estudiante *lista) {
	while (lista != NULL) {
		Estudiante *aux = lista->siguiente;
		free(lista);
		lista = aux;
	}
}
