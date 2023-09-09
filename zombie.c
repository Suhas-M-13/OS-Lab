#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    pid_t mypid, parentpid, childpid;
    childpid=fork();
    if(childpid<0)
    {
        printf("Fork Failed...\nExiting\n");
        exit(0);
    }
    if(!childpid)
    {
        printf("[Child] This is Child Process\n");
        mypid=getpid();
        parentpid=getppid();
        printf("[Child] My PID = %d\n",mypid);
        printf("[Child] My Parent PID = %d\n",parentpid);
        printf("[Child] Exiting\n");
        exit(0);
    }
    else
    {
       printf("[Parent] This is Parent Process\n");
        mypid=getpid();
        parentpid=getppid();
        printf("[Parent] My PID = %d\n",mypid);
        printf("[Parent] My Parent PID = %d\n",parentpid); 
        printf("[Parent] Sleeping for 5 secs\n");
        sleep(5);
        printf("[Parent] Child PID = %d has ended, but it has an entry in process table.\nIt is a Zombie Process\n",childpid);
    }
return 0;
}