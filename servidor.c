#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include "funciones.h"

int semaforo(key_t llave,int vi){
    int semid=semget(llave,1,IPC_CREAT|0777);
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

void servidor_clientes(){
    int proceso_c,id_c;
    char nombre_cliente[20],contraseña_cliente[20],tipo_cliente[2];
    
    struct cliente{
        char n_cliente[20];
        char c_cliente[20];
        char t_cliente[2];
    } *cliente;
    
    key_t llave_c;
    llave_c=ftok("usuario",'u');
    id_c=shmget(llave_c,sizeof(struct cliente),IPC_CREAT|0777);
    cliente=(struct cliente *)shmat(id_c,0,0);
    strcpy(nombre_cliente,cliente->n_cliente);
    strcpy(contraseña_cliente,cliente->c_cliente);
    strcpy(tipo_cliente,cliente->t_cliente);
    
    while(1){
        printf("Atendiendo al usuario %s\n", nombre_cliente);
    sleep(3);
    }
    pthread_exit(NULL);
    
}

int main(){
    int mutex, clientes, usuarios;
    
    key_t llave_mutex,llave_clientes,llave_pid;
    pthread_t id_hilo_clientes;
    pthread_attr_t atributos;
    
    llave_mutex=ftok("mutex",'s');
    llave_clientes=ftok("clientes",'c');
    
    clientes=semaforo(llave_clientes,0);
    mutex=semaforo(llave_mutex,1);
    
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos,PTHREAD_CREATE_DETACHED);
    
    while(1){
        system("clear");
        printf("Servidor\n");
        apagado(clientes);
        apagado(mutex);
        pthread_create(&id_hilo_clientes,&atributos,(void*)servidor_clientes,NULL);
    }
}