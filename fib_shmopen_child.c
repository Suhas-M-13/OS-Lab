#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<string.h>
void main(int arg,char *argv[])
{
int a=0,b=1,c,i,k=2,fd;
void *ptr;
fd=shm_open("OS",O_CREAT|O_RDWR,0666);
ftruncate(fd,4096);
ptr=mmap(0,4096,PROT_WRITE,MAP_SHARED,fd,0);
i=atoi(argv[1]);
printf("\nChild Printing:\n");
for(int j=0;j<i;j++)
    {
        sprintf(ptr, "%d\t", a);
        ptr+=strlen(ptr);
        printf("%d\t",a);
        c=a+b;
        a=b;
        b=c;
    }
}