#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#define  KEY 0xF

int main()
{
	  //create a shared memory
	  int shmid = shmget(KEY , 100,IPC_CREAT | 0666);
     
	  //check any error in creating shared memory
	  if(shmid == -1)
	  {
			perror("shmget");
			return -1;
	  }

	  //attach the calling process to shared memory
	  int * ptr = shmat(shmid, NULL, 0);

	  //check any errror in the shmat
	  if(ptr == (void *)-1)
	  {
            perror("shmat");
			return -1;
	  }

	  //write to shared memory
	  *ptr = 100;
      printf("writing operation is succesfull");
	  //deattach the calling process from shared memory
	  shmdt(ptr);
	  return 0;
}

