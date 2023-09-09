#include<stdio.h>
#include<stdlib.h>

struct process
{
    int id, at, bt,pr;
    int ct, tt, wt;
    int over;
    int rbt;
};

typedef struct process pros;

void display(pros *p, int n)
{
    int awt = 0, att = 0;
    printf("\n\nID\tAT\tBT\tPRI\tCT\tTT\tWT\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d \t%d \t%d \t%d \t%d \t%d \t%d\n", p[i].id, p[i].at, p[i].bt,p[i].pr, p[i].ct, p[i].tt, p[i].wt);
        awt = awt + p[i].wt;
        att = att + p[i].tt;
    }
    printf("Average Turnaround Time: %.4f\n", (float)(att / (float)n));
    printf("Average Waiting Time: %.4f\n", (float)(awt / (float)n));
}

void main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    pros *p;
    p = (pros*)malloc(sizeof(pros) * n);

    int ct = 999;

    printf("Enter the details of each process:\n");
    for(int i = 0; i < n; i++)
    {
        printf("Process - %d:\n", i + 1);
        p[i].id = i + 1;

        printf("AT: ");
        scanf("%d", &p[i].at);

        printf("BT: ");
        scanf("%d", &p[i].bt);

        printf("Priority: ");
        scanf("%d",&p[i].pr);

        p[i].over = 0;
        p[i].rbt = p[i].bt;
        
        if(p[i].at<ct)
        ct=p[i].at;
    }

    int flag = 0;

    printf("\nGantt Chart\n\n");
    while(flag != n)
    {
        int shortest = -1;
        int min_burst = 999;

        for(int i = 0; i < n; i++)
        {
            if(p[i].at <= ct && p[i].over == 0 && p[i].pr < min_burst)
            {
                shortest = i;
                min_burst = p[i].pr;
            }
        }

        if(shortest == -1)
        {
            ct++;
            continue;
        }

        printf("%d -- ", ct);
        ct++;

        p[shortest].rbt--;

        printf("%d : %d\n", ct, p[shortest].id);

        if(p[shortest].rbt == 0)
        {
            p[shortest].ct = ct;
            p[shortest].tt = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tt - p[shortest].bt;
            p[shortest].over = 1;
            flag++;
        }
    }

    display(p, n);
}