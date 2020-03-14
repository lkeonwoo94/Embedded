#include <windows.h>
#include <stdio.h>

#define arraySIZE  1024
#define timedelay  100000
//#define timedelay2 10000

void start_time(void);
void end_time(void);

double thisTickCount = 0 ;
double bcount = 0 ;

void start_time(void)
{
	thisTickCount = GetTickCount();
	bcount = thisTickCount;
//	printf("\n\n current time tick is %f \n\n",thisTickCount);
}

void end_time(void)
{
	thisTickCount = GetTickCount();	
//	printf("\n\n loop end time tick is %f",thisTickCount);
	printf("\n\n used time tick is %f",thisTickCount - bcount);
	thisTickCount = 0 ; 	bcount = 0 ;
}

int main (void)
{
	int data[arraySIZE];
    	int i,j;
	int sum = 0;
	int count;

	thisTickCount = GetTickCount();
	bcount = thisTickCount;

	start_time();
	for(j=0; j< timedelay ;j++)
	{
		for(i=0; i < arraySIZE ;i++)
		{
			data[i] = i%10;
		}
	}
	end_time();   
	
	sum = 0;
	start_time();
	for(j=0; j < timedelay ;j++)
	{
		for(i=0; i< arraySIZE; i += 1)
			sum += data[i];
	}
	end_time();   
    	printf("\n \n original sum is = %d \n\n",sum);

	sum = 0;
	start_time();
	for(j=0; j < timedelay ;j++)
	{
		for(i=0; i < arraySIZE ; i += 4)
		{
			sum += data[i];
			sum += data[i+1];
			sum += data[i+2];
			sum += data[i+3];
		}        // => 1000번의 jump를 250번으로 줄일 수 있다. 
	}
	end_time();   
    	printf("\n \n unrolled sum is = %d \n\n",sum);


	printf("\n -------------- end of program ----------------- \n");
    if ( getch() == '0')
    {
	exit(0);
    }

   

    return 0;
}