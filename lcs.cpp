#include <iostream>
#include<time.h>
#define UP 1
#define DOWN 2
#define DIAG 3
using namespace std;
char * x ;
char * y;
int m,n;
int ** c;
int ** b;
void lcs_length(char*,char*);
int main()
{

	cout<<"Enter the length of X\n";
	cin>>m;
	cout<<"Enter the length of Y\n";
	cin>>n;

	int i=0;
	int j=0;

	c = new int*[m+1];
    for(i=0;i<m+1;i++){
	  c[i] = new int[n+1];
	}


	for(i=0;i<m+1;i++){
	for(j=0;j<n+1;j++)
	{	c[i][j]=0; cout<<c[i][j]<<" ";}

	    cout << "\n";
	}

	x = new char[m+1];
	y = new char[n+1];


	cout<<"Enter sequence x";
	cin>>x;
	cout<<"Enter sequence y";
	cin>>y;


    clock_t start = clock();    
    lcs_length(x,y);
    clock_t end = clock();

    cout<<"\nLength of longest common subsquence is "<<c[m][n]<<"\n";
	
cout<<"\nExecution time : "<<((double)(end-start)/CLOCKS_PER_SEC);
  return 0;
}

void lcs_length(char* x,char* y){


	int i,j;
    for(i=0;i<=m;i++)
		c[i][0] = 0;
	for(j=0;j<=n;j++)
		c[0][j] = 0;

	for(i=1;i<=m;i++){

		for(j=1;j<=n;j++){

			if(x[i]==y[j]){

				c[i][j] = c[i-1][j-1] +1;
				cout<<c[i][j]<<" ";
				b[i][j] = DIAG;
			}
			else if(c[i-1][j] >= c[i][j-1]){
                    c[i][j] = c[i-1][j];
					cout<<c[i][j]<<" ";
					b[i][j] = UP;
			}
			else{

			        c[i][j] = c[i][j-1];
					cout<<c[i][j]<<" ";
					b[i][j] = DOWN;
			}

		}

		cout<<"\n";

	}


}
