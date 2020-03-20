#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  
#include <pthread.h> 

// A normal C function that is executed as a thread 
// when its name is specified in pthread_create() 
void *myThreadFun(void *vargp) 
{ 
	int max;
    //get max number of primes
    printf("Enter max prime number: ");
    scanf("%d",&max);
    //incremental loop to max prime estimte provided
    for (int number = 2; number < max; number++) {
        int isPrime = 1;
        //check divisibility
        for (int divisor = 2; divisor < number; divisor++)
            if ((number % divisor) == 0)
                isPrime = 0;

        if (isPrime == 1)
            printf("%d ", number);
    }

   return 0;
} 

int main() 
{ 
	pthread_t thread_id; 
	printf("Thread Created....\n\n"); 
	pthread_create(&thread_id, NULL, myThreadFun, NULL); 
	pthread_join(thread_id, NULL); 
	printf("\n\nThread Finished.\n"); 
	exit(0); 
}
