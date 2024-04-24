/*
Name: Amrita N S
Date: 09-02-2024
Descripton: Program to block certain signals from being received from command line. 

Requirements: 

1. Write a signal handler function for any signal, say SIGINT .
2. While its running inside handler (use loop) block other signals(atleast 3) being received . 
3. Use sa_mask from struct sigaction to set signals to be blocked (Refer man ). 
4. To create a signal set use variable of sigset_t. 
5. To add or remove signals from set use sigaddset, sigdelset functions (refer man). 
6. Process will receive blocked signals once its out from handler. ﻿

Sample execution: 

 1. ./block_signal
      Process 2345 waiting for signal.. press ctrl + c from terminal. 
      SIGINT received  
Inside handler 
Inside handler 
. .
.....

2. Now open another terminal and send signal to process using kill command. 
Bash$ kill ­SIGUSR1 2345 
Bash$ kill ­SIGTERM 2345 
Bash$ kill ­SIGABRT 2345 

3. After exiting from handler will respond to blocked signal.
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

pid_t pid;
// Define signal handler function
void signal_handler(int signum, siginfo_t *info, void *dummy) 
{

    printf("Process %d waiting for signal\n",pid);
	
    // Counter for demonstrating signal handling duration
    int i = 10;

    // Loop to print the received signal number
    while (--i) 
	{
        // Print the received signal number inside the handler
        printf("%d is received inside handler\n", signum);

        // Wait for 1 second (for demonstration)
        sleep(1);
    }
}

int main()
{

    // process ID (PID) of the current process
    pid = getpid();

	// Define a struct for signal action
    struct sigaction act;

    // Set the flag to use extended signal handling
    act.sa_flags = SA_SIGINFO;

    // Set the signal handler function
    act.sa_sigaction = signal_handler;

    // Initialize the signal mask to an empty set
    sigemptyset(&(act.sa_mask));

    // Add SIGTSTP, SIGSEGV, and SIGCONT signals to the signal mask
    sigaddset(&(act.sa_mask), SIGTSTP);
    sigaddset(&(act.sa_mask), SIGSEGV);
    sigaddset(&(act.sa_mask), SIGCONT);

    // Assign the signal handler for SIGINT, SIGTSTP, SIGSEGV, and SIGCONT
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTSTP, &act, NULL);
    sigaction(SIGSEGV, &act, NULL);
    sigaction(SIGCONT, &act, NULL);
    
    // Infinite loop to keep the program running
    while (1) 
	{
        // Print a message to indicate the main loop
        printf("Inside main\n");

        // Wait for 1 second (for demonstration)
        sleep(1);
    }
}
