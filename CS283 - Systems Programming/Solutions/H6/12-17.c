#include "csapp.h"
#include "csapp.c"

void *thread(void *vargp); 


int main(){
    pthread_t tid;
    Pthread_create(&tid, NULL, thread, NULL); 

    // Join thread here so that it will wait
    // for the thread to finish execution 
    Pthread_join(tid, NULL); 
    exit(0); 
}


// Thread routine 
void *thread(void *vargp){
    Sleep(1); 
    printf("Hello, world!\n"); 
    return NULL; 
}
