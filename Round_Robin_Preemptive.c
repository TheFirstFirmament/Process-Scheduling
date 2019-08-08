#include<stdio.h>
#include<stdlib.h>
#define TEMP 50
int pnum,pburst[TEMP],visit[TEMP],iloop,tempburst[TEMP],wait[TEMP],max=0,arrival[TEMP],choose=0,gantt_num[TEMP],jloop,total_arr,quantum,gantt[TEMP],process_wait[TEMP],process_tat[TEMP],pos=0,proname[TEMP];
float avg_wait,avg_tat,total_wait,total_tat;
void initialise()
{
	for(iloop=0;iloop<50;iloop++)
	{
        arrival[iloop]=0;
        gantt[iloop]=0;
        gantt_num[iloop]=0;
        proname[iloop]=iloop+1;
	visit[iloop]=0;
    	}
}
void input_arrival()
{
	for(iloop=0;iloop<pnum;iloop++)
	{
		printf("\nEnter arrival time for Process %d:\t",(iloop+1));
		scanf("%d",&arrival[iloop]);
	}
}
void input()
{
	printf("\nEnter number of process: ");
	scanf("%d",&pnum);
	for(iloop=0;iloop<pnum;iloop++)
	{
		printf("\nEnter burst for Process %d:\t",(iloop+1));
		scanf("%d",&pburst[iloop]);
		tempburst[iloop]=pburst[iloop];
		if(pburst[iloop]>max)
		max=pburst[iloop];
	}
	printf("Enter 1 if the processes has different arrival times, any number else otherwise: ");
	scanf("%d",&choose);
	if(choose==1)
	input_arrival();
	printf("\nEnter time quantum for round robin scheduling:\t");
	scanf("%d",&quantum);
}
void sort_arrival()
{
    int temp=0;
    if(choose==1)
    {
        for(iloop=0;iloop<pnum-1;iloop++)
        {
            for(jloop=iloop+1;jloop<pnum;jloop++)
            {
                if(arrival[iloop]>arrival[jloop])
                {
                    //Swapping arrival time
                    temp=arrival[iloop];
                    arrival[iloop]=arrival[jloop];
                    arrival[jloop]=temp;
                    //Swapping the process numbers                    
                    temp=proname[iloop];
                    proname[iloop]=proname[jloop];
                    proname[jloop]=temp;
                    //Swapping the process bursts                    
                    temp=pburst[iloop];
                    pburst[iloop]=pburst[jloop];
                    pburst[jloop]=temp;
                }
            }
        }
    }
}
void avg_wait_time()
{
	int temp;
	for(iloop=0;iloop<pnum;iloop++)
	{
		temp=0;
		for(jloop=1;jloop<=pos;jloop++)
		{
			if(gantt_num[jloop-1]==(iloop+1))
			{
				total_wait=total_wait+gantt[jloop-1]-gantt[temp];
				temp=jloop;
			}
		}
	}		
    	total_wait=total_wait-total_arr;
	printf("\nTotal waiting time is %0.2f\n",total_wait);
	avg_wait=(float)(total_wait/pnum);
}
void avg_turnaround()
{
    	for(iloop=pos;iloop>=0;iloop--)
    	{
		if(visit[gantt_num[iloop-1]]==0)
		{
			total_tat=total_tat+gantt[iloop];
			visit[gantt_num[iloop-1]]=1;
		}
	}
	for(iloop=0;iloop<pnum;iloop++)
   	total_arr=total_arr+arrival[iloop];
    	total_tat=total_tat-total_arr;
	printf("\n\nTotal turnaround time is %0.2f",total_tat);
	avg_tat=(float)(total_tat/pnum);
}
void display()
{
	printf("\nAverage turnaround time is %0.2f ms",avg_tat);
	printf("\nAverage waiting time is %0.2f ms\n",avg_wait);
}
int all_done()
{
    int count=0;
    for(iloop=0;iloop<pnum;iloop++)
    {
        if(pburst[iloop]!=0)
        count++;
    }
    return count;
}
void cal_gantt()
{
    int sum=0,temppos[TEMP];
    for(iloop=0;iloop<TEMP;iloop++)
    temppos[iloop]=0;
    while(all_done()!=0)
    {
        for(iloop=0;iloop<pnum;iloop++)
        {
            if(pburst[iloop]!=0)
            {
                if(pburst[iloop]<quantum)
                {
                    sum=sum+pburst[iloop];
                    pburst[iloop]=0;
                    gantt_num[pos]=proname[iloop];
                    gantt[pos+1]=sum;
                    pos++;
                    process_wait[proname[iloop]-1]=process_wait[proname[iloop]-1]+gantt[pos-1]-gantt[temppos[proname[iloop]-1]];
                    temppos[proname[iloop]-1]=pos-1;
                }
                else
                {
                    sum=sum+quantum;
                    pburst[iloop]=pburst[iloop]-quantum;
                    gantt_num[pos]=proname[iloop];
                    gantt[pos+1]=sum;
                    pos++;
                    process_wait[proname[iloop]-1]=process_wait[proname[iloop]-1]+gantt[pos-1]-gantt[temppos[proname[iloop]-1]];
                    temppos[proname[iloop]-1]=pos-1;
                }
            }
        }
    }
}
void gantt_chart()
{
    int sum=0;
    sort_arrival();
    cal_gantt();
    printf("\nHere is the Gantt chart for the given processes:\n\n");
    for(iloop=0;iloop<pos;iloop++)
    {
        printf("\tP%d\t",gantt_num[iloop]);
    }
    printf("\n");
    for(jloop=0;jloop<=pos;jloop++)
    {
        printf("%d\t\t",gantt[jloop]);
    }
}
int main()
{
    initialise();
    input();
    gantt_chart();
    avg_turnaround();
    avg_wait_time();
    display();
}
