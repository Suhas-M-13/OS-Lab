#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/mman.h>
void main(int arg,char *argv[])
{
int fd,i;
void *ptr;
pid_t pid;

if(arg>1)
{
sscanf(argv[1],"%d",&i);
if(i<1)
{
printf("Error input!!\n");
exit(0);
}
}
else
{
printf("Insufficient arguement passed\n");
exit(0);
}
pid=fork();
if(pid==0)
{
execlp("./fib_shmopen_child","fib_shmopen_child",argv[1],NULL);
}
else if(pid>0)
{
wait(NULL);
printf("\nParent:Child completed\n");
fd=shm_open("OS",O_RDONLY,0666);
ptr=mmap(0,4096,PROT_READ,MAP_SHARED,fd,0);
printf("Parent printing:\n");
printf("%s\n",(char*)ptr);
shm_unlink("OS");
}
}