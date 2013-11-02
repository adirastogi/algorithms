
#include<iostream>
#include<stdlib.h>
#define INFINITY 10000
#define NIL -10000
using namespace std;
struct edge{
	int u;
	int w;
	int v;
};
struct element{
	int data;
	int rank;
	element* parent;
};
element* e;
edge* E;
edge* A;
int** graph;
void sort_nondec(edge* E,int k);
void init_graph(int n,int ed,int y);
void print_graph(int n);
int kruskal_mst(int n,int ed);
void make_set(int x);
element* find_set(int x);
void link(element& x,element& y);
void union_set(int x,int y);
void print_edges(int k);

int main(){

	int n,y,e;
        clock_t start,end;
	cout<<"Enter the no of vertices in the graph\n";
	cin>>n;
	cout<<"Enter the no of edges in the graph\n";
	cin>>e;
	cout<<"Weighted or unweighted ?(1 or 0) ";
	cin>>y;
	init_graph(n,e,y);
	cout<<"\nThe graph is\n";
	print_graph(n);
	cout<<"\n";
	cout<<"The edges(u,w,v) in the MST are\n";
	start = clock();
	print_edges(kruskal_mst(n,e));
	end = clock();
        cout<<"\nExecution time : "<<((double)(end-start)/CLOCKS_PER_SEC);
    return 0;

}

void init_graph(int n,int ed,int y){

	int v,w=1,x,k=0;;

	graph = new int*[n];
	for(int i=0;i<n;i++){
		graph[i] = new int[n];
		for(int j=0;j<n;j++)
			graph[i][j] = INFINITY;
	}
	E = new edge[ed];
	A = new edge[ed];
	e = new element[n];


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
			if(graph[v][i]!=INFINITY){
				graph[i][v]=w;
			}
			else{
				graph[i][v]=w;
				E[k].u = i;
				E[k].w = w;
				E[k].v =v;
				k++;
			}
		}
    }

	   sort_nondec(E,ed);


}
void sort_nondec(edge* d,int k){

	edge temp;
	for(int i=0;i<k;i++){
		for(int j=0;j<k-1;j++){
			if(d[j].w>d[j+1].w){
				temp = d[j];
				d[j] =  d[j+1];
				d[j+1] = temp;
			}
		}
	}
}
void print_graph(int n){

	for(int i=0;i<n;i++){
		cout<<i<<"-> ";
		for(int j=0;j<n;j++){
			if(graph[i][j]!=INFINITY)
				cout<<"("<<j<<","<<graph[i][j]<<") ";
		}
		cout<<"\n";
	}
}
int kruskal_mst(int n,int ed){

	int k=0;
	for(int i=0;i<n;i++)
		make_set(i);
	for(int i=0;i<ed;i++){
		if(find_set(E[i].u)->data!=find_set(E[i].v)->data){
			A[k++] = E[i];
			union_set(E[i].u,E[i].v);
		}
	}
	return k;

}
void print_edges(int k){
	for(int i=0;i<k;i++)
		cout<<"("<<A[i].u<<","<<A[i].w<<","<<A[i].v<<")\n";
}
void make_set(int x){

	e[x].data = x;
	e[x].rank = 0;
	e[x].parent = &e[x];
}
element* find_set(int x){

	if(e[x].data!=(e[x].parent->data)){
		e[x].parent = find_set(e[x].parent->data);
	}
	return e[x].parent;
}
void link(element& x,element& y){

	if(x.rank>y.rank)
		y.parent = &x;
	else{
		x.parent = &y;
		if(x.rank==y.rank)
			y.rank++;
	}
}
void union_set(int x,int y){
	link(*find_set(x),*find_set(y));
}

