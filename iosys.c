#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    int n, fd;
    char buffer[30];
    fd=open("sample.txt", O_RDWR);
    printf("File Descriptor is %d\n",fd);
    printf("Reading 10 characters\n");
    n=read(fd, buffer, 10);
    write(1, buffer, n);
    printf("\nSkipping 5 chars from current position\n");
    lseek(fd, 5, SEEK_CUR);
    n=read(fd, buffer, 10);
    write(1, buffer, n);
    printf("\nGoint to 5th last character in file\n");
    lseek(fd, -5, SEEK_END);
    n=read(fd, buffer, 10);
    write(1, buffer, n);
    printf("\nGoing to 3rd charecter in file\n");
    lseek(fd, 3, SEEK_SET);
    n=read(fd, buffer, 10);
    write(1, buffer, n);
return 0;
}