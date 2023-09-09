#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int fn[10], pat[10], temp[20];
    printf("Enter file name\n");
    scanf("%s",&fn);
    FILE *fp;
    printf("Enter Pattern\n");
    scanf("%s",&pat);
    fp=fopen(fn,"r");
    while(!feof(fp))
    {
        fgets(temp, 100, fp);
        if(strstr(temp, pat))
        printf("%s",temp);
    }
    fclose(fp);
}
