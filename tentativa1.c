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


int threadCarro(void *argument){
while(turn==0){
printf("Carros passam\n");
}
}

int threadPedestre (void* argumento){
while (turn!=1){
printf("Pedestres atravessam");
}
}

int main(){
void * stack;
pid_t pid_c;
pid_t pid_a;
stack=malloc (FIBER_STACK);
pid_c=clone (&threadCarro, (char*) stack + FIBER_STACK, SIGCHLD|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_VM,0);
pid_a =clone (&threadPedestre, (char*) stack + FIBER_STACK, SIGCHLD|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_VM,0);
free(stack);
return 0;
}

