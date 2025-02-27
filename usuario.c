#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include "funciones.h"

#define MAX_LINEA 42
#define MAX_PALABRA 20

int main() {

    printf("Registro de usuarios\n");

    while (1) {
        system("clear");
        
        printf("\nEscribe un nombre de usuario: ");
        scanf("%19s", usuario.n_usuario);
        
        printf("\nEscribe el tipo de usuario D o P: ");
        scanf("%1s", usuario.t_usuario);
        while (getchar() != '\n'); 
        
        printf("\nEscribe la contraseña: ");
        ocultar(usuario.c_usuario, MAX_PALABRA);
        
        registro(usuario.n_usuario, usuario.c_usuario, usuario.t_usuario);
        
        printf("\nPresione Enter para continuar...");
        while (getchar() != '\n');
        getchar();
        system("clear");
    }
    return 0;
}
