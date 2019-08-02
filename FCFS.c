#include<stdio.h>
#include<stdlib.h>
int pnum,pburst[50],iloop,wait[50],arrival[50],choose=0,gantt[50],jloop;
float avg_wait,avg_tat,total_wait,total_tat,total_arr;
void initialise()
{
	for(iloop=0;iloop<50;iloop++)
	{
        arrival[iloop]=0;
        gantt[iloop]=iloop+1;
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
	}
	printf("Enter 1 if the processes has different arrival times, any number else otherwise: ");
	scanf("%d",&choose);
	if(choose==1)
	input_arrival();
}
void avg_wait_time()
{
    total_arr=0.0;
    for(iloop=0;iloop<pnum;iloop++)
    total_arr=total_arr+arrival[iloop];
    total_wait=total_wait-total_arr;
	printf("\n\nTotal waiting time is %0.2f",total_wait);
	avg_wait=(float)(total_wait/pnum);
}
void avg_turnaround()
{
    total_arr=0.0;
    for(iloop=0;iloop<pnum;iloop++)
    total_arr=total_arr+arrival[iloop];
    total_tat=total_tat-total_arr;
	printf("\nTotal turnaround time is %0.2f",total_tat);
	avg_tat=(float)(total_tat/pnum);
}
void display()
{
	printf("\n\nAverage waiting time is %0.2f ms",avg_wait);
	printf("\nAverage turnaround time is %0.2f ms\n",avg_tat);
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
                    temp=gantt[iloop];
                    gantt[iloop]=gantt[jloop];
                    gantt[jloop]=temp;
                    //Swapping the process bursts                    
                    temp=pburst[iloop];
                    pburst[iloop]=pburst[jloop];
                    pburst[jloop]=temp;
                }
            }
        }
    }
}
void gantt_chart()
{
    int sum=0;
    sort_arrival();
    printf("\nHere is the Gantt chart for the given processes:\n");
    for(iloop=0;iloop<pnum;iloop++)
    {
        printf("\tP%d\t",gantt[iloop]);
    }
    printf("\n");
    for(jloop=0;jloop<pnum;jloop++)
    {
        printf("%d\t\t",sum);
        sum=sum+pburst[jloop];
        if(jloop!=pnum-1)        
        total_wait=total_wait+sum;
        //if(jloop!=0)
        total_tat=total_tat+sum;
        //printf("\nTotal tat is %d",total_tat);
    }
    printf("%d",sum);
}
int main()
{
	initialise();
	input();
    gantt_chart();	
	avg_wait_time();
	avg_turnaround();
    display();
}
