//orphans process
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
    pid_t mypid, parentpid, childpid;
    childpid=fork();
    if(childpid==0)
    {
        printf("[Child] This is Child Process\n");
        mypid=getpid();
        parentpid=getppid();
        printf("[Child] My PID = %d\n",mypid);
        printf("[Child] My Parent PID = %d\n",parentpid);
        printf("[Child] Sleeping for 2 secs\n");
        sleep(2);
        printf("[Child] My Parent Ended. So I am an Orphan Process adopted by Init Process.\n");
    }
    else
    {
        printf("[Parent] This is Parent Process\n");
        mypid=getpid();
        parentpid=getppid();
        printf("[Parent] My PID = %d\n",mypid);
        printf("[Parent] My Parent PID = %d\n",parentpid);
        printf("[Parent] Parent process exiting\n");
        exit(0);
    }
return 0;
}