#include<stdio.h>
typedef struct{
	int at,bt,ct,tt,wt,rt,st,id;
	}process;
process p[10];
void main(){
	int n,i;
	printf("Enter number of process:");
	scanf("%d",&n);
	float att=0,awt=0,art=0;
	int curtime=0;
	int com[n],completed=0;
	int minindex=-1,minimum=99999;
	for(i=0;i<n;i++){
		printf("Process-%d\n",i+1);
		printf("Enter the arrival time: ");
		scanf("%d",&p[i].at);
		printf("Enter the burst time: ");
		scanf("%d",&p[i].bt);
		p[i].id=i+1;
		com[i]=0;
	}
	while(completed!=n){
		minindex=-1;
		minimum=99999;
		for(i=0;i<n;i++){
			if(p[i].at<=curtime&&com[i]==0){
				if(p[i].bt<minimum){
					minindex=i;
					minimum=p[i].bt;
					}
				if(p[i].bt==minimum){
					if(p[i].at<p[minindex].at){
						minindex=i;
						minimum=p[i].bt;
						}
					}
				}
			}
		if(minindex!=-1){
			p[minindex].st=curtime;
			p[minindex].ct=curtime+p[minindex].bt;
			p[minindex].tt=p[minindex].ct-p[minindex].at;
			p[minindex].wt=p[minindex].tt-p[minindex].bt;
			att+=p[minindex].tt;
			awt+=p[minindex].wt;
			art+=p[minindex].rt;
			printf("%d to %d :",curtime,p[minindex].ct);
			printf("%d\n",p[minindex].id);
			curtime=p[minindex].ct;
			com[minindex]=1;
			completed++;
			}
		else{
			printf("%d to %d :",curtime,curtime+1);
			printf("IDEAL\n");
			curtime++;
			}
			
	
	}
}