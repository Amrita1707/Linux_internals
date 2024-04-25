/*

Name: Amrita N S
Date: 13-02-2024
Description: WAP to sum and maximum of a given array using multiple threads.Synchronize threads using mutex.

Pre-requisites:

• Knowledge about multi-thread process, How to read and understand ‘man pages’. 
• Good knowledge about pthread library functions. 
• Thread synchronization (mutex and semaphores). 

Objective: 

• To understand need and implementation of thread synchronization. 

Requirements: 

1. Create an array[N] (min size 500) with 1 N values and two global variables → global_sum & global_max. 
2. Create multiple threads to find sum of array and maximum value in array. 
3. Threads will share array equally among them. Means each thread will access different part of array at same time. 
4. Create at-least 5 threads. Create and join threads using separate loops. 
5. Each thread will update global_sum and global_max. 
6. Since we are accessing global variable from threads, do proper synchronization using mutex.

*/

#include <stdio.h>
#include <pthread.h>

// Declare global variables max and sum, initialized to 0.
int max=0,sum=0;

// Declare a mutex lock for thread synchronization.
pthread_mutex_t lock;

// Define the thread function
void * thread_fun(void *arg) 
{
    // Lock the mutex to ensure exclusive access to shared resources.
    pthread_mutex_lock( &lock);

    // Cast the argument to an integer pointer and dereference it to get the value of n.
    int n = *(int *)arg;

    // Initialize local variables n1 to 1 and n2 to the global variable max.
    int n1=1,n2=max;

    // Execute the loop while n1 is less than or equal to n.
    while(n1<=n) 
	{
        // Increment n2 and add it to sum.
        sum = sum + (++n2) ;

        // Check if n2 is greater than max.
        if(max < n2)
            // Update max if n2 is greater.
            max = n2;

        n1++;
    }

    // Unlock the mutex to release the lock on shared resources.
    pthread_mutex_unlock(&lock);

    // Return NULL to indicate successful thread execution.
    return NULL;
}


int main() 
{
    int n,i,k,n1;

    // Declare an array of thread IDs.
    pthread_t tid[4];

  
    printf("Enter the size of the array\n");
    // Read the size of the array from the user.
    scanf("%d",&n);

    // Calculate the division factor for distributing workload among threads.
    int div = ( n/5);

    // Initialize the mutex lock.
    pthread_mutex_init( &lock, NULL);

    // Calculate the remaining workload for the last thread if the division factor is not zero.
    if(div != 0) 
	{
        n1 = n - (div*4);
    }

    // Create threads and pass the division factor as an argument if the division factor is zero.
    if(div==0) 
	{
        for(i=0; i<5; i++)
	   	{
            pthread_create( &tid[i], NULL, thread_fun , (void *)&div);
        }
    }

    // Create threads and pass the division factor as an argument for the first four threads
    // and pass the remaining workload as an argument for the last thread if the division factor is not zero.
    else if(div !=0) 
	{
        for(i=0; i<4; i++) 
		{
            pthread_create( &tid[i], NULL, thread_fun , (void *)&div);
        }
        pthread_create( &tid[4], NULL, thread_fun , (void *)&n1);
    }

    // Wait for each thread to finish execution.
    for(k=0; k<5; k++) 
	{
        pthread_join(tid[k],NULL);
    }

    // Print the maximum value and sum calculated by the threads.
    printf("max = %d\nsum = %d\n",max,sum);
	
    return 0;
}
