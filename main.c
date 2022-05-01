#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int ID;
    int maxtime;
}tarefa;


struct no_fila{
    tarefa t;
    struct no_fila *pseg;
};

struct tarefas{
    int tamanho;
    struct no_fila *raiz;
};


void colocar(struct tarefas *p, tarefa t){
    struct no_fila *aux;
    aux = (struct no_fila*) malloc(sizeof(struct no_fila));
    aux->t=t;
    aux->pseg=NULL;

    if(p->raiz==NULL){
        p->raiz=aux;
        p->tamanho = 1;
    }
    else{
        struct no_fila *temp;
        for(temp = p->raiz; temp->pseg!=NULL; temp = temp->pseg);
        temp->pseg = aux;
        p->tamanho+=1;
    }
}

void ordenar(struct tarefas *p){
    struct no_fila *atual = p->raiz, *index = NULL;

    tarefa t;
    if(p->raiz==NULL){
        return;
    }
    else{
        while(atual!=NULL){
            index = atual->pseg;

            while (index!=NULL){
                if(atual->t.maxtime>index->t.maxtime){
                    t = atual->t;
                    atual->t=index->t;
                    index->t=t;
                }
                index=index->pseg;
            }
            atual=atual->pseg;
        }
    }
}



void retirar(struct tarefas *p, tarefa t){
    struct no_fila *temp = p->raiz, *anterior;

    if(temp!=NULL && temp->t.ID==t.ID && temp->t.maxtime == t.maxtime){
        p->raiz=temp->pseg;
        free(temp);
        p->tamanho--;
        return;
    }
    while(temp!=NULL && !(temp->t.ID==t.ID && temp->t.maxtime == t.maxtime)){
        anterior=temp;
        temp=temp->pseg;
    }
    if(temp==NULL){
        return;
    }
    anterior->pseg=temp->pseg;
    p->tamanho--;
    free(temp);

}

int main() {

    tarefa t1 = {1, 10};
    tarefa t7 = {2, 2};
    tarefa t6 = {8, 80};
    tarefa t5 = {5, 5};
    tarefa t3 = {9, 10};


    struct tarefas tarefas;
    tarefas.raiz=NULL;

    colocar(&tarefas, t1);
    colocar(&tarefas, t6);
    colocar(&tarefas, t7);
    colocar(&tarefas, t5);
    colocar(&tarefas, t3);


    for (struct no_fila *aux = tarefas.raiz; aux!=NULL; aux = aux->pseg) {
        printf("%d\n", aux->t.maxtime);
    }

    ordenar(&tarefas);

    printf("----\n");

    for (struct no_fila *aux = tarefas.raiz; aux!=NULL; aux = aux->pseg) {
        printf("%d\n", aux->t.maxtime);
    }
    printf("----\n");
    printf("----\n");
    retirar(&tarefas, t7);
    printf("%d\n", tarefas.tamanho);
    retirar(&tarefas, t1);
    printf("%d\n", tarefas.tamanho);
    retirar(&tarefas, t5);
    printf("%d\n", tarefas.tamanho);
    retirar(&tarefas, t6);
    printf("%d\n", tarefas.tamanho);
    retirar(&tarefas, t3);
    printf("%d\n", tarefas.tamanho);
    printf("----\n");
    printf("----\n");

    for (struct no_fila *aux = tarefas.raiz; aux!=NULL; aux = aux->pseg) {
        printf("%d ", aux->t.maxtime);
    }
}
