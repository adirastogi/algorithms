/*
* Binary search on a circular sorted array .
*/


#include<iostream>
using namespace std;
int binsearch_circular(int* a , int low,int high, int x){

	int mid = (low+high)/2;
	if(a[mid]==x)
		return mid;

	
	if(a[low]<a[mid]){
		//left subarry is sorted and right is unsorted. determin if x lies in left subarry
		if(x<=a[high]){
			//call on right subarray
			return binsearch_circular(a,mid+1,high,x);
		}
		else{
			//in left sorted array. do regular search
			return binsearch_circular(a,low,mid-1,x);
		}
	}
	else if (a[mid]<a[high]){
		//right subarray is sorted, left unsorted
		if(x>=a[low]){
			//call on left unsorted array
			return binsearch_circular(a,low,mid-1,x);
		}
		else{
			//do
			return binsearch_circular(a,mid+1,high,x);
		}
	}


}

int main(){

	int a[] = {3,6,4,8,10,1,2};
	cout<<binsearch_circular(a,0,6,2);


}
