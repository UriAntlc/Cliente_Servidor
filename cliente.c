#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <termios.h>
#include <string.h>
#include "funciones.h"

#define PERMISOS 0777
#define max_palabra 20

int semaforo(key_t llave,int vi){
    int semid=semget(llave,1,IPC_CREAT|PERMISOS);
    if(semid==-1){
        return -1;
    }
    semctl(semid,0,SETVAL,vi);
    return semid;
}

void apagado(int semid){
    struct sembuf op_p[]={0,-1,0};
    semop(semid,op_p,1);
}

void encendido(int semid){
    struct sembuf op_v[]={0,+1,0};
    semop(semid,op_v,1);
}

int main(){
    
    int clientes, id_c, mutex;
    
    key_t llave_clientes,llave_u,llave_m;
    llave_clientes=ftok("clientes",'c');
    llave_u=ftok("usuario",'u');
    llave_m=ftok("mutex",'s');
    
    clientes=semaforo(llave_clientes,0);
    mutex=semaforo(llave_m,0);
    id_c=shmget(llave_u,sizeof(struct cliente),IPC_CREAT|PERMISOS);
    cliente=(struct cliente *)shmat(id_c,0,0);
    encendido(clientes);
    
    while(1){
        principal();
        system("clear");
        encendido(mutex);
    }
}