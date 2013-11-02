#include<iostream>
using namespace std;
#define INFINITY 123134;
int calculate_min_coins(int * d,int d_len, int amt){

	int* m = new int[amt+1];

	for(int i=0;i<=amt;i++)
		m[i] = INFINITY;

	for(int i=0;i<d[0];i++)
		m[i] = 0;

	for(int i=0;i<=amt;i++){
		int min = m[i];
		for(int k=0;k<d_len;k++){
			int j = i-d[k];
			if(j>=0 && (m[j]+1)<m[i]){
				m[i] = m[j]+1;
			}
		}
		
	}

	return m[amt];
}



int main(){

	int amt = 70;
	int d[] = {1,10,30,40};
	cout<<calculate_min_coins(d,4,amt);
	return 0;
}