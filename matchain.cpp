
#include<iostream>
#include<time.h>
#define INFINITY 100000
using namespace std;
void matchain_order(int* p,int n);
void print_parens(int i,int j);
int** s;
int main(){

	int n,i;
	int* p;
	cout<<"Enter the no of matrices to be multiplied\n";
	cin>>n;
	p = new int[n+1];
	cout<<"Enter the first dimension of the n matrices\n";
	for(i=0;i<n;i++)
		cin>>p[i];
	cout<<"Enter the last dimension of the nth matrix\n";
	cin>>p[i];

	clock_t start = clock();
	matchain_order(p,n);
	cout<<"\nThe parenthesization is\n";
	print_parens(1,n);
	clock_t end = clock();
	cout<<"\nExecution time :"<<((double)(end-start))/CLOCKS_PER_SEC;
}
void matchain_order(int* p,int n){

	int i=0,j,k,l,temp;
	int**m;
	n++;
	m= new int*[n];
	s = new int*[n];
	for(i=0;i<n;i++){
		m[i] = new int[n];
		s[i] = new int[n];
	}

	for(i=1;i<n;i++)
		m[i][i]=0;
	for(l=2;l<n;l++){
		for(i=1;i<n-l+1;i++){
			j =i+l-1;
			m[i][j]=INFINITY;
			for(k=i;k<=j-1;k++){
				temp = m[i][k]+m[k+1][j]+(p[i-1]*p[k]*p[j]);
				if(temp<m[i][j]){
					m[i][j]=temp;
					s[i][j]=k;
				}
			}
		}
	}

	cout<<"\nThe s matrix is\n";
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(s[i][j]!=0)
			cout<<s[i][j]<<" ";
		}
		cout<<"\n";
	}

}
void print_parens(int i,int j){

	if(i==j){
		cout<<"A"<<i;

	}
	else{
		cout<<"(";
		print_parens(i,s[i][j]);
		print_parens(s[i][j]+1,j);
		cout<<")";
	}
}
