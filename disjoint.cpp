#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<time.h>
int A[2][16];
void makeset(int i)
{
	A[0][i]=-i;
	A[1][i]=-1;
}
int findset(int i)
{
	if(A[0][i]<0)
		return i;
	else
		return A[0][i];
}
void unionset(int i,int j)
{
	unsigned int rep_i,rep_j,last_i,last_j,size_i,size_j,x,k;
	rep_i=findset(i);
	rep_j=findset(j);
	last_i=abs(A[0][rep_i]);
	last_j=abs(A[0][rep_j]);
	size_i=abs(A[1][last_i]);
	size_j=abs(A[1][last_j]);
	if(size_i>=size_j)
	{
		A[1][last_i]=rep_j;
		A[1][last_j]=-(size_i+size_j);
		A[0][rep_i]=A[0][rep_j];
		x=rep_j;
		for(k=1;k<=size_j;k++)
		{
			A[0][x]=rep_i;
			x=A[1][x];
		}
	}
	else
	{
		A[1][last_j]=rep_i;
		A[1][last_i]=-(size_i+size_j);
		A[0][rep_j]=A[0][rep_i];
		x=rep_i;
		for(k=1;k<=size_i;k++)
		{
			A[0][x]=rep_j;
			x=A[1][x];
		}
	}

}

void main()
{   clock_t start = clock();
	int ans,i,j;
	clrscr();
	do
	{
		printf("\n1.Make set");
		printf("\n2.Find set");
		printf("\n3.Union sets");
		printf("\n4.Display the 2D array");
		printf("\n5.Exit");
		printf("\n Enter ur choice(1-5):");
		scanf("%d",&ans);
		switch(ans)
		{
			case 1:printf("\n enter an element(1-15):");
			       scanf("%d",&i);
			       if(i<1||i>15)
					printf("Invalid value of the element");
			       else
					makeset(i);
			       break;
			case 2:printf("\n enter an element whose representative element is to be found(1-15):");
			       scanf("%d",&i);
			       if(i<1||i>15)
					printf("Invalid value of the element");
			       else
					printf("Representative element of %d is:%d",i,findset(i));
			       break;
			case 3:printf("\n enter an element");
			       scanf("%d",&i);
			       printf("\n enter another element");
			       scanf("%d",&j);
			       if(i<1||i>15||j<1||j>15)
					printf("Invalid value of the element");
			       else
					unionset(i,j);
			       break;
			case 4:for(i=0;i<2;i++)
			       {        printf("\n");
					for(j=1;j<16;j++)
					{
						printf(" %d",A[i][j]);
					}
			       }
			       break;
			case 5:break;
			default:printf("Invalid choice");
		}
	}while(ans>=1&&ans<=5);
	clock_t end = clock();
	printf("\nExecution time : %d",((double)(end-start)/CLOCKS_PER_SEC));
	getch();
}
