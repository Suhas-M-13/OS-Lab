#include<stdio.h>
#include<stdlib.h>
typedef struct Process
{
	int id, at, bt, ct, tt, wt, over;
}Pro;

void display(Pro *p, int n)
{
	int att=0, awt=0;
	printf("ID\tAT\tBT\tCT\tTAT\tWT\n");
	for(int i=0;i<n;i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tt,p[i].wt);
		att+=p[i].tt;
		awt+=p[i].wt;
	}
	printf("Avg TAT = %.2f\nAvg WT = %.2f\n",(float)att/(float)n,(float)awt/(float)n);
}

int main()
{
	int n, i, j, k, ct=999, flag;
	printf("Enter number of processes: ");
	scanf("%d",&n);
	Pro *p;
	p=(Pro*)malloc(sizeof(Pro)*n);
	printf("Enter details of Process :\n");
	for(i=0;i<n;i++)
	{
		printf("P%d\n",i+1);
		p[i].id=i+1;
		printf("AT : ");
		scanf("%d",&p[i].at);
		printf("BT : ");
		scanf("%d",&p[i].bt);
		if(p[i].at<ct)
		ct=p[i].at;
		p[i].over=0;
	}
	Pro t;
	printf("Gantt Chart:\n");
	for(flag=0;flag<n;flag++)
	{
		printf("%d--",ct);
		k=0;
		for(i=0;i<n;i++)
		{
			if(p[i].at<=ct && p[i].over==0)
			{
				t.id=p[i].id;
				t.at=p[i].at;
				t.bt=p[i].bt;
				for(j=0;j<n;j++)
				{
					if(p[j].bt<t.bt && p[j].at<=ct && p[j].over==0)
					{
						t.id=p[j].id;
						t.at=p[j].at;
						t.bt=p[j].bt;
						k=1;
					}
				}
				if(k)
					break;
			}
		}
		ct+=t.bt;
		t.ct=ct;
		t.tt=t.ct-t.at;
		t.wt=t.tt-t.bt;
		t.over=1;
		printf("%d: P%d\n",ct,t.id);
		for(i=0;i<n;i++)
		{
			if(p[i].id==t.id)
				p[i]=t;
		}
	}
	display(p, n);
}