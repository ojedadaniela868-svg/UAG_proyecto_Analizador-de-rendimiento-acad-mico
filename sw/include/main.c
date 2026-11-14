#include <stdio.h>
#include <string.h>
#include "main.h"

void mostrar_menu_principal(void) {
    printf("\n=== SISTEMA DE GESTION DEL DESEMPENO ESCOLAR ===\n");
    printf("1. Docente\n");
    printf("2. Coordinador\n");
    printf("3. Alumno\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
}

void menu_docente(Grupo *grupo, Materia *materia, Sesion *sesion) {
    int op = -1;
    int reg, id_act, i;
    float nota;

    if (!verificar_acceso_rol(sesion, ROL_DOCENTE)) return;

    while (op != 0) {
        printf("\n--- MENU DOCENTE ---\n");
        printf("1. Configurar ponderaciones\n");
        printf("2. Modificar calificacion manual\n");
        printf("3. Ver promedio provisional\n");
        printf("0. Regresar\n");
        printf("Opcion: ");
        scanf("%d", &op);

        if (op == 1) {
            configurar_ponderaciones(materia);
        } else if (op == 2) {
            printf("Registro del alumno: ");
            scanf("%d", &reg);
            printf("ID actividad: ");
            scanf("%d", &id_act);
            printf("Nueva nota: ");
            scanf("%f", &nota);
            for (i = 0; i < grupo->total_estudiantes; i++) {
                if (grupo->estudiantes[i].registro == reg) {
                    modificar_calificacion_manual(&grupo->estudiantes[i], id_act, nota);
                }
            }
        } else if (op == 3) {
            for (i = 0; i < grupo->total_estudiantes; i++) {
                printf("Registro %d: %.2f\n",
                       grupo->estudiantes[i].registro,
                       calcular_promedio_provisional(&grupo->estudiantes[i], materia));
            }
        }
    }
}

void menu_coordinador(Grupo *grupo, Materia *materia, Sesion *sesion) {
    int op = -1;

    if (!verificar_acceso_rol(sesion, ROL_COORDINADOR)) return;

    while (op != 0) {
        printf("\n--- MENU COORDINADOR ---\n");
        printf("1. Consultar datos del grupo\n");
        printf("2. Mostrar estadisticas de inscritos\n");
        printf("3. Generar alertas del grupo\n");
        printf("0. Regresar\n");
        printf("Opcion: ");
        scanf("%d", &op);

        if (op == 1) {
            consultar_datos_grupo(grupo);
        } else if (op == 2) {
            mostrar_estadisticas_inscritos(grupo);
        } else if (op == 3) {
            /* TODO: falta conectar funcion generar_alertas_grupo() */
        }
    }
}

void menu_alumno(Grupo *grupo, Materia *materia, Sesion *sesion) {
    int op = -1;
    int i, j;
    float meta;

    if (!verificar_acceso_rol(sesion, ROL_ALUMNO)) return;

    while (op != 0) {
        printf("\n--- MENU ALUMNO ---\n");
        printf("1. Ver calificacion final\n");
        printf("2. Ver actividades y fechas limite\n");
        printf("3. Simular calificacion\n");
        printf("0. Regresar\n");
        printf("Opcion: ");
        scanf("%d", &op);

        if (op == 1) {
            for (i = 0; i < grupo->total_estudiantes; i++) {
                if (validar_privacidad_alumno(sesion, grupo->estudiantes[i].registro)) {
                    calcular_promedio_con_criterios(materia);
                    printf("Calificacion final: %.2f\n",
                           calcular_calificacion_final_rd(&grupo->estudiantes[i], materia));
                }
            }
        } else if (op == 2) {
            for (i = 0; i < grupo->total_estudiantes; i++) {
                if (validar_privacidad_alumno(sesion, grupo->estudiantes[i].registro)) {
                    for (j = 0; j < grupo->estudiantes[i].total_actividades; j++) {
                        mostrar_metadatos_tarea(&grupo->estudiantes[i].actividades[j]);
                    }
                }
            }
        } else if (op == 3) {
            printf("Nota deseada: ");
            scanf("%f", &meta);
            simular_calificacion(materia, meta);
        }
    }
}

int main(void) {
    Grupo grupo;
    Materia materia;
    Usuario usuarios[MAX_USUARIOS];
    Sesion sesion;
    int total_usuarios = 0;
    int opcion = -1;
    int id_usuario, pin;

    grupo.total_estudiantes = 0;
    sesion.autenticado = 0;

    while (opcion != 0) {
        mostrar_menu_principal();
        scanf("%d", &opcion);

        if (opcion >= 1 && opcion <= 3) {
            printf("ID / Registro: ");
            scanf("%d", &id_usuario);
            printf("PIN: ");
            scanf("%d", &pin);

            if (iniciar_sesion(usuarios, total_usuarios, id_usuario, pin, &sesion)) {
                validar_permisos_acceso(sesion.id_usuario, opcion);
                if (opcion == ROL_DOCENTE) {
                    menu_docente(&grupo, &materia, &sesion);
                } else if (opcion == ROL_COORDINADOR) {
                    menu_coordinador(&grupo, &materia, &sesion);
                } else if (opcion == ROL_ALUMNO) {
                    menu_alumno(&grupo, &materia, &sesion);
                }
                cerrar_sesion(&sesion);
            } else {
                printf("[!] Credenciales invalidas.\n");
            }
        }
    }
}
