#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<sys/types.h>

int main(int argc, char *argv[])
{
    int i, shmid;
    pid_t pid;
    void *ptr;
    shmid=shmget((key_t)1122, 4096, 0666|IPC_CREAT);
    ptr=shmat(shmid, NULL, 0666);
    if(argc<1)
    {
        printf("Error\n");
        exit(0);
    }
    if(argc>1)
    {
        sscanf(argv[1],"%d\t",&i);
    }
    pid=fork();
    if(pid==0)
    {
        execlp("./fib_shmget_child","fib",argv[1],NULL);
    }
    else
    {
        wait(NULL);
        printf("Child Completed\n");
        printf("Parent Printing: ");
        printf("%s",(char *)ptr);
        shmdt(ptr);
    }
    return 0;
}