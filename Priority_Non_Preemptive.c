#include<stdio.h>
#include<stdlib.h>
int pnum,pburst[50],iloop,wait[50],arrival[50],choose=0,gantt[50],jloop,total_arr,priority[50];
float avg_wait,avg_tat,total_wait,total_tat;
void initialise()
{
	for(iloop=0;iloop<50;iloop++)
	{
        arrival[iloop]=0;
        gantt[iloop]=iloop+1;
        priority[iloop]=0;
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
    printf("Priority Scheduling (Low value higher priority)");
	printf("\nEnter number of process: ");
	scanf("%d",&pnum);
	for(iloop=0;iloop<pnum;iloop++)
	{
		printf("\nEnter burst for Process %d:\t",(iloop+1));
		scanf("%d",&pburst[iloop]);
        printf("\nEnter priority for Process %d:\t",(iloop+1));
        scanf("%d",&priority[iloop]);
	}
	printf("Enter 1 if the processes has different arrival times, any number else otherwise: ");
	scanf("%d",&choose);
	if(choose==1)
	input_arrival();
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
                    //Swapping priority
                    temp=priority[iloop];
                    priority[iloop]=priority[jloop];
                    priority[jloop]=temp;
                }
            }
        }
        printf("\nAfter sort_arrival():\nPriority\tNumber\tBurst\tArrival:\n");
        for(iloop=0;iloop<pnum;iloop++)
        printf("%d\t%d\t%d\t%d\n",priority[iloop],gantt[iloop],pburst[iloop],arrival[iloop]);
    }
}
void sort_priority()
{
    int temp=0,min;
    for(iloop=0;iloop<pnum-1;iloop++)
    {
        min=iloop;
        for(jloop=iloop+1;jloop<pnum;jloop++)
        {
            if((priority[min]>priority[jloop])&&(arrival[min]>=arrival[jloop]))
            {
                min=jloop;
            }
        }
        if(min!=iloop)
        {
            //Swapping arrival time
            temp=arrival[iloop];
            arrival[iloop]=arrival[min];
            arrival[min]=temp;
            //Swapping the process numbers                    
            temp=gantt[iloop];
            gantt[iloop]=gantt[min];
            gantt[min]=temp;
            //Swapping the process bursts                    
            temp=pburst[iloop];
            pburst[iloop]=pburst[min];
            pburst[min]=temp;
            //Swapping priority
            temp=priority[iloop];
            priority[iloop]=priority[min];
            priority[min]=temp;
        }
    }
    printf("\nAfter sort_priority():\nPriority\tNumber\tBurst\tArrival:\n");
    for(iloop=0;iloop<pnum;iloop++)
    printf("%d\t%d\t%d\t%d\n",priority[iloop],gantt[iloop],pburst[iloop],arrival[iloop]);
}
void avg_wait_time()
{
    for(iloop=0;iloop<pnum;iloop++)
    total_arr=total_arr+arrival[pnum];
    total_wait=total_wait-total_arr;
	printf("\nTotal waiting time is %0.2f",total_wait);
	avg_wait=(float)(total_wait/pnum);
}
void avg_turnaround()
{
    total_tat=total_tat-total_arr;
	printf("\nTotal turnaround time is %0.2f",total_tat);
	avg_tat=(float)(total_tat/pnum);
}
void display()
{
	printf("\nAverage waiting time is %0.2f ms\n",avg_wait);
	printf("\nAverage turnaround time is %0.2f ms\n",avg_tat);
}
void gantt_chart()
{
    int sum=0;
    sort_arrival();
    sort_priority();
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
