#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tutorias.h"

/* -- Cargar tutorias ----------------------------- */
Tutoria* cargarTutorias() {
	FILE *f = fopen(ARCHIVO_TUTORIAS, "r");
	if (f == NULL) return NULL;
	
	Tutoria *lista = NULL, *ultimo = NULL;
	int id, id_est, id_doc;
	char fecha[20], hora[10], tema[100], estado[20];
	
	while (fscanf(f, "%d|%d|%d|%19[^|]|%9[^|]|%99[^|]|%19[^\n]\n",
				  &id, &id_est, &id_doc, fecha, hora, tema, estado) == 7) {
		Tutoria *nuevo = (Tutoria*)malloc(sizeof(Tutoria));
		nuevo->id = id;
		nuevo->id_estudiante = id_est;
		nuevo->id_docente = id_doc;
		strcpy(nuevo->fecha, fecha);
		strcpy(nuevo->hora, hora);
		strcpy(nuevo->tema, tema);
		strcpy(nuevo->estado, estado);
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

/*  Guardar tutorias - */
void guardarTutorias(Tutoria *lista) {
	FILE *f = fopen(ARCHIVO_TUTORIAS, "w");
	if (f == NULL) {
		printf(">> Error: no se pudo guardar.\n");
		return;
	}
	
	while (lista != NULL) {
		fprintf(f, "%d|%d|%d|%s|%s|%s|%s\n",
				lista->id, lista->id_estudiante, lista->id_docente,
				lista->fecha, lista->hora, lista->tema, lista->estado);
		lista = lista->siguiente;
	}
	fclose(f);
}

/* Validar disponibilidad del docente */
int validarDisponibilidadDocente(Tutoria *lista, int id_docente, char fecha[], char hora[]) {
	while (lista != NULL) {
		if (lista->id_docente == id_docente &&
			strcmp(lista->fecha, fecha) == 0 &&
			strcmp(lista->hora, hora) == 0 &&
			strcmp(lista->estado, "activa") == 0) {
			return 0; // No disponible
		}
		lista = lista->siguiente;
	}
	return 1; // Disponible
}

/* -- Asignar tutoria ------------------------------ */
void asignarTutoria(Tutoria **lista, Estudiante *estudiantes, Docente *docentes) {
	Tutoria nueva;
	nueva.id = 0;
	nueva.estado[0] = '\0';
	char cedula[20], codigo[20];
	
	// Obtener siguiente ID
	Tutoria *temp = *lista;
	while (temp != NULL) {
		if (temp->id > nueva.id) nueva.id = temp->id;
		temp = temp->siguiente;
	}
	nueva.id++;
	
	printf("\n=============================================\n");
	printf("   ASIGNAR TUTORIA\n");
	printf("=============================================\n");
	
	// C?dula del estudiante
	do {
		printf("Cedula del estudiante: ");
		fgets(cedula, 20, stdin);
		cedula[strcspn(cedula, "\n")] = '\0';
		
		Estudiante *e = buscarEstudiantePorCedula(estudiantes, cedula);
		if (e == NULL) {
			printf(">> Error: estudiante no registrado.\n");
		} else {
			nueva.id_estudiante = e->id;
		}
	} while (nueva.id_estudiante == 0);
	
	// C?digo del docente
	do {
		printf("Codigo del docente: ");
		fgets(codigo, 20, stdin);
		codigo[strcspn(codigo, "\n")] = '\0';
		
		Docente *d = buscarDocentePorCodigo(docentes, codigo);
		if (d == NULL) {
			printf(">> Error: docente no registrado.\n");
		} else {
			nueva.id_docente = d->id;
		}
	} while (nueva.id_docente == 0);
	
	// Fecha
	do {
		printf("Fecha (DD/MM/AAAA): ");
		fgets(nueva.fecha, 20, stdin);
		nueva.fecha[strcspn(nueva.fecha, "\n")] = '\0';
		if (strlen(nueva.fecha) == 0) {
			printf(">> Error: fecha no puede estar vacia.\n");
		}
	} while (strlen(nueva.fecha) == 0);
	
	// Hora
	do {
		printf("Hora (HH:MM): ");
		fgets(nueva.hora, 10, stdin);
		nueva.hora[strcspn(nueva.hora, "\n")] = '\0';
		if (strlen(nueva.hora) == 0) {
			printf(">> Error: hora no puede estar vacia.\n");
		}
	} while (strlen(nueva.hora) == 0);
	
	// Verificar disponibilidad del docente
	if (!validarDisponibilidadDocente(*lista, nueva.id_docente, nueva.fecha, nueva.hora)) {
		printf(">> Error: el docente ya tiene una tutoria en esa fecha y hora.\n");
		return;
	}
	
	// Asunto
	do {
		printf("Asunto de la tutoria: ");
		fgets(nueva.tema, 100, stdin);
		nueva.tema[strcspn(nueva.tema, "\n")] = '\0';
		if (strlen(nueva.tema) == 0) {
			printf(">> Error: el asunto no puede estar vacio.\n");
		}
	} while (strlen(nueva.tema) == 0);
	
	strcpy(nueva.estado, "activa");
	
	// Crear nodo
	Tutoria *nodo = (Tutoria*)malloc(sizeof(Tutoria));
	*nodo = nueva;
	nodo->siguiente = NULL;
	
	// Insertar al final
	if (*lista == NULL) {
		*lista = nodo;
	} else {
		temp = *lista;
		while (temp->siguiente != NULL) temp = temp->siguiente;
		temp->siguiente = nodo;
	}
	
	guardarTutorias(*lista);
	printf("\n>> Tutoria #%d asignada correctamente.\n", nueva.id);
}

/* -- Cancelar tutoria ----------------------------- */
void cancelarTutoria(Tutoria *lista) {
	int id;
	printf("ID de la tutoria a cancelar: ");
	scanf("%d", &id);
	while (getchar() != '\n');
	
	Tutoria *temp = lista;
	while (temp != NULL) {
		if (temp->id == id) {
			if (strcmp(temp->estado, "activa") != 0) {
				printf(">> Solo se pueden cancelar tutorias activas.\n");
				return;
			}
			strcpy(temp->estado, "cancelada");
			guardarTutorias(lista);
			printf(">> Tutoria #%d cancelada.\n", id);
			return;
		}
		temp = temp->siguiente;
	}
	printf(">> Tutoria #%d no encontrada.\n", id);
}

/* -- Reprogramar tutoria -------------------------- */
void reprogramarTutoria(Tutoria *lista) {
	int id;
	char nuevaFecha[20], nuevaHora[10];
	
	printf("ID de la tutoria a reprogramar: ");
	scanf("%d", &id);
	while (getchar() != '\n');
	
	Tutoria *temp = lista;
	while (temp != NULL) {
		if (temp->id == id) {
			if (strcmp(temp->estado, "activa") != 0) {
				printf(">> Solo se pueden reprogramar tutorias activas.\n");
				return;
			}
			
			printf("Nueva fecha (DD/MM/AAAA): ");
			fgets(nuevaFecha, 20, stdin);
			nuevaFecha[strcspn(nuevaFecha, "\n")] = '\0';
			
			printf("Nueva hora (HH:MM): ");
			fgets(nuevaHora, 10, stdin);
			nuevaHora[strcspn(nuevaHora, "\n")] = '\0';
			
			// Verificar disponibilidad en nueva fecha/hora
			if (!validarDisponibilidadDocente(lista, temp->id_docente, nuevaFecha, nuevaHora)) {
				printf(">> Error: el docente no esta disponible en esa fecha y hora.\n");
				return;
			}
			
			strcpy(temp->fecha, nuevaFecha);
			strcpy(temp->hora, nuevaHora);
			strcpy(temp->estado, "reprogramada");
			guardarTutorias(lista);
			printf(">> Tutoria #%d reprogramada.\n", id);
			return;
		}
		temp = temp->siguiente;
	}
	printf(">> Tutoria #%d no encontrada.\n", id);
}

/* -- Cancelar tutoria propia (estudiante o docente) --
id_usuario es el id de sesion (id_estudiante o id_docente segun
corresponda) y esDocente indica cual de los dos comparar. Verifica
que la tutoria le pertenezca antes de cancelarla. */
int cancelarTutoriaPropia(Tutoria *lista, int id_tutoria, int id_usuario, int esDocente) {
	Tutoria *temp = lista;
	while (temp != NULL) {
		if (temp->id == id_tutoria) {
			int pertenece = esDocente ? (temp->id_docente == id_usuario)
				: (temp->id_estudiante == id_usuario);
			if (!pertenece) {
				printf(">> Error: esa tutoria no te pertenece.\n");
				return 0;
			}
			if (strcmp(temp->estado, "activa") != 0) {
				printf(">> Solo se pueden cancelar tutorias activas.\n");
				return 0;
			}
			strcpy(temp->estado, "cancelada");
			guardarTutorias(lista);
			printf(">> Tutoria #%d cancelada.\n", id_tutoria);
			return 1;
		}
		temp = temp->siguiente;
	}
	printf(">> Tutoria #%d no encontrada.\n", id_tutoria);
	return 0;
}

/* -- Reprogramar tutoria propia (estudiante o docente) -- */
int reprogramarTutoriaPropia(Tutoria *lista, int id_tutoria, int id_usuario, int esDocente) {
	Tutoria *temp = lista;
	while (temp != NULL) {
		if (temp->id == id_tutoria) {
			int pertenece = esDocente ? (temp->id_docente == id_usuario)
				: (temp->id_estudiante == id_usuario);
			if (!pertenece) {
				printf(">> Error: esa tutoria no te pertenece.\n");
				return 0;
			}
			if (strcmp(temp->estado, "activa") != 0) {
				printf(">> Solo se pueden reprogramar tutorias activas.\n");
				return 0;
			}
			
			char nuevaFecha[20], nuevaHora[10];
			printf("Nueva fecha (DD/MM/AAAA): ");
			fgets(nuevaFecha, 20, stdin);
			nuevaFecha[strcspn(nuevaFecha, "\n")] = '\0';
			
			printf("Nueva hora (HH:MM): ");
			fgets(nuevaHora, 10, stdin);
			nuevaHora[strcspn(nuevaHora, "\n")] = '\0';
			
			if (!validarDisponibilidadDocente(lista, temp->id_docente, nuevaFecha, nuevaHora)) {
				printf(">> Error: el docente no esta disponible en esa fecha y hora.\n");
				return 0;
			}
			
			strcpy(temp->fecha, nuevaFecha);
			strcpy(temp->hora, nuevaHora);
			strcpy(temp->estado, "reprogramada");
			guardarTutorias(lista);
			printf(">> Tutoria #%d reprogramada.\n", id_tutoria);
			return 1;
		}
		temp = temp->siguiente;
	}
	printf(">> Tutoria #%d no encontrada.\n", id_tutoria);
	return 0;
}

/* -- Mostrar horario de un docente ---------------
Muestra el horario general del docente y una tabla con sus
tutorias activas/reprogramadas (agenda). La usa tanto el docente
para ver su propio horario, como el estudiante al solicitar una
tutoria, para que vea la disponibilidad antes de elegir fecha/hora. */
void mostrarHorarioDocente(Docente *docente, Tutoria *tutorias) {
	if (docente == NULL) {
		printf(">> Docente no encontrado.\n");
		return;
	}
	
	printf("\n=============================================\n");
	printf("   HORARIO DE %s\n", docente->nombre);
	printf("=============================================\n");
	printf(">> Area            : %s\n", docente->area);
	printf(">> Horario general : %s\n", docente->horario);
	printf("---------------------------------------------\n");
	printf("   AGENDA (tutorias activas/reprogramadas)\n");
	printf("---------------------------------------------\n");
	printf("%-5s %-6s %-12s %-8s %-30s %-12s\n",
		   "ID", "Est", "Fecha", "Hora", "Asunto", "Estado");
	printf("%-5s %-6s %-12s %-8s %-30s %-12s\n",
		   "-----", "------", "------------", "--------",
		   "------------------------------", "------------");
	
	int encontrado = 0;
	Tutoria *temp = tutorias;
	while (temp != NULL) {
		if (temp->id_docente == docente->id &&
			(strcmp(temp->estado, "activa") == 0 ||
			 strcmp(temp->estado, "reprogramada") == 0)) {
			printf("%-5d %-6d %-12s %-8s %-30s %-12s\n",
				   temp->id, temp->id_estudiante,
				   temp->fecha, temp->hora, temp->tema, temp->estado);
			encontrado = 1;
		}
			temp = temp->siguiente;
	}
	if (!encontrado) printf(">> El docente no tiene tutorias agendadas actualmente.\n");
	printf("---------------------------------------------\n");
}

/* -- Listar tutorias activas ---------------------- */
void listarTutoriasActivas(Tutoria *lista) {
	int encontrado = 0;
	printf("\n%-5s %-6s %-6s %-12s %-8s %-30s %-12s\n",
		   "ID", "Est", "Doc", "Fecha", "Hora", "Tema", "Estado");
	printf("%-5s %-6s %-6s %-12s %-8s %-30s %-12s\n",
		   "-----", "------", "------", "------------",
		   "--------", "------------------------------", "------------");
	
	while (lista != NULL) {
		if (strcmp(lista->estado, "activa") == 0) {
			printf("%-5d %-6d %-6d %-12s %-8s %-30s %-12s\n",
				   lista->id, lista->id_estudiante, lista->id_docente,
				   lista->fecha, lista->hora, lista->tema, lista->estado);
			encontrado = 1;
		}
		lista = lista->siguiente;
	}
	if (!encontrado) printf(">> No hay tutorias activas.\n");
}

/* -- Consultar por estudiante --------------------- */
void consultarPorEstudiante(Tutoria *lista, Estudiante *estudiantes) {
	char cedula[20];
	printf("Cedula del estudiante: ");
	fgets(cedula, 20, stdin);
	cedula[strcspn(cedula, "\n")] = '\0';
	
	Estudiante *e = buscarEstudiantePorCedula(estudiantes, cedula);
	if (e == NULL) {
		printf(">> Estudiante no encontrado.\n");
		return;
	}
	
	int encontrado = 0;
	printf("\n%-5s %-6s %-12s %-8s %-30s %-12s\n",
		   "ID", "Doc", "Fecha", "Hora", "Tema", "Estado");
	printf("%-5s %-6s %-12s %-8s %-30s %-12s\n",
		   "-----", "------", "------------", "--------",
		   "------------------------------", "------------");
	
	while (lista != NULL) {
		if (lista->id_estudiante == e->id) {
			printf("%-5d %-6d %-12s %-8s %-30s %-12s\n",
				   lista->id, lista->id_docente,
				   lista->fecha, lista->hora, lista->tema, lista->estado);
			encontrado = 1;
		}
		lista = lista->siguiente;
	}
	if (!encontrado) printf(">> No hay tutorias para este estudiante.\n");
}

/* -- Consultar por docente ------------------------ */
void consultarPorDocente(Tutoria *lista, Docente *docentes) {
	char codigo[20];
	printf("Codigo del docente: ");
	fgets(codigo, 20, stdin);
	codigo[strcspn(codigo, "\n")] = '\0';
	
	Docente *d = buscarDocentePorCodigo(docentes, codigo);
	if (d == NULL) {
		printf(">> Docente no encontrado.\n");
		return;
	}
	
	int encontrado = 0;
	printf("\n%-5s %-6s %-12s %-8s %-30s %-12s\n",
		   "ID", "Est", "Fecha", "Hora", "Tema", "Estado");
	printf("%-5s %-6s %-12s %-8s %-30s %-12s\n",
		   "-----", "------", "------------", "--------",
		   "------------------------------", "------------");
	
	while (lista != NULL) {
		if (lista->id_docente == d->id) {
			printf("%-5d %-6d %-12s %-8s %-30s %-12s\n",
				   lista->id, lista->id_estudiante,
				   lista->fecha, lista->hora, lista->tema, lista->estado);
			encontrado = 1;
		}
		lista = lista->siguiente;
	}
	if (!encontrado) printf(">> No hay tutorias para este docente.\n");
}

/* -- Reporte: Tutorias por docente ---------------- */
void reporteTutoriasPorDocente(Tutoria *lista, Docente *docentes) {
	printf("\n=============================================\n");
	printf("   TUTORIAS POR DOCENTE\n");
	printf("=============================================\n");
	
	while (docentes != NULL) {
		int count = 0;
		Tutoria *temp = lista;
		while (temp != NULL) {
			if (temp->id_docente == docentes->id) count++;
			temp = temp->siguiente;
		}
		printf("%s: %d tutorias\n", docentes->nombre, count);
		docentes = docentes->siguiente;
	}
}

/* -- Reporte: Estudiantes con mas de una tutoria -- */
void reporteEstudiantesMultiples(Tutoria *lista) {
	printf("\n=============================================\n");
	printf("   ESTUDIANTES CON MULTIPLES TUTORIAS\n");
	printf("=============================================\n");
	
	// Contar por estudiante
	int ids[1000], counts[1000], total = 0;
	
	while (lista != NULL) {
		int encontrado = 0;
		for (int i = 0; i < total; i++) {
			if (ids[i] == lista->id_estudiante) {
				counts[i]++;
				encontrado = 1;
				break;
			}
		}
		if (!encontrado) {
			ids[total] = lista->id_estudiante;
			counts[total] = 1;
			total++;
		}
		lista = lista->siguiente;
	}
	
	int hay = 0;
	for (int i = 0; i < total; i++) {
		if (counts[i] > 1) {
			printf("Estudiante ID %d: %d tutorias\n", ids[i], counts[i]);
			hay = 1;
		}
	}
	if (!hay) printf(">> No hay estudiantes con multiples tutorias.\n");
}

/* -- Reporte: Docentes con mas tutorias ------------ */
void reporteDocentesMasTutorias(Tutoria *lista) {
	printf("\n=============================================\n");
	printf("   DOCENTES CON MAS TUTORIAS\n");
	printf("=============================================\n");
	
	int ids[1000], counts[1000], total = 0, max = 0;
	
	while (lista != NULL) {
		int encontrado = 0;
		for (int i = 0; i < total; i++) {
			if (ids[i] == lista->id_docente) {
				counts[i]++;
				if (counts[i] > max) max = counts[i];
				encontrado = 1;
				break;
			}
		}
		if (!encontrado) {
			ids[total] = lista->id_docente;
			counts[total] = 1;
			if (counts[total] > max) max = counts[total];
			total++;
		}
		lista = lista->siguiente;
	}
	
	for (int i = 0; i < total; i++) {
		if (counts[i] == max && max > 0) {
			printf("Docente ID %d: %d tutorias (maximo)\n", ids[i], counts[i]);
		}
	}
}

/* -- Liberar tutorias ------------------------------ */
void liberarTutorias(Tutoria *lista) {
	while (lista != NULL) {
		Tutoria *aux = lista->siguiente;
		free(lista);
		lista = aux;
	}
}
