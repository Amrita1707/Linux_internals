#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
//#define  KEY 0xF
#define SMSIZE 100
int main()
{
	  key_t key;
	  key = 'A';
	  // cretae the shared memory segment
	  int shmid = shmget(key, SMSIZE,IPC_CREAT | 0664);
   
	  // check creation  was successful
	  if(shmid == -1)
	  {
			perror("shmget");
			return -1;
	  }

	  // attech the calling process to shared memory
	  char * ptr = shmat(shmid,NULL, 0);

	  // check any error in the shmat
	  if( ptr  == (void *)-1)
	  {
			perror("shmat");
			return -1;
	  }

	  printf("Date from shm is ");
      //Print the data stored in shared memory 
	  printf("%s\n",(char*)ptr);

      
	  // Detach the calling process from the shared memory segment
	  shmdt(ptr);

	  // Remove the shared memory segment
	  shmctl(shmid, IPC_RMID, NULL);
	  return 0;
}

