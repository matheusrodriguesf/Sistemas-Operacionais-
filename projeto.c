#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#define FIBER_STACK 1024*64
#define SEM 1
#define PEDESTRE 10

int down (){
    SEM<= SEM -1;
    return SEM;
}

int up (){
    SEM<= SEM +1;
    return SEM;
}


int threadFunction( void* argument ){
        while(1){
            if (r==0){
                printf("Carros passando pela via:\n");
                up();
            }
            else{
                printf("Pedestres passando\n");
            }
    }
    return NULL;
    down();
}

int threadFunction2( void* argument ){
    int id = * (int *) v;
    int result=up();
    if (result== 0){
        printf("Pedestre %d esperando para atravessar.\n",id);
        up();
        printf("Pedestre %d atravessou a rua\n",id);
        down();
        printf("Já atravessou a rua pedestre %d \n", id);
    }
    else{
        printf("Pode atravessar rapidamente %d \n",id);
        return NULL;
    }
    down();
}


int main(){
    void* stack;
    pid_t pid;
    stack = malloc( FIBER_STACK );
    if (stack == 0){
        perror("malloc: could not allocate stack");
        exit(1);
    }
    printf( "Creating child thread\n" );
    pid = clone( &threadFunction, (char*) stack + FIBER_STACK,SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
    if ( pid == -1 ){
        perror( "clone" );
        exit(2);
    }
    pid = waitpid( pid, 0, 0 );
    if (pid == -1){
        perror( "waitpid" );
        exit(3);
    }



    printf( "Creating child 2 thread\n" );
    pid = clone( &threadFunction2, (char*) stack + FIBER_STACK,SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
    if ( pid == -1 ){
        perror( "clone" );
        exit(2);
    }
    pid = waitpid( pid, 0, 0 );
    if (pid == -1){
        perror( "waitpid" );
        exit(3);
    }
    free( stack );
    printf( "Child thread returned and stack freed.\n" );
    return 0;
 }
