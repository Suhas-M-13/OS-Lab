#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>
int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;
    if(argc<2)
    {
        printf("You are not passing directory\n");
        exit(0);
    }
    if((dp=opendir(argv[1]))==NULL)
    {
        printf("Cannot open, it doesn't exist\n");
        exit(0);
    }
    while((dirp=readdir(dp))!=NULL)
    printf("%s\n",dirp->d_name);
    closedir(dp);
return 0;
}