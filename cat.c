#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
    char ch;
    FILE *f1, *f2;
    if(argc<2)
    {
        printf("Error\n");
        exit(0);
    }
    if(argc>2)
    {
        f1=fopen(argv[1],"r");
        f2=fopen(argv[2],"a");
    }
    if(f1==NULL)
    {
        printf("Error in opening File\n");
        exit(0);
    }
    while((ch=fgetc(f1))!=EOF)
    {
        fprintf(f2,"%c",ch);
    }
    fclose(f1);
    fclose(f2);
return 0;
}