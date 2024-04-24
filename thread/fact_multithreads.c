/*

Name: Amrita N S
Date: 10-02-2024
Description: WAP to print the factorial of a given number using multithreads

Pre-requisites:

Knowledge about multi-thread process, How to read and understand ‘man pages’. 
Good knowledge about pthread library functions. 

Objective: 
 • To understand working and flow of multithread programs.

Requirements: 

1. Modify the factorial template code using multiple threads. 
2. Create at-least 3 threads and share the work among threads equally . 
3. Create and join threads using separate loops . 
4. You may have to change the argument structure. 
5. Declare all integer variables as unsigned long int (For max values). 

*/

#include <stdio.h>
#include <pthread.h>

//Define a structure to hold information about each thread's task
struct fact 
{
    // Starting number for factorial calculation
    int start;

	// Stopping number for factorial calculation
    int stop;

    // Result of factorial calculation
    long int result;
};

// Thread function to calculate factorial
void *thread_fun(void *arg) 
{
    struct fact *ptr = (struct fact *)arg;

    // Initialize f with the starting number
    int f = ptr->start;

	/// Initialize f1 with the starting number
    long int f1 = f;    
    while (f != (ptr->stop)) 
	{
		// Calculate factorial iteratively
        f1 = f1 * (--f); 
    }
    // Store the result in the structure
    ptr->result = f1; 
    return NULL;
}

int main() 
{
    // structure variable array to hold information for each thread
    struct fact var[3];
    int num, n, i, j = 0;

    // Array to hold thread IDs
    pthread_t tid[3];  

    printf("Enter the number: ");
    scanf("%d", &num);

    // Divide the input number into three equal parts	
    n = (num / 3); 

    // Determine the tasks for each thread based on the input number
    if (num <= 2) 
	{
        // If the input number is less than or equal to 2
        for (i = 0; i < num; i++) 
		{
            var[j].start = (num - i);
            var[j].stop = ((num - i) - n);
            j++;
        }

        for (int k = num; k < 3; k++) 
		{
            var[j].start = 1;
            var[j].stop = 1;
            j++;
        }
    } 
	else if ((num % 3) != 0) 
	{
        // If the input number is not divisible by 3
        for (i = 0; i < (n * 3); i = (i + n)) 
		{
            var[j].start = (num - i);
            var[j].stop = ((num - i) - (n - 1));
            j++;
        }
        if (var[--j].stop != 1) 
		{
            var[2].stop = num - (n * 3);
        }
    } 
	else 
	{
        // If the input number is divisible by 3
        for (i = 0; i < num; i = (i + n)) 
		{
            var[j].start = (num - i);
            var[j].stop = ((num - i) - (n - 1));
            j++;
        }
    }

    // Create threads for each task and execute the thread function
    for (int k = 0; k < 3; k++) 
	{
        pthread_create(&tid[k], NULL, thread_fun, (void *)&var[k]);
    }

    // Wait for all threads to finish
    for (int p = 0; p < 3; p++) 
	{
        pthread_join(tid[p], NULL);
    }

    // Calculate the factorial by multiplying results from each thread
    // Print the factorial result
    printf("Factorial of %d is %ld\n", num, (var[0].result * var[1].result * var[2].result));

    return 0;
}
