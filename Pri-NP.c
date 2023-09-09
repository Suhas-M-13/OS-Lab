#include<stdio.h>
#include<stdlib.h>
struct process 
{
int id,at,bt,pr;
int ct,tt,wt;
int over;
};
typedef struct process pros;

void display(pros *p,int n)
{
int awt=0,att=0;
printf("\n\nID \tAT \tBT \tPR \tCT \tTT \tWT \n");
for(int i=0;i<n;i++)
{
awt=awt+p[i].wt;
att=att+p[i].tt;
printf("%d \t%d \t%d \t%d \t%d \t%d \t%d\n",p[i].id,p[i].at,p[i].bt,p[i].pr,p[i].ct,p[i].tt,p[i].wt);
}
printf("\nAverage Turn Around Time: %.4f\n",(att/(float)n));
printf("\nAverage Waiting Time: %.4f\n",(awt/(float)n));
}


void main()
{
int n;
printf("Enter the number of processes: ");
scanf("%d",&n);
pros *p;
p=(pros*)malloc(sizeof(pros)*n);
printf("Enter the details of ");
int ct=999,flag=0;
int i,j;
for(i=0;i<n;i++)
{
printf("Process - %d :\n",i+1);
p[i].id=i+1;
printf("AT: ");
scanf("%d",&p[i].at);
printf("BT: ");
scanf("%d",&p[i].bt);
p[i].over=0;
printf("Priority: ");
scanf("%d",&p[i].pr);
if(p[i].at<ct)
ct=p[i].at;
}
int k=0;
printf("\nGantt Chart\n\n");
for(flag=0;flag<n;flag++)
{
pros t;
k=0;
printf("%d -- ",ct);
for(i=0;i<n;i++)
{
	if((p[i].at<=ct)&&(p[i].over==0))
	{
		t.at=p[i].at;
		t.id=p[i].id;
		t.bt=p[i].bt;
		t.pr=p[i].pr;
		for(j=0;j<n;j++)
		{
		 if((p[j].pr<t.pr)&&(p[j].at<=ct)&&(p[j].over==0))
			{	t.bt=p[j].bt;
				t.id=p[j].id;
				t.at=p[j].at;
				t.pr=p[j].pr;
				k=1;
			}
		}
		if(k==1)
		break;
	}
	
}
ct=ct+t.bt;
t.ct=ct;
t.tt=t.ct-t.at;
t.wt=t.tt-t.bt;
t.over=1;
printf("%d : %d\n",ct,t.id);
for(i=0;i<n;i++)
{
	if(p[i].id==t.id)
		p[i]=t;
}
}
display(p,n);
}