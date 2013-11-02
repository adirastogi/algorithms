/*
* Program to calculate the kth smallest element in two arrays
*
*/

#include<iostream>

using namespace std;

int kthsmallest(int* a, int p, int* b,int q, int k){

	if(p==0)
		return b[k-1];
	else if(q==0)
		return a[k-1];

	int ma = p/2;
	int mb = q/2;
	char larger = (a[ma]>b[mb])?'a':'b';
	int nleft = ma+mb+1;

	if(nleft>=k)
		if(larger=='a') return kthsmallest(a,ma,b,mb+1,k);
		else			return kthsmallest(a,ma+1,b,mb,k);
	else if(nleft<k)
		if(larger=='a') return kthsmallest(a+ma,p-ma,b+mb+1,q-mb-1,k-nleft);
		else			return kthsmallest(a+ma+1,p-ma-1,b+mb,q-mb,k-nleft);

}
int main(){
	int a[] = {1,2,3,4,5};
	int b[] = {5,6,8,10,12};
	for(int i=1;i<=10;i++)
	cout<<kthsmallest(a,5,b,5,i)<<endl;
	return 0;
}
