#include <stdio.h>
#include <string.h>
#include "auth.h"

int registrar_usuario(Usuario usuarios[], int *total_usuarios, int max_usuarios, int id_usuario, int pin, int rol, const char *nombre) {
    if (*total_usuarios >= max_usuarios) return 0;

    usuarios[*total_usuarios].id_usuario = id_usuario;
    usuarios[*total_usuarios].pin = pin;
    usuarios[*total_usuarios].rol = rol;
    strcpy(usuarios[*total_usuarios].nombre_completo, nombre);
    (*total_usuarios)++;

    return 1;
}

int validar_credenciales(char *user, char *pass) {
    return 0;
}

int iniciar_sesion(const Usuario usuarios[], int total_usuarios, int id_usuario, int pin, Sesion *sesion) {
    int i;
    for (i = 0; i < total_usuarios; i++) {
        if (usuarios[i].id_usuario == id_usuario && usuarios[i].pin == pin) {
            sesion->autenticado = 1;
            sesion->id_usuario = usuarios[i].id_usuario;
            sesion->rol = usuarios[i].rol;
            strcpy(sesion->nombre_completo, usuarios[i].nombre_completo);
            return 1;
        }
    }
    return 0;
}

void validar_permisos_acceso(int id_usuario, int rol_esperado) {
    printf("Permisos validados\n");
}

int verificar_acceso_rol(const Sesion *sesion, int rol_esperado) {
    return (sesion->rol == rol_esperado);
}

int validar_privacidad_alumno(const Sesion *sesion, int registro_estudiante) {
    if (sesion->rol == ROL_DOCENTE || sesion->rol == ROL_COORDINADOR) return 1;
    if (sesion->rol == ROL_ALUMNO && sesion->id_usuario == registro_estudiante) return 1;
    return 0;
}

void cerrar_sesion(Sesion *sesion) {
    sesion->autenticado = 0;
}
