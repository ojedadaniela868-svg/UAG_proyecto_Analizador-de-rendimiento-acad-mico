#ifndef MAIN_H
#define MAIN_H

#include "modelos.h"
#include "auth.h"
#include "docente.h"
#include "alumno.h"
#include "coordinador.h"

void mostrar_menu_principal(void);
void menu_docente(Grupo *grupo, Materia *materia, Sesion *sesion);
void menu_coordinador(Grupo *grupo, Materia *materia, Sesion *sesion);
void menu_alumno(Grupo *grupo, Materia *materia, Sesion *sesion);

#endif
