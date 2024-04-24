/*
Name: Amrita N S
Date: 08-02-2024
Description: print the address which is causing Segmentation fault

Pre-requisites:

Knowledge about system calls, How to read and understand ‘man pages’.
Good knowledge about signals and signal handling.
Working of sigaction system calls. 
Objective: 

• To understand working of signal handling. 

Requirements: 

Write a signal handler function to print address which caused seg-fault(SIGSEGV). 
Use sigaction system call to register signal. 
Use struct siginfo from sa_sigaction to print address (Read man page). 
Create a segmentation fault from code. 
When error occurs program should print address and exit. 
Sample execution: 

 ./sigsegv 

Segmentation fault ..!! 

Address 0x123456 caused error
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

// Define signal handler function
void sigaction_handler(int signum, siginfo_t *info, void *dummy)
{
      // Print the address that caused the erro
	  printf("Address %p caused error\n",info->si_addr);
	  exit(0);
}

int main()
{
	  // Define a struct for signal action
	  struct sigaction act;

   	  // Set the flag to use extended signal handling 
	  act.sa_flags = SA_SIGINFO;

	  // Set the signal handler function
	  act.sa_sigaction = sigaction_handler;

      // Assign the signal handler for SIGSEGV (Segmentation Fault)
	  sigaction(SIGSEGV, &act,NULL);

	  // Create a pointer initialized with an invalid memory address (for demonstration)
	  int *ptr = (int *) 0xA;

	  // Attempt to dereference the invalid pointer
	  *ptr = 10;
}

