#include <iostream>
#include <time.h>

using namespace std;
int* counting_sort(int* a,int n,int k);
int main(){


int k,n;
	int *a,*b;

	cout<<"Enter the range of array data(k)\n";
	cin>>k;
	cout<<"Enter the no of elements(n)\n";
	cin>>n;
    a = new int[n];


 cout<<"enter the elements in array\n";

 for(int i=0;i<n;i++)
	 cin>>a[i];


 cout<<"the sorted array is\n";

  clock_t start = clock();
  b = counting_sort(a,n,k);
  clock_t end = clock();
  
for(int i=0;i<n;i++)
	  cout<<b[i]<<"\n";
 cout<<"\nExecution time : "<<((double)(end-start)/CLOCKS_PER_SEC);

return 0;
}

int* counting_sort(int *a,int n,int k ){
int* pos,*count,*b;
b = new int[n];

pos = new int[k];
count  = new int[k];
int i;


  for(i=0;i<k;i++)
	 count[i]=0;
  for(i=0;i<n;i++)
     count[a[i]]++;
  pos[0]=0;
  for(i=1;i<k;i++)
     pos[i]=pos[i-1] + count[i-1];
  for(i=0;i<n;i++)
  {
   b[pos[a[i]]]=a[i];
   pos[a[i]]++;
  }

  delete[] pos;
  delete[] count;
  return b;
}
