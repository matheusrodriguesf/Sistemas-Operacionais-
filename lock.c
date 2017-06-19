#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#define N_CARROS 10
#define N_PEDESTRES 10 
int lock = 0;
void* functionCarros(void *args){
    int ct = *(int*)args;
    if(lock==0){
        
        lock = 1;
        printf("Via liberada\n ");
        while(lock!=0){
            printf("Carro %d passando\n ",ct);
            printf("Pedestre aguardando\n ");    
            lock = 0;
        }
        
    } else{
           printf("Faixa de pedestre liberada");
           printf("Pedestre %d passando\n",ct);
           printf("Carro aguardando\n");    
    }
 
    
    
}

void* functionPedestres(void*args){
    int ct = *(int*)args;
    if(lock==0){
        lock = 1;
           printf("Faixa de pedestre liberada\n ");
        
        while(lock!=0){
           printf("Pedestre %d passando\n",ct);
           printf("Carro aguardando\n");    
           lock = 0;
    }
    } else{
           printf("Faixa de pedestre liberada\n");
            printf("Carro %d passando\n",ct);
            printf("Pedestre aguardando\n");    
    }
  
    
}


int main(){
    pthread_t threadCarros[N_CARROS];
    pthread_t threadPedestres[N_PEDESTRES];
    int i;

    /*Variavel para identificado de cliente*/
    int idPedestres[N_PEDESTRES];
    /*Criação da thread do pedestre*/
    
    for(i=0; i < N_PEDESTRES;i++){
        idPedestres[i] = i;
        pthread_create(&threadPedestres[i],NULL,functionPedestres,&idPedestres[i]);
    }

    int idCarros[N_CARROS];
    for(i=0; i < N_CARROS;i++){
        idCarros[i] = i;
        pthread_create(&threadCarros[i],NULL,functionCarros,&idCarros[i]);
    }
    
    for(i=0;i < N_PEDESTRES;i++){
        pthread_join(threadPedestres[i],NULL);
        pthread_join(threadCarros[i],NULL);
    
    }
}
