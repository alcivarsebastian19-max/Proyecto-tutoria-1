                                   Escuela Politécnica Nacional

                     Proyecto: Sistema de gestión de tutorías académicas

                                         Versión: 1.0

                        Integrantes: Sebastián Alcivar - Michael Zavala

                                         Programación I

                                   Quito, 12 de julio de 2026

Introducción
Este Sistema de Gestión de Tutorías Académicas es una aplicación de consola desarrollada en lenguaje C, diseñada para la Escuela Politécnica Nacional. Tiene como objetivo centralizar y automatizar el proceso de registro, asignación y seguimiento de tutorías entre estudiantes y docentes.
Este programa esta dirigido a tres tipos de usuarios: administradores, docentes y estudiantes. Cada uno debe de acceder con sus credenciales y dispone de un menú adaptado a las necesidades del sistema.
Requisitos para usar el sistema
Sistema operativo 
•	Windows 10/11 (Recomendado)
•	Linux o macOS (compatible)
Requisitos mínimos 
•	Compilador GCC instalado (versión 10 o superior)
•	Terminal o símbolo del sistema
•	Carpetas data/ y reportes/ dentro del directorio del proyecto
Para ejecutar el programa, cree las carpetas “data”  “reportes” posteriormente ejecute el archivo “Proyecto tutoria v.1” haciendo doble clic.
Descripción de las funcionalidades
•	Incio de la aplicación
Al ejecutar el programa por primera vez, el sistema verificará el usuario administrador. Si no existe, mostrara el siguiente mensaje
SISTEMA INICIALIZADO
>> Presiona Enter para continuar...
Esto indica que se creó automáticamente las configuraciones iniciales necesarias, El usuario debe presionar Enter para continuar el inicio de sesión.
En ejecuciones posteriores este mensaje no aparecerá y el sistema va directamente al login.
•	Inicio de sesión
El sistema solicitará usuario y contraseña. Se tienen 3 intentos fallidos hasta que el acceso quede bloqueado y regrese al menú principal. Si el usuario no existe ofrece registrarse.
Tipos de usuario:
•	Administrador: Acceso total al sistema.
•	Docente: puede ver tutorías asignadas y las puede gestionar.
•	Estudiante: puede solicitar tutorías y modificar su estado.

•	Registro de nuevo usuario

Si el usuario no existe, el sistema ofrece registrarse como:
•	Estudiante
•	Docente

Datos requeridos de estudiante: 
• Cedula (exactamente 10 dígitos numéricos, no puede estar ya registrada)
• Nombre completo (no puede estar vacío)
• Carrera (no puede estar vacía)
• Correo electrónico (debe contener @)
• Usuario para login
•Contraseña (oculta con asteriscos)
Datos requeridos de docente
• Código de docente (solo números, no puede repetirse)
• Nombre completo (no puede estar vacío)
• Área de conocimiento (no puede estar vacía)
• Horario disponible, ej: Lun-Vie 8:00-12:00 (no puede estar vacío)
• Usuario para login
• Contraseña (se escribe oculta con asteriscos)

•	Menu de administrador/administrador principal
 <img width="530" height="549" alt="Imagen7" src="https://github.com/user-attachments/assets/52d8b391-9ade-4369-8c5b-d48fc715e149" />

La opción 14 solo es visible y funcional para el Administrador principal

•	Asignar tutoría (En administrador – opción 5)
El administrador ingresa los siguientes datos para asignar tutoría
•	Cedula del estudiante (debe estar registrado)
•	Código del docente (debe estar registrado)
•	Fecha en formato DD/MM/AAAA
•	Hora en formato HH:MM
•	Asunto de la tutoría (no puede estar vacío)
El sistema valida que el docente no tena tutoría activa con los mismos datos antes de guardar.

•	Cancelar y reprogramar tutorías (En administrador – Opciones 6 y 7)
El administrador puede cancelar o reprogramar cualquier tutoría activa ingresando su ID. Solo se pueden cancelar o reprogramar tutorías en estado activa. Al reprogramar, el sistema valida nuevamente la disponibilidad del docente.

•	Consultas y reportes (En administrador – Opciones 8 - 13)
               • Opción 8: lista todas las tutorías con estado activa.
• Opción 9: muestra todas las tutorías de un estudiante buscado por cedula.
• Opción 10: muestra todas las tutorías de un docente buscado por código.
• Opción 11: reporte con el número de tutorías por cada docente.
• Opción 12: reporte de estudiantes que tienen más de una tutoría.
• Opción 13: reporte de los docentes con mayor número de tutorías. asignadas

•	Menú Docente
 <img width="544" height="325" alt="Imagen5" src="https://github.com/user-attachments/assets/b1a4a7ea-480e-4875-bb2a-2087b119bcdf" />

• Opción 1: muestra todas las tutorías asignadas al docente con su estado.
• Opción 2: muestra el horario general del docente y su agenda de tutorías activas.
• Opción 3: cancela una tutoría propia ingresando su ID (solo tutorías activas).
• Opción 4: reprograma una tutoría propia con nueva fecha y hora.
• Opción 5: cierra la sesión y regresa al login para que entre otro usuario.
• Opción 0: cierra el programa completamente.

•	Menú Estudiante
 <img width="434" height="269" alt="Imagen4" src="https://github.com/user-attachments/assets/6fa4253e-2524-408f-ba4a-e620dd40f972" />

• Opción 1: muestra todas las tutorías del estudiante con estado y docente asignado.
• Opción 2: solicita una nueva tutoría eligiendo docente, fecha, hora y asunto.
• Opción 3: cancela una tutoría propia (solo tutorías activas que le pertenezcan).
• Opción 4: reprograma una tutoría propia con nueva fecha y hora.
• Opción 5: cierra la sesión y regresa al login.
• Opción 0: cierra el programa completamente.
Al solicitar una tutoria, el sistema muestra los docentes disponibles y permite al estudiante ver el horario y agenda del docente elegido antes de confirmar la fecha y hora.

•	Salida del sistema
Existen dos formas de salir del sistema:
•	Opción 15 (administrador)/Opción 5 (docente y estudiante): cierra la sesión actual y regresa al login para que otro usuario pueda ingresar.
•	Opción 0 (todos los menús): guarda los datos y cierra el programa completamente.
Al cerrar el programa, el sistema muestra:
=============================================
   DATOS GUARDADOS.
=============================================
Programa finalizado
Gracias

•	Mensajes y posibles errores
Mensaje del sistema	Acciones de usuario
SISTEMA INICIALIZADO / Presiona Enter para continuar	Se muestra en el primer uso, presionar Enter para ir al login.
Cédula debe tener exactamente 10 dígitos numéricos, y no debe estar ya registrada.	Verificar que la cédula tenga 10 número y que no esté duplicada.

El nombre no puede estar vacío.	Ingresar nombre completo.

La carrera no puede estar vacía.	Ingresar carrera del estudiante.
Correo inválido (debe contener @)	Ingresar el correo en un formato válido.
El código debe contener solo números.	Ingresar solo dígitos en el código docente.
Código ya registrado.	Ingresar un código de docente diferente.
El área no puede estar vacía.	Completar el área de conocimiento.

El horario no puede estar vacío.	Ingresar el horario disponible del docente. 
Error: estudiante no registrado.	Verificar cédula o registrar estudiante.
Error: docente no registrado.	Verificar código o registrar docente.
El docente ya tiene una tutoría en esa fecha y hora.	Elegir una fecha u hora diferente
El asunto no puede estar vacío.	Ingresar el tema o asunto de la tutoría
Solo se pueden cancelar tutorías activas.	Solo es posible cancelar tutorías que estén activas
Solo se pueden reprogramar tutorías activas.	Solo es posible reprogramar tutorías en estado activa.
Error: esa tutoría no te pertenece.	Solo puede modificar sus propias tutorías 
No existe ningún usuario registrado con ese nombre.	El usuario no existe. Se ofrece la opción de registrarse.
Usuario o contraseña incorrectos.	Verificar credenciales.
Acceso bloqueado por demasiados intentos.	Regresar al menú principal e intentar nuevamente.
Error: no se pudo guardar.	Verificar que la carpeta “data/estatus” este en el directorio del programa

•	Recomendaciones
• Usar la opción Regresar al menú principal (opción 15 o 5 según el rol) en lugar de cerrar la ventana, para que los datos se guarden correctamente.
• Realizar copias de respaldo de la carpeta data/ periódicamente para no perder la información registrada.
• No eliminar ni modificar manualmente los archivos .txt de la carpeta data/ mientras el sistema este en uso.
• Si se olvida la contraseña de un usuario, un administrador deberá eliminar y volver a registrar ese usuario.
