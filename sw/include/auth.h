#ifndef AUTH_H
#define AUTH_H

#include "modelos.h"

#define ROL_NINGUNO 0
#define ROL_DOCENTE 1
#define ROL_COORDINADOR 2
#define ROL_ALUMNO 3

#define MAX_USUARIOS 30

typedef struct {
    int id_usuario;
    int pin;
    int rol;
    char nombre_completo[60];
} Usuario;

typedef struct {
    int autenticado;
    int id_usuario;
    int rol;
    char nombre_completo[60];
} Sesion;

int registrar_usuario(Usuario usuarios[], int *total_usuarios, int max_usuarios, int id_usuario, int pin, int rol, const char *nombre);
int validar_credenciales(char *user, char *pass);
int iniciar_sesion(const Usuario usuarios[], int total_usuarios, int id_usuario, int pin, Sesion *sesion);
void validar_permisos_acceso(int id_usuario, int rol_esperado);
int verificar_acceso_rol(const Sesion *sesion, int rol_esperado);
int validar_privacidad_alumno(const Sesion *sesion, int registro_estudiante);
void cerrar_sesion(Sesion *sesion);

#endif
