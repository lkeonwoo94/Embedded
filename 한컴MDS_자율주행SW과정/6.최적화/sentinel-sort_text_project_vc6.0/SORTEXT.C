#include <stdio.h>
#include <limits.h>
#include <windows.h>
#include <limits.h>
#include <limits.h>
#include <limits.h>



#define timedelay  1000000


int LEN = 0 ;

double thisTickCount = 0 ;
double bcount = 0 ;

int *base;

char *str = "ATOLEBRNSORTBLGORITHM";
//char *str = "ATOLEBRNSORTBLGORITHM";
void start_time(void)
{
	thisTickCount = GetTickCount();
	bcount = thisTickCount;
	printf("\n current time tick is \t %f",thisTickCount);
}

void end_time(void)
{
	thisTickCount = GetTickCount();	
	printf("\n loop end time tick is \t %f",thisTickCount);
	printf("\n used time tick is \t %f\n",thisTickCount - bcount);
	thisTickCount = 0 ; 	bcount = 0 ;
}


void print_array(int *a, int n)
{
    int i;
    printf("\n    ");
    for (i = 0; i < n; i++)
	printf("%c  ", a[i]);
}

void set_array(int *a)
{
    int i;
    for (i = 0; i < LEN; i++)
        a[i] = (int)str[i+1];
}


void t_insert_sort(int a[], int n)
{
    int i, j, t;
//    printf("\nInsertion Sort");
    for (i = 1; i < n; i++)
	{
//	print_array(a, LEN);
	t = a[i];
	j = i;
	while (a[j-1] > t && j > 0)
	    {
	    a[j] = a[j-1];
	    j--;
	    }
	a[j] = t;
	}
//	print_array(a, LEN);
}

void t_insert_sort2(int a[], int n)
{
    int i, j, t;
//    printf("\nInsertion Sort");
    for (i = 1; i < n; i++)
	{
//	print_array(a, LEN);
	t = a[i];
	j = i;
	while (a[j-1] > t )
	    {
	    a[j] = a[j-1];
	    j--;
	    }
	a[j] = t;
	}
//	print_array(a, LEN);
}



void main(void)
{
    int *a;
	int j;
	LEN = strlen(str);

    if ((a = (int*)malloc(sizeof(int)*(LEN+1))) == NULL)
        {
        printf("\nOut of memory");
        return;
        }
	
	printf("\n");
	print_array(a, LEN);
	printf("\n");

//-----------------------------------------------
	printf("\n [1] insertion sort \n");

	set_array(a);
	print_array(a, LEN);
	printf("\n");

	start_time();
	for(j=0; j< timedelay ;j++)
	{
	    set_array(a);
		t_insert_sort(a, LEN);
	}
	end_time();  

	print_array(a, LEN);
	printf("\n");

//-----------------------------------------------

	printf("\n [2] sentinel \n");

	set_array(a);
	*( a - 1 ) = 'A' ;
	print_array(a, LEN);
	printf("\n");

	start_time();
	for(j=0; j< timedelay ;j++)
	{
	    set_array(a);
		t_insert_sort2(a, LEN);
	}
	end_time();  

	print_array(a, LEN);
	printf("\n\n");

	
	printf("\n -------------- end of program ----------------- \n");
    if ( getch() == '0')
    {
	exit(0);
    }

   
}