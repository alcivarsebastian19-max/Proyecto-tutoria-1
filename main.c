#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "auth.h"

#include "estudiantes.h"

#include "docentes.h"

#include "tutorias.h"



// Prototipos

// Devuelven 0 si el usuario eligio salir del programa por completo,

// o 1 si eligio regresar al menu principal (login) para otra sesion.

int menuAdmin(Estudiante **estudiantes, Docente **docentes, Tutoria **tutorias, SesionActiva sesion);

int menuDocente(Tutoria **tutorias, SesionActiva sesion);

int menuEstudiante(Tutoria **tutorias, SesionActiva sesion);



int main() {
	
	inicializarSistema();
	
	
	
	Tutoria *tutorias = cargarTutorias();
	
	int continuarPrograma = 1;
	
	
	
	while (continuarPrograma) {
		
		Estudiante *estudiantes = cargarEstudiantes();
		
		Docente *docentes = cargarDocentes();
		
		
		
		SesionActiva sesion = login();
		
		
		
		if (sesion.rol == ROL_NINGUNO) {
			
			liberarEstudiantes(estudiantes);
			
			liberarDocentes(docentes);
			
			continuarPrograma = 0;
			
			break;
			
		}
		
		
		
		int resultado = 1; // por defecto, volver al menu principal
		
		
		
		switch (sesion.rol) {
			
		case ROL_SUPERADMIN:
			
		case ROL_ADMIN:
			
			resultado = menuAdmin(&estudiantes, &docentes, &tutorias, sesion);
			
			break;
			
		case ROL_DOCENTE:
			
			resultado = menuDocente(&tutorias, sesion);
			
			break;
			
		case ROL_ESTUDIANTE:
			
			resultado = menuEstudiante(&tutorias, sesion);
			
			break;
			
		default:
			
			printf(">> Rol desconocido.\n");
			
		}
		
		
		
		guardarTutorias(tutorias);
		
		
		
		liberarEstudiantes(estudiantes);
		
		liberarDocentes(docentes);
		
		
		
		if (resultado == 0) {
			
			continuarPrograma = 0;
			
		}
		
	}
	
	
	
	liberarTutorias(tutorias);
	
	
	
	limpiarPantalla();
	
	printf("\n=============================================\n");
	
	printf("   DATOS GUARDADOS.\n");
	
	printf("=============================================\n");
	
	printf("\nPrograma finalizado\n");
	
	printf("\nGracias\n");
	
	return 0;
	
}



int menuAdmin(Estudiante **estudiantes, Docente **docentes, Tutoria **tutorias, SesionActiva sesion) {
	
	int opcion;
	
	int salirPrograma = 0;
	
	do {
		
		limpiarPantalla();
		
		printf("\n+-----------------------------------------+\n");
		
		printf("|         MENU ADMINISTRADOR              |\n");
		
		if (sesion.rol == ROL_SUPERADMIN)
			
			printf("|       [ ADMINISTRADOR PRINCIPAL ]                  |\n");
		
		printf("+-----------------------------------------+\n");
		
		printf("|  1. Listar estudiantes                  |\n");
		
		printf("|  2. Buscar estudiante por cedula        |\n");
		
		printf("|  3. Listar docentes                     |\n");
		
		printf("|  4. Buscar docente por codigo           |\n");
		
		printf("|  5. Asignar tutoria                     |\n");
		
		printf("|  6. Cancelar tutoria                    |\n");
		
		printf("|  7. Reprogramar tutoria                 |\n");
		
		printf("|  8. Listar tutorias activas             |\n");
		
		printf("|  9. Tutorias por estudiante             |\n");
		
		printf("| 10. Tutorias por docente                |\n");
		
		printf("| 11. Reporte: Tutorias por docente       |\n");
		
		printf("| 12. Reporte: Estudiantes con >1 tutoria |\n");
		
		printf("| 13. Reporte: Docentes con mas tutorias  |\n");
		
		if (sesion.rol == ROL_SUPERADMIN)
			
			printf("| 14. Registrar nuevo admin              |\n");
		
		printf("| 15. Regresar al menu principal          |\n");
		
		printf("|  0. Salir del programa                  |\n");
		
		printf("+-----------------------------------------+\n");
		
		printf("Opcion: ");
		
		scanf("%d", &opcion);
		
		while (getchar() != '\n');
		
		
		
		switch (opcion) {
			
		case 1:
			
			limpiarPantalla();
			
			listarEstudiantes(*estudiantes);
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 2:
			
			limpiarPantalla();
			
			buscarEstudiante(*estudiantes);
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 3:
			
			limpiarPantalla();
			
			listarDocentes(*docentes);
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 4:
			
			limpiarPantalla();
			
			buscarDocente(*docentes);
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 5:
			
			limpiarPantalla();
			
			asignarTutoria(tutorias, *estudiantes, *docentes);
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 6:
			
			limpiarPantalla();
			
			cancelarTutoria(*tutorias);
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 7:
			
			limpiarPantalla();
			
			reprogramarTutoria(*tutorias);
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 8:
			
			limpiarPantalla();
			
			listarTutoriasActivas(*tutorias);
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 9:
			
			limpiarPantalla();
			
			consultarPorEstudiante(*tutorias, *estudiantes);
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 10:
			
			limpiarPantalla();
			
			consultarPorDocente(*tutorias, *docentes);
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 11:
			
			limpiarPantalla();
			
			reporteTutoriasPorDocente(*tutorias, *docentes);
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 12:
			
			limpiarPantalla();
			
			reporteEstudiantesMultiples(*tutorias);
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 13:
			
			limpiarPantalla();
			
			reporteDocentesMasTutorias(*tutorias);
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 14:
			
			if (sesion.rol == ROL_SUPERADMIN) {
				
				limpiarPantalla();
				
				registrarAdmin();
				
			}
			
			break;
			
		case 15:
			
			limpiarPantalla();
			
			printf(">> Regresando al menu principal...\n");
			
			break;
			
		case 0:
			
			limpiarPantalla();
			
			printf(">> Cerrando sesion y saliendo del programa...\n");
			
			salirPrograma = 1;
			
			break;
			
		default:
			
			limpiarPantalla();
			
			printf(">> Opcion invalida.\n");
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
		}
		
	} while (opcion != 0 && opcion != 15);
	
	
	
	return salirPrograma ? 0 : 1;
	
}



int menuDocente(Tutoria **tutorias, SesionActiva sesion) {
	
	int opcion;
	
	int salirPrograma = 0;
	
	do {
		
		limpiarPantalla();
		
		printf("\n+-----------------------------------+\n");
		
		printf("|       MENU DOCENTE                 |\n");
		
		printf("+-----------------------------------+\n");
		
		printf("|  1. Ver mis tutorias (y su estado)|\n");
		
		printf("|  2. Ver mi horario                |\n");
		
		printf("|  3. Cancelar una tutoria mia      |\n");
		
		printf("|  4. Reprogramar una tutoria mia   |\n");
		
		printf("|  5. Regresar al menu principal    |\n");
		
		printf("|  0. Salir del programa            |\n");
		
		printf("+-----------------------------------+\n");
		
		printf("Opcion: ");
		
		scanf("%d", &opcion);
		
		while (getchar() != '\n');
		
		
		
		switch (opcion) {
			
		case 1:
			
			limpiarPantalla();
			
			{
				
				int encontrado = 0;
				
				Tutoria *temp = *tutorias;
				
				printf("\n=============================================\n");
				
				printf("   MIS TUTORIAS ASIGNADAS\n");
				
				printf("=============================================\n");
				
				printf("%-5s %-6s %-12s %-8s %-30s %-12s\n",
					   
					   "ID", "Est", "Fecha", "Hora", "Tema", "Estado");
				
				printf("%-5s %-6s %-12s %-8s %-30s %-12s\n",
					   
					   "-----", "------", "------------", "--------",
					   
					   "------------------------------", "------------");
				
				while (temp != NULL) {
					
					if (temp->id_docente == sesion.id) {
						
						printf("%-5d %-6d %-12s %-8s %-30s %-12s\n",
							   
							   temp->id, temp->id_estudiante,
							   
							   temp->fecha, temp->hora, temp->tema, temp->estado);
						
						encontrado = 1;
						
					}
					
					temp = temp->siguiente;
					
				}
				
				if (!encontrado) printf(">> No tienes tutorias asignadas.\n");
				
			}
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 2:
			
			limpiarPantalla();
			
			{
				
				Docente *listaDocentes = cargarDocentes();
				
				Docente *d = buscarDocentePorId(listaDocentes, sesion.id);
				
				mostrarHorarioDocente(d, *tutorias);
				
				liberarDocentes(listaDocentes);
				
			}
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 3:
			
			limpiarPantalla();
			
			{
				
				int id;
				
				printf("\n=============================================\n");
				
				printf("   CANCELAR TUTORIA\n");
				
				printf("=============================================\n");
				
				printf("ID de la tutoria a cancelar: ");
				
				scanf("%d", &id);
				
				while (getchar() != '\n');
				
				cancelarTutoriaPropia(*tutorias, id, sesion.id, 1);
				
			}
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 4:
			
			limpiarPantalla();
			
			{
				
				int id;
				
				printf("\n=============================================\n");
				
				printf("   REPROGRAMAR TUTORIA\n");
				
				printf("=============================================\n");
				
				printf("ID de la tutoria a reprogramar: ");
				
				scanf("%d", &id);
				
				while (getchar() != '\n');
				
				reprogramarTutoriaPropia(*tutorias, id, sesion.id, 1);
				
			}
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 5:
			
			limpiarPantalla();
			
			printf(">> Regresando al menu principal...\n");
			
			break;
			
		case 0:
			
			limpiarPantalla();
			
			printf(">> Cerrando sesion y saliendo del programa...\n");
			
			salirPrograma = 1;
			
			break;
			
		default:
			
			limpiarPantalla();
			
			printf(">> Opcion invalida.\n");
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
		}
		
	} while (opcion != 0 && opcion != 5);
	
	
	
	return salirPrograma ? 0 : 1;
	
}



int menuEstudiante(Tutoria **tutorias, SesionActiva sesion) {
	
	int opcion;
	
	int salirPrograma = 0;
	
	do {
		
		limpiarPantalla();
		
		printf("\n+-----------------------------------+\n");
		
		printf("|       MENU ESTUDIANTE              |\n");
		
		printf("+-----------------------------------+\n");
		
		printf("|  1. Ver mis tutorias (y su estado)|\n");
		
		printf("|  2. Solicitar tutoria             |\n");
		
		printf("|  3. Cancelar una tutoria mia      |\n");
		
		printf("|  4. Reprogramar una tutoria mia   |\n");
		
		printf("|  5. Regresar al menu principal    |\n");
		
		printf("|  0. Salir del programa            |\n");
		
		printf("+-----------------------------------+\n");
		
		printf("Opcion: ");
		
		scanf("%d", &opcion);
		
		while (getchar() != '\n');
		
		
		
		switch (opcion) {
			
		case 1:
			
			limpiarPantalla();
			
			{
				
				int encontrado = 0;
				
				Tutoria *temp = *tutorias;
				
				printf("\n=============================================\n");
				
				printf("   MIS TUTORIAS\n");
				
				printf("=============================================\n");
				
				printf("%-5s %-6s %-12s %-8s %-30s %-12s\n",
					   
					   "ID", "Doc", "Fecha", "Hora", "Tema", "Estado");
				
				printf("%-5s %-6s %-12s %-8s %-30s %-12s\n",
					   
					   "-----", "------", "------------", "--------",
					   
					   "------------------------------", "------------");
				
				while (temp != NULL) {
					
					if (temp->id_estudiante == sesion.id) {
						
						printf("%-5d %-6d %-12s %-8s %-30s %-12s\n",
							   
							   temp->id, temp->id_docente,
							   
							   temp->fecha, temp->hora, temp->tema, temp->estado);
						
						encontrado = 1;
						
					}
					
					temp = temp->siguiente;
					
				}
				
				if (!encontrado) printf(">> No tienes tutorias.\n");
				
			}
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 2:
			
			limpiarPantalla();
			
			{
				
				Docente *docentes = cargarDocentes();
				
				printf("\n=============================================\n");
				
				printf("   SOLICITAR TUTORIA\n");
				
				printf("=============================================\n");
				
				listarDocentesSinCodigo(docentes);
				
				
				
				Tutoria nueva;
				
				nueva.id = 0;
				
				nueva.id_estudiante = sesion.id;
				
				
				
				Tutoria *temp = *tutorias;
				
				while (temp != NULL) {
					
					if (temp->id > nueva.id) nueva.id = temp->id;
					
					temp = temp->siguiente;
					
				}
				
				nueva.id++;
				
				
				
				Docente *docenteElegido = NULL;
				
				do {
					
					int idDocente;
					
					printf("\nID del docente: ");
					
					scanf("%d", &idDocente);
					
					while (getchar() != '\n');
					
					
					
					Docente *d = buscarDocentePorId(docentes, idDocente);
					
					if (d == NULL) {
						
						printf(">> Error: docente no registrado.\n");
						
						nueva.id_docente = 0;
						
					} else {
						
						nueva.id_docente = d->id;
						
						docenteElegido = d;
						
					}
					
				} while (nueva.id_docente == 0);
				
				
				
				mostrarHorarioDocente(docenteElegido, *tutorias);
				
				
				
				do {
					
					printf("Fecha (DD/MM/AAAA): ");
					
					fgets(nueva.fecha, 20, stdin);
					
					nueva.fecha[strcspn(nueva.fecha, "\n")] = '\0';
					
					if (strlen(nueva.fecha) == 0) {
						
						printf(">> Error: fecha no puede estar vacia.\n");
						
					}
					
				} while (strlen(nueva.fecha) == 0);
				
				
				
				do {
					
					printf("Hora (HH:MM): ");
					
					fgets(nueva.hora, 10, stdin);
					
					nueva.hora[strcspn(nueva.hora, "\n")] = '\0';
					
					if (strlen(nueva.hora) == 0) {
						
						printf(">> Error: hora no puede estar vacia.\n");
						
					}
					
				} while (strlen(nueva.hora) == 0);
				
				
				
				if (!validarDisponibilidadDocente(*tutorias, nueva.id_docente, nueva.fecha, nueva.hora)) {
					
					printf(">> Error: el docente no esta disponible.\n");
					
					liberarDocentes(docentes);
					
					printf("\n>> Presiona Enter para continuar...");
					
					getchar();
					
					break;
					
				}
				
				
				
				do {
					
					printf("Asunto de la tutoria: ");
					
					fgets(nueva.tema, 100, stdin);
					
					nueva.tema[strcspn(nueva.tema, "\n")] = '\0';
					
					if (strlen(nueva.tema) == 0) {
						
						printf(">> Error: el asunto no puede estar vacio.\n");
						
					}
					
				} while (strlen(nueva.tema) == 0);
				
				
				
				strcpy(nueva.estado, "activa");
				
				
				
				Tutoria *nodo = (Tutoria*)malloc(sizeof(Tutoria));
				
				*nodo = nueva;
				
				nodo->siguiente = NULL;
				
				
				
				if (*tutorias == NULL) {
					
					*tutorias = nodo;
					
				} else {
					
					temp = *tutorias;
					
					while (temp->siguiente != NULL) temp = temp->siguiente;
					
					temp->siguiente = nodo;
					
				}
				
				
				
				guardarTutorias(*tutorias);
				
				printf("\n=============================================\n");
				
				printf("   TUTORIA SOLICITADA\n");
				
				printf("=============================================\n");
				
				printf(">> Tutoria #%d solicitada.\n", nueva.id);
				
				liberarDocentes(docentes);
				
			}
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 3:
			
			limpiarPantalla();
			
			{
				
				int id;
				
				printf("\n=============================================\n");
				
				printf("   CANCELAR TUTORIA\n");
				
				printf("=============================================\n");
				
				printf("ID de la tutoria a cancelar: ");
				
				scanf("%d", &id);
				
				while (getchar() != '\n');
				
				cancelarTutoriaPropia(*tutorias, id, sesion.id, 0);
				
			}
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 4:
			
			limpiarPantalla();
			
			{
				
				int id;
				
				printf("\n=============================================\n");
				
				printf("   REPROGRAMAR TUTORIA\n");
				
				printf("=============================================\n");
				
				printf("ID de la tutoria a reprogramar: ");
				
				scanf("%d", &id);
				
				while (getchar() != '\n');
				
				reprogramarTutoriaPropia(*tutorias, id, sesion.id, 0);
				
			}
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
			break;
			
		case 5:
			
			limpiarPantalla();
			
			printf(">> Regresando al menu principal...\n");
			
			break;
			
		case 0:
			
			limpiarPantalla();
			
			printf(">> Cerrando sesion y saliendo del programa...\n");
			
			salirPrograma = 1;
			
			break;
			
		default:
			
			limpiarPantalla();
			
			printf(">> Opcion invalida.\n");
			
			printf("\n>> Presiona Enter para continuar...");
			
			getchar();
			
		}
		
	} while (opcion != 0 && opcion != 5);
	
	
	
	return salirPrograma ? 0 : 1;
	
}
