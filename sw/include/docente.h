#ifndef DOCENTE_H
#define DOCENTE_H

#include "modelos.h"

void configurar_ponderaciones(Materia *mat);
float calcular_promedio_provisional(Estudiante *est, Materia *mat);
void calcular_promedio_con_criterios(const Materia *mat);
void modificar_calificacion_manual(Estudiante *est, int id_actividad, float nueva_nota);

#endif
