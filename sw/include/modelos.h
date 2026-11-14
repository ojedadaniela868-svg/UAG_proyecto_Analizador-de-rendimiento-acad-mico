#ifndef MODELOS_H
#define MODELOS_H

#define MAX_ESTUDIANTES 20
#define MAX_ACTIVIDADES 30

typedef struct {
    int id;
    char nombre[50];
    char fecha_limite[20];
    float calificacion;
    int categoria;       /* 1 = examen, 2 = tarea, 3 = proyecto */
    int evaluada;        /* 1 = ya tiene calificacion, 0 = pendiente */
    int pendiente;       /* 1 = tiene prorroga/esta pendiente */
} Actividad;

typedef struct {
    char nombre[50];
    float ponderacion_examenes;
    float ponderacion_tareas;
    float ponderacion_proyectos;
} Materia;

typedef struct {
    int registro;
    char nombre[30];
    char apellido_paterno[15];
    char apellido_materno[15];
    int semestre;
    char carrera[100];
    int num_sanciones;
    Actividad actividades[MAX_ACTIVIDADES];
    int total_actividades;
} Estudiante;

typedef struct {
    char nombre[30];
    char materia[50];
    char docente[50];
    char periodo[30];
    Estudiante estudiantes[MAX_ESTUDIANTES];
    int total_estudiantes;
} Grupo;

#endif
