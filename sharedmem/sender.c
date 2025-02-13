/*
Name :Amrita
Date : 10-02-2024
Description : Implement communication between two different processes using SHM
*/
#include <stdlib.h>
#include <string.h>
 #include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
   //#define  KEY 0xF
#define SMSIZE 100

int main()
{
    //variable declaration
    int shmid,shmid1,i,len;
    char str[100];
    void *shm,*shm1;
    key_t key,key1;

    //key can be read/write
    key = 'A';

    //create a shared memory
    shmid = shmget(key, SMSIZE,IPC_CREAT | 0664);

    if(shmid < 0)
    {
        perror("shmget");
        exit(1);
    }
   
      shm = shmat(shmid,NULL,0);

        //read string from user
        printf("Enter the string : ");
        scanf("%s",str);

        //to change string lower case to upper case letter
        for(i = 0 ; str[i] != '\0' ; i++)
        {
            if(str[i] >= 'a' && str[i] <= 'z')
            {
                str[i] = str[i] - 32;
            }
		}
        printf("Send the string to Receiver...successfully = %s\n",str);
        //write into shared memory
        strcpy(shm,str);
}
/* 
int main()
{
    //variable declaration
    int shmid,shmid1,i,len;
    char str[100];
    void *shm,*shm1;
    key_t key,key1;

    //key can be read/write

    if(shmid < 0)
    {
        perror("shmget");
        exit(1);
    }
   
      shm = shmat(shmid,NULL,0);


        //to change string lower case to upper case letter
        for(i = 0 ; str[i] != '\0' ; i++)
    //key can be read/write
    key1 = 'B';

    //create a chared memory
    shmid1 = shmget(key1, SMSIZE,IPC_CREAT | 0666);

    if(shmid1 < 0)
    {
        perror("shmget");
        exit(1);
    }
    //attach the shared memory
    shm1 = shmat(shmid1,NULL,0);
    if(shm1 < 0)
    {
        perror("shmat");
        exit(1);
    }
    else
    {         
        printf("Received the Reverse string value from receiver..successfully\n");
        printf("%s\n",(char*)shm1);
    }
    return 0;
}*/
