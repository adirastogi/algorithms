#include<iostream>
using namespace std;

int find_primes(int N){

	char *sieve = new char[N+1];

	for(int i=0;i<N+1;i++)
		sieve[i]=0;

	int start = 2;
	while(start<=N){
		
		while(sieve[start]==1)
			start++;
		int j = start*start;
		//j = j+start;
		while(j<=N){
			sieve[j]=1;
			j =j+start;
		}
		start++;	
		
	}

	int count = 0;
	for(int i=2;i<=N;i++){
		if(sieve[i]==0){
			count++;
			cout<<i<<" ";
		}
			
	}

	return count;
	
}
int main(){
	int x = find_primes(1000000);
	cout<<"\t"<<x;
}