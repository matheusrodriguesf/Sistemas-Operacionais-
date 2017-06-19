#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define N_PEDESTRES 10
#define N_CARROS 10


int turn=0;
int controle=1;

int dimi(void* argument){
    turn=1;
}
int aut(void * argument){
    turn=0;
}

/*funcao dos carros*/
void* funcaoCarros(void* args){
while(turn!=0){
    int ct = *(int*)args;
    printf("Carro %d passando\n ",ct);
    aut(&turn);
    
}
}

/*funcao dos pedestres*/
void* funcaoPedestres(void* args){
while (turn!=1){
        int ct = *(int*)args;
        printf("pedestre %d passando\n",ct);
        dimi(&turn);
}    
}

/*Metodo principal*/
int main(){
    pthread_t threadCarros[N_CARROS];
    pthread_t threadPedestres[N_PEDESTRES];
    int i;

    /*Variavel para identificado de cliente*/
    int idPedestres[N_PEDESTRES];
    /*Criação da thread do pedestre*/
    
    for(i=0; i < N_PEDESTRES;i++){
        idPedestres[i] = i;
        pthread_create(&threadPedestres[i],NULL,funcaoPedestres,&idPedestres[i]);
    }

    int idCarros[N_CARROS];
    for(i=0; i < N_CARROS;i++){
        idCarros[i] = i;
        pthread_create(&threadCarros[i],NULL,funcaoCarros,&idCarros[i]);
    }
    
    for(i=0;i < N_PEDESTRES;i++){
        pthread_join(threadPedestres[i],NULL);
        pthread_join(threadCarros[i],NULL);
    
}
   
    
}//fim do metodo principal.
