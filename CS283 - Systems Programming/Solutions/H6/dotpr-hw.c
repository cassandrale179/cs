#include <pthread.h>
#include <stdio.h> 
#include <stdlib.h> 
#define NUMTHRDS 4
#define VECLEN 100000

// Global variables here 
pthread_t callThd[NUMTHRDS];
double *array_a;
double *array_b;
double big_sum;
int veclen;
pthread_mutex_t mutexsum; 


// Calculate the dot product here 
void *dotprod(void *arg){

    // Declare local variables 
    double *x; 
    double *y; 
    double mysum; 
    int i, start, end; 

    // Set local variable to global varaibles 
    x = array_a; 
    y = array_b; 
    mysum = 0; 

    // Initialize start and end point for calculations 
    long offset; 
    int l = veclen; 
    offset = (long) arg; 
    start = offset * l; 
    end = start + l; 

    // Calculating sum 
    for (i = start; i < end; i++){
        mysum  += (x[i] * y[i]); 
    }


    // Create a lock before adding current sum to global sum 
    // In case a thread isn't finished calculating local sum 
    pthread_mutex_lock(&mutexsum); 
    big_sum += mysum; 
    pthread_mutex_unlock (&mutexsum); 


    return NULL; 
}

// Main function 
int main (int argc, char *argv[]){

    // Local variables declared here 
    long i;
    double *a, *b;
    void *status;

   // Allocate memory for a and b 
   a = (double*) malloc (NUMTHRDS*VECLEN*sizeof(double));
   b = (double*) malloc (NUMTHRDS*VECLEN*sizeof(double));
   for (i=0; i<VECLEN*NUMTHRDS; i++){
       a[i]=1;
       b[i]=a[i];
    }
     
   veclen = VECLEN;
   array_a = a;
   array_b = b;
   big_sum = 0;

   // Initialize the lock
   pthread_mutex_init(&mutexsum, NULL); 

   // Create a thread to calculate the sum 
   for(i=0;i<NUMTHRDS;i++){
     pthread_create(&callThd[i], NULL, dotprod, NULL);  
   }


    // Wait on the other threads 
   for(i=0;i<NUMTHRDS;i++) {
      pthread_join(callThd[i], &status);
    } 

    // Output the sum and free memory 
     printf ("Sum = %f \n", big_sum);
     free (a);
     free (b);
     pthread_mutex_destroy(&mutexsum);
     pthread_exit(NULL); 
}
