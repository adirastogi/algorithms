#include<iostream>
#define min(x,y) (x>y)?y:x
#define MODNUM 1000000007
using namespace std;
long long comb[900][900];
long long binomial(int n, int k){

	if(k==0)		comb[n][k] = 1;
	else if(n==0)	comb[n][k] = 0;
	else			{
		if(comb[n][k]<0)
			comb[n][k] = binomial(n-1,k-1) + binomial(n-1,k);
			
	}
	return comb[n][k];
}

long long calculateScorecards(int* a, int n){

	

	int sumOutdeg = 0;
	int emptyNodes = 0;

	for(int i=0;i<n;i++)
		if(a[i]==-1)	emptyNodes++;
		else			sumOutdeg += a[i];

	//calculate the number of graph edges using nC2
	long nEdges = binomial(n,2);
	//check if the initial scores are valid
	if(sumOutdeg>nEdges)
		return 0;
	//check if graph is already complete.
	if(sumOutdeg==nEdges)
		return 1;
	nEdges = nEdges - sumOutdeg;
	int k = emptyNodes;
	int r = nEdges;
	
	//s = max exponent of x allowed in (1-x^n) in the lc term
	int s = min(r+1,n);
	int check = k-(r/s);

	//solve the equation o1+o2+.....ok = r;
	long long solution = 0;
	for(int i=k;(s*(k-i))<=r && i>0;i--){
		//get coefficient of the ith term in (1-x^n)^k the ith term is (kCi).1^k.(-x)^(k-i)
		long long lc = ((k-i)%2)?(-1)*binomial(k,k-i):binomial(k,k-i);

		//get the matching  coefficient for r-in i*n expansion of (1-x)^(-k)
		int t = (r-(k-i)*s);
		long long rc =binomial(k+t-1,t);

		//add the lc and c to get coefficient of x^r in (1-x^n)^k.(1-x)^(-k);
		long long c = lc*rc;
		solution += c;
	}

	return solution%MODNUM;
}

int main(){

	for(int i=0;i<900;i++)
		for(int j=0;j<900;j++)
			comb[i][j]=-1;

	int nCases =0;
	//cout<<binomial(40,20);

	int a[]  = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20};
	cout<<calculateScorecards(a,23);
 
/*
	cin>>nCases;
	int nodes;
	for(int i=0;i<nCases;i++){
		cin>>nodes;
		int* a = new int[nodes];
		for(int j=0;j<nodes;j++)
			cin>>a[j];
		int x = calculateScorecards(a,nodes);
		cout<<x<<endl;
	}
	*/
	

}