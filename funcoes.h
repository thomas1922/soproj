//Rui Santos - 2020225542
//Tomás Dias - 2020215701

#ifndef SYSTEMMANAGER_C_AUX_H
#define SYSTEMMANAGER_C_AUX_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include <semaphore.h>
#include <sys/wait.h>

//#define DEBUG

#define PIPE_NAME  "TASK_PIPE"


typedef struct{
	char *nome;
	int index;	
	int i;
}vcpu_args;



typedef struct{
	time_t tempo_executada;
	time_t tempo;
    int ID;
    int instructionsNumber;
    float maxtime;
} tarefa;

struct no_fila{
    tarefa t;
    struct no_fila *pseg;
};

struct tarefas{
    int tamanho;
    struct no_fila *raiz;
};


typedef struct{
    char nome[20];
    int c1;
    int c2;
    int numero_manutencoes;
    int numero_executadas;
    int flag[2];
    int fds[2];
   	float tempos[2];
    pthread_mutex_t vcpu_mutex[2];
	pthread_cond_t vcpu_work[2];
}edge_Servers;


typedef struct{
    int QUEUE_POS, MAX_WAIT,EDGE_SERVER_NUMBER;
    int flag;
    int total_tarefas_realizadas;
    int total_tarefas_nao_realizadas;
    float tempo_medio;
    float tempoespera;
    struct tarefas tarefas;
    int keep_going;
    int keep_going_dispatcher;
    bool ativo;
    edge_Servers edge_servers[];
}memoria;

sem_t *log_mutex;
sem_t *write_mutex;


memoria *mem;
time_t horas;


int shmid;
int msqid;
key_t key;

void ler_file(char nome[]);
void logW(char s[1000]);
void maintenanceManager();
void taskmanager();
void monitor();
void systemManager(char fileConfig[]);
void inicia();
void termina();

#endif //SYSTEMMANAGER_C_AUX_H
