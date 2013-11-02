/*
* Program to calculate the kth smallest elemment in two arrays
*
*/


#include<iostream>
using namespace std;
int binsearch(int*, int , int);

int kthsmallest(int* a, int n, int* b, int m, int k){

	int* p = a;
	int* q = b;
	int split_p = (n-1)/2 + 1;
	int split_q = binsearch(q,m,p[split_p-1]);

	if(k>m+n)
		return -1;
	else if(k<1)
		return -1;
	else if(split_p+split_q == k)
		return (p[split_p-1]>q[split_q-1]?p[split_p-1]:q[split_q-1]);
	else if (split_p+split_q>k)
		return kthsmallest(p,split_p,q,split_q,k);
	else return kthsmallest(p+split_p,n-split_p,q+split_q,m-split_q,k-(split_p+split_q));

}

int binsearch(int * a , int n, int x){

	int* low = a;
	int* high = a+n-1;

	while(high!=low-1){

		int offset = (high-low)/2;
		int* mid = low+offset;

		if(x==*mid)
			return mid-a+1;
		else if(x > *mid)
			low = mid+1;
		else high = mid-1;

	}
	
	if(high==a-1)
		//left end of array
		return 0;
	else if(low == a+n)
		//right end of array
		return n;
	else return high-a+1;

}

int main(){

	int a[] = {1,3,4,5,9,10,11};
	int b[] = {6,7,8,19};
	int x = kthsmallest(a,7,b,4,5);
	cout<<x;

}
