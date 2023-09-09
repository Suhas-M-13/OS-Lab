#include<stdio.h>
#include<stdlib.h>

struct process 
{
    int id, at, bt;
    int ct, tt, wt;
    int over;
    int dbt;
};

typedef struct process pros;

int q[50], f = -1, r = -1;

void enqueue(int i)
{
    if (r == 49)
    {
        printf("Queue is full");
        exit(0);
    }
    if (f == -1)
        f = 0;
    //r++;
    q[++r] = i;
}

int dequeue()
{
    if (f == -1 || f > r)
    {
        printf("No process to execute");
        exit(0);
    }
    // int temp = q[f];
    // f++;
    return q[f++];
}

void sort(pros *p, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                pros t = p[i];
                p[i] = p[j];
                p[j] = t;
            }
        }
    }
}

void display(pros *p, int n)
{
    int awt = 0, att = 0;
    printf("\n\nID \tAT \tBT \tCT \tTT \tWT \n");
    for (int i = 0; i < n; i++)
    {
        awt += p[i].wt;
        att += p[i].tt;
        printf("%d \t%d \t%d \t%d \t%d \t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tt, p[i].wt);
    }
    printf("\nAverage Turn Around Time: %.4f\n", (att / (float)n));
    printf("\nAverage Waiting Time: %.4f\n", (awt / (float)n));
}

int isinqueue(int i)
{
    for (int j = f; j <= r; j++)
    {
        if (q[j] == i)
            return 1;
    }
    return 0;
}

int main()
{
    int n, ct=999;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    pros *p;
    p = (pros *)malloc(sizeof(pros) * n);

    printf("Enter the details of processes:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process - %d:\n", i + 1);
        p[i].id = i + 1;
        printf("AT: ");
        scanf("%d", &p[i].at);
        printf("BT: ");
        scanf("%d", &p[i].bt);
        p[i].over = 0;
        p[i].dbt = p[i].bt;
        if(p[i].at<ct)
        ct=p[i].at;
    }

    int tq;
    printf("Enter the Time Quantum: ");
    scanf("%d", &tq);

    sort(p, n);//at

    int flag = 0, min = 0;
    enqueue(0);

    while (flag != n)
    {
        printf("%d-->",ct);
        min = dequeue();

        if (p[min].dbt <= tq)
        {
            ct += p[min].dbt;
            p[min].ct = ct;
            p[min].dbt = 0;
            p[min].tt = p[min].ct - p[min].at;
            p[min].wt = p[min].tt - p[min].bt;
            p[min].over = 1;
            flag++;
        }
        else
        {
            ct += tq;
            p[min].dbt -= tq;
        }
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= ct && p[i].over == 0 && !isinqueue(i) && i != min)
            {
                enqueue(i);
            }
        }
	    if(!isinqueue(min) && !p[min].over)
	        enqueue(min);
        printf("%d : P%d\n",ct,p[min].id);   
    }

    display(p, n);

    return 0;
}