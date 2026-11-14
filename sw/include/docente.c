#include <stdio.h>
#include "docente.h"

void configurar_ponderaciones(Materia *mat) {
    float examenes, tareas, proyectos;

    if (mat == NULL) return;

    do {
        printf("\\nPonderacion de examenes (0 a 100): ");
        scanf("%f", &examenes);
        printf("Ponderacion de tareas (0 a 100): ");
        scanf("%f", &tareas);
        printf("Ponderacion de proyectos (0 a 100): ");
        scanf("%f", &proyectos);

        if (examenes < 0 || tareas < 0 || proyectos < 0 ||
            examenes > 100 || tareas > 100 || proyectos > 100 ||
            examenes + tareas + proyectos != 100.0f) {
            printf("Error: las ponderaciones deben sumar exactamente 100. Intente de nuevo.\\n");
        }
    } while (examenes < 0 || tareas < 0 || proyectos < 0 ||
             examenes > 100 || tareas > 100 || proyectos > 100 ||
             examenes + tareas + proyectos != 100.0f);

    mat->ponderacion_examenes = examenes;
    mat->ponderacion_tareas = tareas;
    mat->ponderacion_proyectos = proyectos;

    printf("[SUCCESS] Ponderaciones actualizadas.\\n");
}

float calcular_promedio_provisional(Estudiante *est, Materia *mat) {
    float suma[4] = {0, 0, 0, 0};
    int cantidad[4] = {0, 0, 0, 0};
    float pesos[4];
    float resultado = 0.0f;
    float peso_utilizado = 0.0f;
    int i, categoria;

    if (est == NULL || mat == NULL) return 0.0f;

    pesos[1] = mat->ponderacion_examenes;
    pesos[2] = mat->ponderacion_tareas;
    pesos[3] = mat->ponderacion_proyectos;

    for (i = 0; i < est->total_actividades; i++) {
        categoria = est->actividades[i].categoria;
        if (categoria >= 1 && categoria <= 3 &&
            est->actividades[i].evaluada == 1) {
            suma[categoria] += est->actividades[i].calificacion;
            cantidad[categoria]++;
        }
    }

    for (categoria = 1; categoria <= 3; categoria++) {
        if (cantidad[categoria] > 0) {
            resultado += (suma[categoria] / cantidad[categoria]) *
                         (pesos[categoria] / 100.0f);
            peso_utilizado += pesos[categoria];
        }
    }

    if (peso_utilizado == 0.0f) return 0.0f;

    /* Se expresa sobre los criterios que ya tienen calificaciones. */
    return resultado * 100.0f / peso_utilizado;
}

void calcular_promedio_con_criterios(const Materia *mat) {
    if (mat == NULL) return;

    printf("\\nCriterios de evaluacion de %s:\\n", mat->nombre);
    printf("Examenes: %.2f%%\\n", mat->ponderacion_examenes);
    printf("Tareas: %.2f%%\\n", mat->ponderacion_tareas);
    printf("Proyectos: %.2f%%\\n", mat->ponderacion_proyectos);
    printf("El promedio se calcula aplicando estos porcentajes a cada categoria.\\n");
}

void modificar_calificacion_manual(Estudiante *est, int id_actividad, float nueva_nota) {
    int i;

    if (est == NULL || nueva_nota < 0 || nueva_nota > 100) {
        printf("Error: estudiante no valido o calificacion fuera del rango 0-100.\\n");
        return;
    }

    for (i = 0; i < est->total_actividades; i++) {
        if (est->actividades[i].id == id_actividad) {
            est->actividades[i].calificacion = nueva_nota;
            est->actividades[i].evaluada = 1;
            est->actividades[i].pendiente = 0;
            printf("[SUCCESS] Calificacion modificada.\\n");
            return;
        }
    }

    printf("No se encontro una actividad con ese identificador.\\n");
}
