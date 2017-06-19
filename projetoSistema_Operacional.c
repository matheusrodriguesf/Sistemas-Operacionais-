#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define CARROS 100
#define PEDESTRES 100
int lock = 0;//Variavel global, do tipo inteiro para realizar o controle.
int teste(){
    while(lock!=0){
        lock = 1;
        /*Região critica*/
        lock = 0;
        return 0;
    }
}



void *function_carros(void*args){
    printf("\nEu sou a porra da thread dos carros !!!\n");
    return NULL;
}

void *function_pedestres(void*args){
    printf("\nEu sou a porra da thread dos carros !!!\n");
    return NULL;
}




/* ALGORITMO PARA VARIAVEL DE TRAVA(LOCK);
    * Uma variavel compartilhada(trava).
    * Está variavel inicialmente contendo o valor 0.
    * O processo antes de entrar na região critica, deve testar o valor da trava.
    * Se o valor da trava for 0, o processo deve alterar o valor da trava para 1.
    * Se o valor da trava for 1, o processo deve aguardar até que o valor da trava seja 0.
*/
int main(){
    int i;
    pthread_t thr1;
    pthread_t thr2;
    
    /*Criação de uma thread.*/
    pthread_create(&thr1,NULL,function_thread1,NULL);
    /*Criação da segunda thread.*/
    pthread_create(&thr2,NULL,function_thread2,NULL);

    function_thread1(NULL);
    function_thread2(NULL);
    return 0;
    
}


