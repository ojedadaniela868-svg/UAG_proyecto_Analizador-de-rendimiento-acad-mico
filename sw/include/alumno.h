#ifndef ALUMNO_H
#define ALUMNO_H

#include "modelos.h"

float simular_calificacion(const Materia *mat, float nota_deseada);
void mostrar_metadatos_tarea(const Actividad *act);
float calcular_calificacion_final_rd(const Estudiante *est, const Materia *mat);

#endif
