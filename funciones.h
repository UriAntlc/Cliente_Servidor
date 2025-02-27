#ifndef CITAS_H
#define CITAS_H

#define MAX_LINEA 100
#define MAX_PALABRA 50
#define max_palabra 20
#define max_linea 42

struct {
        char n_usuario[MAX_PALABRA];
        char c_usuario[MAX_PALABRA];
        char t_usuario[2];
    } usuario;

typedef struct {
    char p_nombre[MAX_PALABRA];
    char p_otroDato[MAX_PALABRA];
    char p_identificador;
} Paciente;

struct cliente{
        char n_cliente[max_palabra];
        char c_cliente[max_palabra];
        char t_cliente[2];
}*cliente;

//Menus
void mostrarPrincipal();
void mostrarMenu();
void menuPaciente();

//funciones inicios
void iniciar();
void inicioRegistro();

//Usuarios
void principal();
void doctor();
void paciente();

//funciones doctor
void generarCita();
void generar(char *paciente);

//funciones paciente
void ver(char *nombrePaciente);

//funciones registro
void escritura(const char *usuario, const char *contraseña, const char *tipo);
void registro(const char *usuario, const char *contraseña, const char *tipo);

//funciones seguridad
void ocultar(char *o_contraseña, int maxLen);

//funciones validacion
void busqueda(char *usuario, char *contraseña, char *tipo_cliente);
#endif /* CITAS_H */
