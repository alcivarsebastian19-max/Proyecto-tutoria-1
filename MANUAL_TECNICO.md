                                  Escuela Politécnica Nacional

                       Proyecto: Sistema de gestión de tutorías académicas

                    Integrantes: Sebastián Alcivar - Michael Zavala

                                      Programación I

                         Docente: Nelson Iván Herrera Herrera

                                 Quito, 12 de julio de 2026

                                        Versión: 1.0

Introducción

Este manual técnico describe la estructura interna, arquitectura y funcionamiento del Sistema de Gestión de Tutorías Académicas, desarrollado como proyecto final de la asignatura Programación I en la Escuela Politécnica Nacional. Con el objetivo de servir de referencia para desarrolladoras que necesiten comprender, mantener o extender el sistema.
Descripción del sistema
Objetivo del software: Automatizar el proceso de registro, asignación y seguimiento de tutorías académicas entre estudiantes y docentes en una institución educativa.
Problema que resuelve: En las instituciones educativas se gestiona las tutorías de manera manual, esto hace que se pierda información, conflictos de horario y falta de seguimiento. Este sistema centraliza esa gestión con la persistencia de datos en archivos de texto.

Funcionalidades principales:
•	Autenticación de usuarios por su rol.
•	Registro de estudiantes y docentes con validaciones,
•	Asignación de tutorías con validación de disponibilidad.
•	Cancelación y reprogramación de tutorías.
•	Consultas por estudiante y por docente.
•	Generación de reportes.
•	Persistencia de datos en archivos .txt

Tecnologías utilizadas
•	Lenguaje de programación: C (estándar C99)
•	Entorno de desarrollo (IDE): Zinjai v.20191006
•	Sistema operativo: Windows 11 
•	Herramientas o librerías empleadas: stdio.h, stdlib.h, string.h, ctype.h, conio.h (Windows)/termios.h (Linux/Mac) 

Arquitectura y Estructura

<img width="329" height="176" alt="Pe" src="https://github.com/user-attachments/assets/45992a59-9aa7-4513-a5a8-4d311aebf75c" />

Descripción de archivos

main.c - Punto de entrada del programa. Contiene el bucle principal del sistema, la carga inicial d datos y los menús de cada rol. Controla si el usuario elige salir del programa o regresar al login.


auth.c / auth.h – Maneja la autenticación. Contiene la función “login()” que busca credenciales en los tres archivos, “inicializarSistema()” crea el administrador principal, lo hace por defecto si este no existe, “registrarEstudiante()” y “registrarDocente()”accesibles desde el login, “resitrarAdmin()” exclusivo para el administrador principal y “leerContrasenaOculta()” que oculta la contraseña con asteriscos usando “_getch()” en Windows.


estudiantes.h / estudiantes.c – Enlaza a los estudiantes en una lista. Implementa carga y guardado en data/estudiantes.txt con separador “|”, busca por cédula o por ID y listado en tabla formateada.


docentes.h / docentes.c – Lista enlazada de docentes. Misma estructura que estudiantes. Incluye “listarDocentesSinCodigo()” para mostrar a los estudiantes al solicitar una tutoría.


tutorias.h / tutorias.c – Lista enlazada de tutorías. Contiene la lógica de asignación con validación de disponibilidad del docente, cancelación y reprogramación.


Estructura de archivos:


admins.txt:       id|usuario|contrasena|rol


estudiantes.txt:  id|cedula|nombre|carrera|correo|usuario|contrasena


docentes.txt:     id|codigo|nombre|area|horario|usuario|contrasena


tutorias.txt:     id|id_estudiante|id_docente|fecha|hora|tema|estado



Funciones principales:


Función	Archivo	Descripción


inicializarSistema() |	auth.c	| Crea “admins.txt” con el administrador superior si no existe


login()	| auth.c	| Autentica usuario y retorna SesionActiva con rol e ID


leerContrasenaOculta()	| auth.c	| Lee contraseña y muestra asteriscos


registrarEstudiante() |	auth.c	| Registra estudiante con validaciones desde el login


registrarDocente()	| auth.c	| Registra docente con validaciones desde el login


registrarAdmin()	| auth.c	| Crea un administrador, esto solo lo hace el administrador superior


cargarEstudiantes()	| estudiantes.c	| Carga la lista desde el archivo.


buscarEstudiantePorCedula()	| estudiantes.c	| Búsqueda lineal por cédula.


buscarDocentePorCodigo()	|  docentes.c	| Búsqueda lineal por código.


validarDisponibilidadDocente()	| tutorias.c	| Verifica que no haya conflictos entre horarios.


asignarTutoria()	| tutorias.c	| Crea y guarda una nueva tutoría con validaciones.


cancelarTutoriaPropia()	| tutorias.c	| Cancela tutoría verificando que pertenezca al usuario


reprogramarTutoriaPropia()	| tutorias.c	| Reprograma verificando pertenencia y disponibilidad.


mostrarHoriarioDocente()	| tutorias.c	| Muestra agenda de docente.


reporteTutoriasPorDocente()	| tutorias.c	| Conteo de tutorías por cada docente.


reporteEstudiantesMultiples()	| tutorias.c | Estudiantes con más de una tutoría.


reporteDocentesMasTutorias()	| tutorias.c | 	Docentes con el mayor número de tutorías.


Instalación y ejecución


•	Requisitos mínimos.


Sistema operativo: Windows 10/11 (Linux/Mac con GCC)


•	Pasos para ejecutar la aplicación. 


Se puede ejecutar directamente el archivo sistema.exe haciendo doble clic. La carpeta data/ debe existir antes de ejecutar; si no existe el programa no podrá guardar datos.


Validaciones implementadas


Cédula: 10 dígitos numéricos, no duplicada


Nombre, carrera, área, horario y asunto: no pueden estar vacíos.


Correo: debe contener el carácter “@”.


Código de docente: solo dígitos, no duplicado


Disponibilidad del docente: no puede tener dos tutorías activas en la misma fecha y hora.


Pertenencia de tutoría: un docente o estudiante solo puede cancelar o reprogramar sus propias tutorías


Estado de tutoría: solo se pueden cancelar o reprogramar tutorías activas


Login: máximo 3 intentos fallidos con el mismo usuario; si el usuario no existe, ofrece registro


Contraseña: se ingresa de forma oculta con asteriscos


Mensajes de error importantes


•	>> Error: la cedula debe tener exactamente 10 digitos numericos, y no debe estar ya registrada.


•	>> Error: correo invalido (debe contener @).


•	>> Error: el codigo debe contener solo numeros.


•	>> Error: el docente ya tiene una tutoria en esa fecha y hora.


•	>> Error: esa tutoria no te pertenece.


•	>> Solo se pueden cancelar tutorias activas.


•	>> Usuario o contrasena incorrectos.


•	>> Acceso bloqueado por demasiados intentos.


•	>> Error: no se pudo guardar.


Soluciones a problemas frecuentes:


El programa no guarda datos: verificar que la carpeta  data/ exista en el mismo directorio que el ejecutable.


No aparece la opción 14 en el menú admin: esa opción es exclusiva del administrador principal. Un admin regular no la ve.


La contraseña no aparece al escribir: es intencional, el sistema la oculta con asteriscos por seguridad.


Error al compilar en Linux: reemplazar conio.h no es necesario; el código ya tiene un bloque alternativo con termios.h 
para Linux/Mac mediante #ifdef _WIN32.


El programa abre y cierra inmediatamente: Verificar que la carpeta data/ exista.


Mantenimiento y Mejoras Futuras


•	Cómo agregar nuevas funcionalidades. 


Para crear nuevos módulos:


Crear cabecera con definición del struct y prototipos.


Crear código con implementación de las funciones.


Incluir la cabecera en el main


Dar opciones en el menú de administrador


Agregar el archivo .c en la compilación.


Para agregar en una estructura existente:


Agregar en struct dentro del .h


Actualizar las funciones de carga y guardado en él .c


Actualizar la función de registro para pedirle el dato al usuario


Agregar opciones correspondientes 


•	Recomendaciones para futuras versiones.


 Implementar cifrado básico de contraseñas en los archivos .txt para mayor seguridad.

 
Migrar el almacenamiento de .txt a una base de datos como SQLite para mayor robustez


Agregar un módulo de recuperación de contraseña por correo


Implementar un log de actividad que registre quién hizo qué y cuándo


Agregar la opción de exportar reportes directamente a archivos .txt en la carpeta reportes/


Separar el registro de estudiantes y docentes en un flujo independiente del login para mayor claridad

