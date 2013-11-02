#include<iostream>
#include<math.h>
#include<stdio.h>
#include<string.h>
using namespace std;
#define RADIX 128
#define PRIME 251
int compare(char* P,char* beg,char* end);
int rabin_karp(char* T,int n,char* P,int m);
long int arith_mod(long int x,long int y);
int main(){

   char T[100],P[100];
   int y=-1;
   cout<<"Enter the text string\n";
   gets(T);
   cout<<"Enter pattern string\n";
   gets(P);
   start = clock();
   y=rabin_karp(T,strlen(T),P,strlen(P));
   end = clock();
   if(y>=0)
	   cout<<"First match occurs at "<<y;
   else
	   cout<<"No Match found";
   cout<<"\nExecution time : "<<((double)(end-start)/CLOCKS_PER_SEC);
 return 0;
}
int rabin_karp(char* T,int n,char* P,int m){

    long double temp = pow(RADIX,m-1);     //to avoid data overflow
	int h = (long long)(temp)%PRIME;  //
	long int p = 0;
	long int* t = new long int[n-m+1];
	t[0]=0;
	for(int i=0;i<m;i++){
		p = (RADIX*p+P[i])%PRIME;
		t[0] = (RADIX*t[0]+T[i])%PRIME;
	}
	for(int s=-1;s<n-m;s++){
		if(p==t[s+1]){
			if(compare(P,&T[s+1],&T[s+m])){
				return s+1;
			}
		}
	if(s<n-m-1)
			t[s+2] = arith_mod((RADIX*(t[s+1]-T[s+1]*h)+T[s+m+1]),PRIME);
	}
	return -1;
}
long int arith_mod(long int x,long int y){
	if(x<0)
		return ((x*(1-y))%y);
	else
		return x%y;
}
int compare(char* P,char* beg,char* end){

	while((beg!=end)&&(*P==*beg)){
		beg++;
		P++;
	}
	if(beg==end)
		return -1;
	else
		return 0;
}
