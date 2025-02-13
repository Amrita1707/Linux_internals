#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#define  KEY 0xF

int main()
{
	  char str[30];
	  int i;
	  printf("Enter a string\n");
	  scanf("%s",str);

	  //create a shared memory
	  int shmid = shmget(KEY , 100,IPC_CREAT | 0664);
     
	  //check any error in creating shared memory
	  if(shmid == -1)
	  {
			perror("shmget");
			return -1;
	  }

	  //attach the calling process to shared memory
	  char * ptr = shmat(shmid, NULL, 0);

	  //check any errror in the shmat
	  if(ptr == (void *)-1)
	  {
            perror("shmat");
			return -1;
	  }

	  //write to shared memory
	  for(i=0; str[i] !='\0'; i++)
	  {
	     if(str[i] >= 'a' || str[i] <= 'z')
	         str[i] = (str[i]-32);
	  }
	  ptr= str;
	 
	  printf("entered data is %s\n", ptr);
	  
      printf("writing operation is succesfull\n");
	  //deattach the calling process from shared memory
//	  shmdt(ptr);
	  return 0;
}

