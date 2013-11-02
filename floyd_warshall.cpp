#include<iostream>
#include<stdlib.h>
using namespace std;
#define INFINITY 100000
#define NIL -10000
using namespace std;
int** graph;
void init_graph(int n,int y);
void print_graph(int n);
int** floyd_warshall(int n);
void print_matrix(int** D,int n);
int main(){

	int n,y;
        clock_t start,end;
	cout<<"Enter the no of vertices in the graph\n";
	cin>>n;
	cout<<"Weighted or unweighted ?(1 or 0) ";
	cin>>y;
	init_graph(n,y);
	cout<<"The graph is\n";
	print_graph(n);
	cout<<"the final weight matrix is\n";
	cout<<"\n";
	start = clock();
	print_matrix(floyd_warshall(n),n);
	end = clock();
        cout<<"\nExecution time : "<<((double)(end-start)/CLOCKS_PER_SEC);
    return 0;

}
void init_graph(int n,int y){

	int v,w=1,x;
	graph = new int*[n];
	for(int i=0;i<n;i++){
		graph[i] = new int[n];
		for(int j=0;j<n;j++){
			if(i==j)
				graph[i][j] = 0;
			else
				graph[i][j] = INFINITY;
		}
	}

    for(int i=0;i<n;i++){
		cout<<"Enter the no of vertices adjacent to vertex "<<i<<" ";
		cin>>x;
		for(int j=0;j<x;j++){
			cout<<"vertex:";
			cin>>v;
			if(y){
				cout<<"weight:";
				cin>>w;
			}
			graph[i][v]=w;
		}
    }

}
void print_graph(int n){

	for(int i=0;i<n;i++){
		cout<<i<<"-> ";
		for(int j=0;j<n;j++){
			if(graph[i][j]!=INFINITY&&(i!=j))
				cout<<"("<<j<<","<<graph[i][j]<<") ";
		}
		cout<<"\n";
	}
}
int** floyd_warshall(int n){

	int** D1,**D2,**temp;
	D1 = new int*[n];
	D2 = new int*[n];
	for(int i=0;i<n;i++){
		D1[i] = new int[n];
		D2[i] = new int[n];
		for(int j=0;j<n;j++){
			D1[i][j] = graph[i][j];
			D2[i][j] = graph[i][j];
		}

	}

	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(D1[i][j]<(D1[i][k]+D1[k][j])){
					D2[i][j] = D1[i][j];
				}
				else{
					D2[i][j] = D1[i][k] + D1[k][j];
				}
			}
		}
		temp = D1;
		D1 = D2;
		D2 = temp;
	}
	return D2;

}
void print_matrix(int** D,int n){

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(D[i][j]<90000)
				cout<<D[i][j]<<" ";
			else
				cout<<"I ";
		}
		cout<<"\n";
	}
}
