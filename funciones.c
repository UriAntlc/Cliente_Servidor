#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include "funciones.h"

//menus
void mostrarPrincipal() {
    printf("\n--- Menu ---\n");
    printf("1. Iniciar\n");
    printf("2. Registrar\n");
    printf("3. Salir\n");
}

void mostrarMenu() {
    printf("\n--- Menu ---\n");
    printf("1. Generar Cita\n");
    printf("2. Salir\n");
}

void menuPaciente() {
    printf("\n--- Menu ---\n");
    printf("1. Ver Citas\n");
    printf("2. Salir\n");
}

//funciones inicios
void iniciar(){
    system("clear");
        
    printf("\nEscribe un nombre de cliente: ");
    scanf("%s", cliente->n_cliente);
    
    printf("\nEscribe el tipo de usuario D o P: ");
    scanf("%1s", cliente->t_cliente);
    fflush(stdin);
    
    printf("\nEscribe la contarseña: ");
    ocultar(cliente->c_cliente, max_palabra);
    busqueda(cliente->n_cliente, cliente->c_cliente, cliente->t_cliente);
}

void inicioRegistro(){
    system("clear");
        
    printf("\nEscribe un nombre de cliente: ");
    scanf("%s", cliente->n_cliente);
    
    printf("\nEscribe el tipo de usuario D o P: ");
    scanf("%1s", cliente->t_cliente);
    fflush(stdin);
    
    printf("\nEscribe la contarseña: ");
    ocultar(cliente->c_cliente, max_palabra);
    registro(cliente->n_cliente, cliente->c_cliente, cliente->t_cliente);
}

//ususarios
void principal(){
    int opcion;
    do {
        mostrarPrincipal();
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida. Por favor ingrese un número.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        switch(opcion) {
            case 1:
                iniciar();
                break;
            case 2:
                inicioRegistro();
                break;
            case 3:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Por favor, intente de nuevo.\n");
        }
    } while(opcion != 3);
}

void doctor(){
    int opcion;
    do {
        mostrarMenu();
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida. Por favor ingrese un número.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        switch(opcion) {
            case 1:
                generarCita();
                break;
            case 2:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Por favor, intente de nuevo.\n");
        }
    } while(opcion != 2);
}

void paciente(){
    int opcion;
    do {
        menuPaciente();
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida. Por favor ingrese un número.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        switch(opcion) {
            case 1:
                ver(cliente->n_cliente);
                break;
            case 2:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Por favor, intente de nuevo.\n");
        }
    } while(opcion != 2);
}

//funciones doctor
void generarCita() {
    FILE *file = fopen("usuarios.txt", "r");
    if (!file) {
        perror("No se pudo abrir el archivo de pacientes");
        return;
    }
    char line[MAX_LINEA];
    Paciente pacientes[100];
    int count = 0, pac;
    while (fgets(line, sizeof(line), file)) {
        Paciente paciente;
        char *token = strtok(line, ",");
        if (token != NULL) {
            strncpy(paciente.p_nombre, token, MAX_PALABRA);
            paciente.p_nombre[MAX_PALABRA - 1] = '\0'; // Asegurar la terminación nula
        }
        token = strtok(NULL, ",");
        if (token != NULL) {
            strncpy(paciente.p_otroDato, token, MAX_PALABRA);
            paciente.p_otroDato[MAX_PALABRA - 1] = '\0'; // Asegurar la terminación nula
        }
        token = strtok(NULL, ",");
        if (token != NULL) {
            paciente.p_identificador = token[0];
        }
        if (paciente.p_identificador == 'P') {
            pacientes[count++] = paciente;
        }
    }
    fclose(file);
    if (count == 0) {
        printf("\nNo hay pacientes disponibles para cita.\n");
    } else {
        printf("\nPacientes disponibles para cita:\n");
        for (int i = 0; i < count; i++) {
            printf("%d.- %s\n", i, pacientes[i].p_nombre);
        }
    }
    printf("Selecciona el paciente que desees.");
    scanf("%d", &pac);
    fflush(stdin);
    generar(pacientes[pac].p_nombre);
}

void generar(char *paciente){
    int var = 0;
    char cadena[MAX_LINEA];
    char seccion1[MAX_PALABRA], seccion2[MAX_PALABRA], seccion3[MAX_PALABRA];
    char nombreArchivo[MAX_PALABRA + 5];
    printf("Razon de la consulta: ");
    fgets(cadena, sizeof(cadena), stdin);
    cadena[strcspn(cadena, "\n")] = '\0';
    printf("Ingrese tres secciones separadas por comas los siguientes elementos\n");
    printf("Medicamento, Dosis, Tiempo de tratamiento: \n");
    scanf("%19[^,], %19[^,], %19[^,\n]", seccion1, seccion2, seccion3);
    snprintf(nombreArchivo, sizeof(nombreArchivo), "%s.txt", paciente);
    FILE *file = fopen(nombreArchivo, "a");
    if (file == NULL) {
        perror("No se pudo abrir el archivo");
        return;
    }
    fprintf(file, "%s\n", paciente);
    fprintf(file, "%s\n", cadena);
    fprintf(file, "%s,%s,%s\n\n", seccion1, seccion2, seccion3);
    fclose(file);
    printf("La informacion se ha escrito en el archivo '%s'.\n", paciente);
}

//funciones paciente
void ver(char *nombrePaciente) {
    FILE *file;
    char line[MAX_LINEA];
    char nombreArchivo[MAX_LINEA + 4];
    snprintf(nombreArchivo, sizeof(nombreArchivo), "%s.txt", nombrePaciente);
    file = fopen(nombreArchivo, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo '%s' para lectura.\n", nombreArchivo);
        return;
    }
    printf("Contenido de la receta de '%s':\n", nombrePaciente);
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

//funciones registro
void escritura(const char *usuario, const char *contraseña, const char *tipo) {
    FILE *archivo_w = fopen("usuarios.txt", "a");
    if (archivo_w == NULL) {
        printf("\nError en la apertura del archivo para escritura.\n");
        return;
    }
    if (fprintf(archivo_w, "%s,%s,%s\n", usuario, contraseña, tipo) > 0) {
        printf("\nUsuario: %s registrado\n", usuario);
    } else {
        printf("\nError al escribir en el archivo.\n");
    }
    fclose(archivo_w);
}

void registro(const char *usuario, const char *contraseña, const char *tipo) {
    char nombre_usuario[MAX_PALABRA];
    char contraseña_usuario[MAX_PALABRA];
    char tipo_usuario[2];
    FILE *archivo_r = fopen("usuarios.txt", "r");
    if (archivo_r == NULL) {
        printf("No se pudo abrir el archivo para lectura.\n");
        return;
    }
    char linea[MAX_LINEA];
    int existe = 0;
    while (fgets(linea, MAX_LINEA, archivo_r) != NULL) {
        linea[strcspn(linea, "\n")] = '\0'; // Eliminar el salto de línea
        char *token = strtok(linea, ",");
        if (token != NULL) {
            strncpy(nombre_usuario, token, MAX_PALABRA);
            token = strtok(NULL, ",");
            if (token != NULL) {
                strncpy(contraseña_usuario, token, MAX_PALABRA);
                token = strtok(NULL, ",");
                if (token != NULL) {
                    strncpy(tipo_usuario, token, 2);
                }
            }
        }
        if (strcmp(nombre_usuario, usuario) == 0 && strcmp(contraseña_usuario, contraseña) == 0 && strcmp(tipo_usuario, tipo) == 0) {
            existe = 1;
            break;
        }
    }
    fclose(archivo_r);
    if (!existe) {
        escritura(usuario, contraseña, tipo);
    } else {
        printf("\nEl usuario %s ya está registrado.\n", usuario);
    }
}

//funcion seguridad
void ocultar(char *o_contraseña, int maxLen) {
    struct termios oldt, newt;
    int i = 0;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    while ((ch = getchar()) != '\n' && ch != EOF && i < maxLen - 1) {
        o_contraseña[i++] = ch;
    }
    o_contraseña[i] = '\0';
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

//funcion validacion
void busqueda(char *usuario, char *contraseña, char *tipo_cliente){
    FILE *archivo = fopen("usuarios.txt", "r");
    if (archivo == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo.\n");
    }
    
    char palabra1[max_palabra]; 
    char palabra2[max_palabra];
    char palabra3[2];
    char linea[max_linea];
    char *token;
    int encontradas = 0;
    
    while (fgets(linea, max_palabra, archivo) != NULL) {
        
        linea[strcspn(linea, "\n")] = '\0';
        token = strtok(linea, ",");
        
        if (token != NULL) {
            strcpy(palabra1, token);
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(palabra2, token);
                token = strtok(NULL, ",");
                if (token != NULL) {
                strcpy(palabra3, token);
            }
            }
        }
        
        if (strcmp(palabra1, usuario) == 0 && strcmp(palabra2, contraseña) == 0 && strcmp(palabra3, tipo_cliente) == 0) {
            encontradas = 1;
            break;
        }
    }
    
    fclose(archivo);
    if (encontradas) {
        if(strcmp(palabra3, "D") == 0){
            printf("Doctor: %s localizado\n", usuario);
            doctor();
        }
        if(strcmp(palabra3, "P") == 0){
            printf("Paciente: %s localizado\n", usuario);
            paciente();
        }
    }else {
        
    }
}
