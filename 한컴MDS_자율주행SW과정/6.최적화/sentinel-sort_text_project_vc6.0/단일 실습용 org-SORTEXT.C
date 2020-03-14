#include <stdio.h>

#define LEN  20

char *str = "TOLEARNSORTALGORITHM";

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
        a[i] = (int)str[i];
}

void t_insert_sort(int a[], int n)
{
    int i, j, t;
    printf("\nInsertion Sort");
    for (i = 1; i < n; i++)
	{
		print_array(a, LEN);
		t = a[i];
		j = i;
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}
	print_array(a, LEN);
}

void main(void)
{
	int *a;
	int j;	
	if ((a = (int*)malloc(sizeof(int)*(LEN+1))) == NULL)
	{ printf("\nOut of memory");
      return;
	}		
	set_array(a);
	t_insert_sort(a, LEN);
}






