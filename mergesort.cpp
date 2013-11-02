 #include<stdio.h>
 #include<conio.h>
#include<time.h>
 void mergesort(int*,int,int);
 void merge(int*,int,int,int);
 void display(int*);
 void  main()
 {
 int A[10],i;
 clrscr();
 printf("Enter the values to be sorted");
 for(i=0;i<10;i++)
  scanf("%d",&A[i]);
 clock_t start = clock();
 mergesort(A,0,9);
 clock_t end = clock();
 display(A);
 printf("\nExecution time : %d",((double)(end-start)/CLOCKS_PER_SEC));
 getch();
 }

 void mergesort(int*A,int p,int r)
 {
 int q;
 if(p<r)
  {
   q=(p+r)/2;
   mergesort(A,p,q);
   mergesort(A,(q+1),r);
   merge(A,p,q,r);
  }
 }

 void merge(int*A,int p, int q,int r)
 {
 int*B,i,j,k=0;
 B=(int*)malloc((r-p)*sizeof(int));
 i=p;
 j=q+1;
 while((i<=q)&&(j<=r))
 {
  if(A[i]<A[j])
   B[k++]=A[i++];
  else
   B[k++]=A[j++];
 }
 while(i<=q)
  B[k++]=A[i++];
 while(j<=r)
  B[k++]=A[j++];
 for(i=0;i<=r-p;i++)
  A[i+p]=B[i];
}

void display(int*A)
{
int i;
for(i=0;i<10;i++)
 printf("\n%d",A[i]);
}
