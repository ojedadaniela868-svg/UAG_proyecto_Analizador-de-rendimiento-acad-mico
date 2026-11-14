#include <stdio.h>
#include "coordinador.h"

void consultar_datos_grupo(const Grupo *grupo) {
    if (grupo == NULL) return;

    printf("\\n========== DATOS DEL GRUPO ==========\\n");
    printf("Grupo: %s\\n", grupo->nombre);
    printf("Materia: %s\\n", grupo->materia);
    printf("Docente: %s\\n", grupo->docente);
    printf("Periodo: %s\\n", grupo->periodo);
}

void mostrar_estadisticas_inscritos(const Grupo *grupo) {
    int i, j;
    int pendientes = 0;

    if (grupo == NULL) return;

    for (i = 0; i < grupo->total_estudiantes; i++) {
        for (j = 0; j < grupo->estudiantes[i].total_actividades; j++) {
            if (!grupo->estudiantes[i].actividades[j].evaluada)
                pendientes++;
        }
    }

    printf("\\n========== ESTADISTICAS DEL GRUPO ==========\\n");
    printf("Total de estudiantes inscritos: %d\\n", grupo->total_estudiantes);
    printf("Actividades pendientes por calificar: %d\\n", pendientes);
}
