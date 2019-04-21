#include "csapp.h"
#include "csapp.c"
void *thread(void *vargp); 

int main(int argc, char* argvs[])
{

    if (argc != 2){
        printf("Please input the number of threads to run, e.g ./12-16 <number_of_threads> \n"); 
        exit(0); 
    }

    int N = atoi(argvs[1]); 

    pthread_t tid; 
    for (int i = 0; i < N; i++){
        Pthread_create(&tid, NULL, thread, NULL); 
     }
    // We do not need to call Pthread_join since detached threads
    // are automatically repaed on termination 
    Pthread_exit(NULL); 
    exit(0);
            
}


void *thread(void *vargp) /* Thread routine */ 
{
    printf("Helo World!\n"); 
    return NULL; 
}
