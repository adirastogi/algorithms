#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<time.h>

void selection_sort(int*,int);
int main()
{
    int *a,n;

    printf("Enter the no of elements(n)\n");
	scanf("%d",&n);
    a = (int*)malloc(n*sizeof(int));
    if (a==NULL) {printf("Error");exit (1);}

	printf("enter the elements in array\n");

    for(int i=0;i<n;i++)
	 scanf("%d",&a[i]);


    printf("the sorted array is\n");
    clock_t start = clock();
    selection_sort(a,n);
    clock_t end = clock();

    
    for(int i=0;i<n;i++)
	  printf("%d\n",a[i]);
printf("\nExecution time :%f ",((double)(end-start)/CLOCKS_PER_SEC));
//
	return 0;
}


void selection_sort(int* a,int n)
{
	int i,j,k=0,temp,t2;

	for(j=0;j<n;j++)
	{
		temp=a[k];
		for(i=k;i<n;i++)
		{
			if(temp>a[i])
			{
				temp=a[i];
			}
			if(temp==a[i])
			{
				t2=a[k];
				a[k]=temp;
				a[i]=t2;
			}
		}
		k++;
	}

}
