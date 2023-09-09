#include<stdio.h>
#include<stdlib.h>
typedef struct process
{
    int id, at, bt, ct, tt, wt;
}pro;
int stt=0, swt=0, i, j;
void swap(pro *p, pro *q)
{
    pro t;
    t=*p;
    *p=*q;
    *q=t;
}
void sort(pro *p, int n)
{
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(p[i].at>p[j].at)
                swap(&p[i], &p[j]);
        }
    }
}
void newsort(pro *p, int n)
{
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(p[i].id>p[j].id)
                swap(&p[i], &p[j]);
        }
    }
}

void main()
{
    int n,ct=999;
    printf("Enter number of process\n");
    scanf("%d",&n);
    pro p[n];
    for(i=0;i<n;i++)
    {
        p[i].id=i+1;
        printf("Enter P%d AT :",i+1);
        scanf("%d",&p[i].at);
        printf("Enter P%d BT :",i+1);
        scanf("%d",&p[i].bt);
        if(p[i].at<ct)
        ct=p[i].at;
    }
    sort(p,n);
    printf("Gantt Chart:\n");
    for(i=0;i<n;i++)
    {
        printf("P%d: %d-->",p[i].id,ct);
        ct+=p[i].bt;
        p[i].ct=ct;
        printf("%d\n",p[i].ct);
        p[i].tt=p[i].ct-p[i].at;
        p[i].wt=p[i].tt-p[i].bt;
        stt+=p[i].tt;
        swt+=p[i].wt;
    newsort(p,n);
    printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tt,p[i].wt);
    }
    printf("Avg TAT=%.2f\nAvg WT=%.2f\n",(float)stt/(float)n,(float)swt/(float)n);
}
}