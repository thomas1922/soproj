//Rui Santos - 2020225542
//Tomás Dias - 2020215701

#include "funcoes.h"


int main(int argc, char *argv[]){

    if(argc != 2){ //por no log???
        printf("Erro: número de argumentos inválido\n");
        return 0;
    }
    inicia();
    if(fork()==0){
        systemManager(argv[1]);
    }
    wait(NULL);
    termina();
    return 0;
}