#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<time.h>
//int*
void counting_sort(int A[],int temp[],int n,int k)
{
	int i,j,C[10],B[15];
	for(i=0;i<=k;i++)
		C[i]=0;
	for(j=0;j<n;j++)
		C[temp[j]]++;
	for(i=1;i<=k;i++)
		C[i]=C[i]+C[i-1];
	for(j=n-1;j>=0;j--)
		{
			B[C[temp[j]]-1]=A[j];
			C[temp[j]]--;
		}
       for(i=0;i<n;i++)	//here u can also return array B
	       A[i]=B[i];
}
void radix(int A[],int n,int k,int l)
{
	int i,q,high,temp[15];
	double y=0.0;
	if(l>0)
	{       high=0;
		y=pow(10,(k-l));
		for(i=0;i<n;i++)
		{
			q=A[i]/(int)y;
			temp[i]=q%10;
			if(high<temp[i])
				high=temp[i];
		}
		counting_sort(A,temp,n,high);
		radix(A,n,k,l-1);
	}
	else
	{
		printf("the sorted array is:\n");
		for(i=0;i<n;i++)
			printf("%d ",A[i]);
	}
}
int main()
{
	int n,k,i;
	int A[15];

	printf("enter no of elements:");
	scanf("%d",&n);
	printf("enter max no. of digits for an element:");
	scanf("%d",&k);
	for(i=0;i<n;i++)
	{
		printf("enter element %d:",i+1);
		scanf("%d",&A[i]);
	}
	clock_t start = clock();
	radix(A,n,k,k);
	clock_t end = clock();
    printf("Execution time: %f",((double)(end-start)/CLOCKS_PER_SEC));

	return 0;
}
