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

int main(int argc, char* argv[])
{
    int a=0, b=1, c, i;
    int shmid;
    void *ptr;
    shmid=shmget((key_t)1122, 4096, 0666);
    ptr=shmat(shmid, NULL, 0666);
    printf("Child Printing : ");
    i=atoi(argv[1]);
    for(int j=0;j<i;j++)
    {
        sprintf(ptr, "%d\t", a);
        ptr+=strlen(ptr);
        printf("%d\t",a);
        c=a+b;
        a=b;
        b=c;
    }
    shmctl(shmid, IPC_RMID, NULL);
}