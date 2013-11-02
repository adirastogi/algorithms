#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<time.h>
typedef struct node
{
	float val;
	struct node *link;
}NODE;
typedef struct bucket
{
	struct node *llink;
	struct node *flink;
}BUCKET;

BUCKET *B[15];
NODE *arr[15];

void display(BUCKET *B)
{
	NODE *node;
	node=B->flink;
	while(node!=NULL)
	{
		printf("%.3f\t",node->val);
		node=node->link;
	}
}
void insertion_sort(BUCKET *B)
{
	NODE *node;int k,i=0,j;float temp=0.0f;
	node=B->flink;
	while(node!=NULL)
	{
		arr[i++]=node;
		node=node->link;
	}
	for(j=1;j<i;j++)
	{
		temp=arr[j]->val;
		k=j-1;
		while(k>=0&&arr[k]->val>temp)
		{
			arr[k+1]->val=arr[k]->val;
			k--;
		}
		arr[k+1]->val=temp;
	}
}
void bucket_sort(float A[],int n)
{
	int i,k=0;
	float temp;
	NODE *nod;
	for(i=0;i<n;i++)
	{
		temp=n*A[i];
		k=(int)temp;
		nod=(NODE*)malloc(sizeof(NODE));
		nod->val=A[i];
		nod->link=NULL;
		if(B[k]->flink==NULL)
		{
			B[k]->flink=nod;
		}
		else
		{
			B[k]->llink->link=nod;
		}
		B[k]->llink=nod;
//		printf("\nk and temp are:%d %.2f",k,temp);
	}
	printf("\noriginal array is:\n");
	for(i=0;i<n;i++)
	{
		if(B[i]->flink!=NULL)
			display(B[i]);
	}
	for(i=0;i<n;i++)
	{
		if(B[i]->flink!=NULL)
			insertion_sort(B[i]);
	}
	printf("\n the sorted array is:\n");
	for(i=0;i<n;i++)
	{
		if(B[i]->flink!=NULL)
			display(B[i]);
	}
}

void main()
{
	float A[15];
	int n,i;
	clrscr();
	printf("enter size of array:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("enter element %d:",i+1);
		scanf("%f",&A[i]);
		B[i]=(BUCKET*)malloc(sizeof(BUCKET));
		B[i]->flink=NULL;
		B[i]->llink=NULL;
	}
	clock_t start = clock();
	bucket_sort(A,n);
	clock_t end = clock();
	printf("\nExecution time :%f ",((double)(end-start)/CLOCKS_PER_SEC));
	getch();
}
