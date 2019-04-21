// Starting with file hello-hw.txt, write a program that uses threads that print a string,their own task id and the value of a variable sum. The task id, value of sum and string address must be passed to the string through pthread_create(). Do not change the code in hello-hw.txt but only add statements. Some of the places where new code must be added are shown by 


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#define NUM_THREADS 8


typedef struct arg_struct{
    int taskid; 
    int sum; 
    char* hello_msg; 
} arg_struct; 

char *messages[NUM_THREADS];


// The thread to do the work 
void *PrintHello(void *threadarg){
     int taskid, sum;
     char *hello_msg;
     struct arg_struct * arg; 


     arg = (struct arg_struct * ) threadarg; 
     taskid = arg->taskid; 
     sum = arg->sum;
     hello_msg = arg->hello_msg; 

    //  printf("taskid %d", task_id); 
   
     

    printf("The ID of this thread is: %u\n", (unsigned int)pthread_self()); 
     printf("Thread %d %s Sum=%d\n", taskid, hello_msg, sum);
     pthread_exit(NULL);
    }


   int main(int argc, char *argv[])
    {
     pthread_t threads[NUM_THREADS];
     int rc, t, sum;
     sum = 0;
     messages[0] = "Hello-0";
     messages[1] = "Hello-1";
     messages[2] = "Hello-2";
     messages[3] = "Hello-3";
     messages[4] = "Hello-4";
     messages[5] = "Hello-5";
     messages[6] = "Hello-6";
     messages[7] = "Hello-7";

     // Loop through number of threads here 
     for(t = 0; t < NUM_THREADS; t++)
     {
       sum = sum + t;
       char *helloWorld = "Hello"; 
       
       // Create a struct arg that holds all the argument 
       arg_struct *args = malloc(sizeof *args); 
       args->taskid = t; 
       args->sum = sum;
       args->hello_msg = helloWorld; 


       printf("Creating thread %d\n", t);
       
        if(pthread_create(&threads[t], NULL, PrintHello, args)) {
            free(args);
        }

      }

     pthread_exit(NULL);
    } 
