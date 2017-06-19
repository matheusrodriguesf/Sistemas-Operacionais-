#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>


#define FIBER_STACK 1024*64
int turn=0;

int threadPedestre(void* argumento){
while (turn!=0){
printf("Pedestres passando");
}
turn=1;
}


void pedestres(){
printf("Pedestres passando");
turn=1;
}

int threadCarros (void* argumento){
while(turn!=1){
printf("Carros passando pela via\n");
}
turn=0;
}

void carros(){
printf("Carros passam pela via\n");
turn=0;
}

int main(){
void* stack;
pid_t pid_c;
pid_t pid_a;
stack=malloc (FIBER_STACK);
pid_c = clone (&threadPedestre, (char*) stack +FIBER_STACK,SIGCHLD|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_VM,0);
pid_c=waitpid (pid_c,0,0);
pid_a=clone(&threadCarros, (char*) stack + FIBER_STACK, SIGCHLD|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_VM,0);
pid_a=waitpid(pid_a,0,0);
free(stack);
return 0;
}




