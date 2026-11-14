#include <stdio.h>
#include "alumno.h"

float simular_calificacion(const Materia *mat, float nota_deseada) {
    float pesos[4], calificaciones[4] = {0, 0, 0, 0};
    float peso_calificado = 0.0f, acumulado = 0.0f;
    float peso_restante, requerido;

    if (mat == NULL || nota_deseada < 0 || nota_deseada > 100) return -1.0f;

    pesos[1] = mat->ponderacion_examenes;
    pesos[2] = mat->ponderacion_tareas;
    pesos[3] = mat->ponderacion_proyectos;

    printf("\\nPara simular correctamente, primero capture el promedio actual de cada categoria evaluada.\\n");
    printf("Promedio actual de examenes (si aun no hay, escriba -1): ");
    scanf("%f", &calificaciones[1]);
    printf("Promedio actual de tareas (si aun no hay, escriba -1): ");
    scanf("%f", &calificaciones[2]);
    printf("Promedio actual de proyectos (si aun no hay, escriba -1): ");
    scanf("%f", &calificaciones[3]);

    for (int i = 1; i <= 3; i++) {
        if (calificaciones[i] >= 0 && calificaciones[i] <= 100) {
            acumulado += calificaciones[i] * pesos[i] / 100.0f;
            peso_calificado += pesos[i];
        }
    }

    peso_restante = 100.0f - peso_calificado;
    if (peso_restante <= 0.0f) {
        printf("No quedan ponderaciones disponibles para nuevas calificaciones.\\n");
        return 0.0f;
    }

    requerido = (nota_deseada - acumulado) * 100.0f / peso_restante;
    printf("Promedio necesario en el porcentaje restante: %.2f\\n", requerido);

    if (requerido > 100.0f)
        printf("La meta no es alcanzable con las ponderaciones restantes.\\n");
    else if (requerido < 0.0f)
        printf("La meta ya fue alcanzada con las calificaciones actuales.\\n");

    return requerido;
}

void mostrar_metadatos_tarea(const Actividad *act) {
    if (act == NULL) return;

    printf("\\nActividad: %s\\n", act->nombre);
    printf("Fecha limite de entrega: %s\\n", act->fecha_limite);
    if (act->evaluada)
        printf("Estado: Calificada (%.2f)\\n", act->calificacion);
    else
        printf("Estado: Pendiente por calificar\\n");
}

float calcular_calificacion_final_rd(const Estudiante *est, const Materia *mat) {
    float suma[4] = {0, 0, 0, 0};
    int cantidad[4] = {0, 0, 0, 0};
    float pesos[4], resultado = 0.0f;
    int i, categoria;

    if (est == NULL || mat == NULL) return 0.0f;

    pesos[1] = mat->ponderacion_examenes;
    pesos[2] = mat->ponderacion_tareas;
    pesos[3] = mat->ponderacion_proyectos;

    for (i = 0; i < est->total_actividades; i++) {
        categoria = est->actividades[i].categoria;
        if (categoria >= 1 && categoria <= 3 && est->actividades[i].evaluada) {
            suma[categoria] += est->actividades[i].calificacion;
            cantidad[categoria]++;
        }
    }

    for (categoria = 1; categoria <= 3; categoria++) {
        if (cantidad[categoria] > 0)
            resultado += (suma[categoria] / cantidad[categoria]) *
                         (pesos[categoria] / 100.0f);
    }

    return resultado;
}
