#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SEM 1
#define PEDESTRE 5


int down (){
SEM<= SEM -1;
return SEM;
}

int up (){
SEM<= SEM +1;
return SEM;
}

void * f_carros (void *v){

int r;

  while(TRUE){
    r=down();
     if (r==0){
    printf("Carros passando pela via:\n");
}
down();
else{
printf("Pedestres passando\n");
down();
printf("%d",r);
}


}

return NULL;

}


void * f_pedestre( void *v){ //procedimento que verifica barbeiro dorme atende?
int id = * (int *) v;
int result=up();
//sleep(id%3);///
if (result== 1){
printf("Pedestres podem atravessar.\n");
down();
}
else{
printf("Atenção semáforo fechado\n");
up();
}

}


int main(){
pthread_t thr_pedestres[PEDESTRE];//vetor de thread indicando as cadeiras
pthread_t thr_carros;//thread do barbeiro
int i;// controla
int id [PEDESTRE];


for(i=0; i<PEDESTRE;i++){
id[i]=i;
pthread_create(&thr_pedestres[i],NULL,f_pedestre,(void *) &id[i]);
}






pthread_create(&thr_carros,NULL,f_carros,NULL);

//chamada thread cliente

for (i=0;i<PEDESTRE;i++){
pthread_join(thr_pedestres[i],NULL);
}

return 0;
}


