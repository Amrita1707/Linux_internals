#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#define  KEY 0xF

int main()
{
	  // cretae the shared memory segment
	  int shmid = shmget(KEY, 100, 0);
   
	  // check creation  was successful
	  if(shmid == -1)
	  {
			perror("shmget");
			return -1;
	  }

	  // attech the calling process to shared memory
	  int *ptr = shmat(shmid, NULL, 0);

	  // check any error in the shmat
	  if(ptr  == (void *)-1)
	  {
			perror("shmat");
			return -1;
	  }

      //Print the data stored in shared memory 
	  printf("Data from shm is %d\n",*ptr);
      
	  // Detach the calling process from the shared memory segment
	  shmdt(ptr);

	  // Remove the shared memory segment
	  shmctl(shmid, IPC_RMID, NULL);
	  return 0;
}

