#include<stdio.h>
#include<conio.h>
#include<malloc.h>

void insert_sort(int* ,int);

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

    insert_sort(a,n);

    for(int i=0;i<n;i++)
	  printf("%d\n",a[i]);

//
	return 0;
}

void insert_sort(int* a ,int n)
{
	int i,j,k,temp;
	for(i=0;i<n;i++)
	{
		temp=a[i];
		for(j=0;j<i;j++)
		{
			if(a[i]<a[j])
			{
				for(k=i;k>j;k--)
				{
					a[k]=a[k-1];
				}
				a[j]=temp;
				j--;
			}
		}
	}

}

