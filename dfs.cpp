
#include<iostream>
#include<stdlib.h>
#include<time.h>
#define INFINITY 10000
#define NIL -10000
using namespace std;
struct node{
	int v;
	int w;
	node* next;
};
struct graph{
	node** vertex;
};
int* d;
int* parent;
char* color;
int* f;
int t;
void init_graph(graph& G,int n,int y);
void print_graph(graph& G,int n);
void dfs(graph& G,int n);
void dfs_visit(graph& G,int u);
int main(){

	int n,y;
	graph G;
	cout<<"Enter the no of vertices in the graph\n";
	cin>>n;
	cout<<"Weighted or unweighted ?(1 or 0) ";
	cin>>y;
	init_graph(G,n,y);
	cout<<"\nThe graph is\n";
	print_graph(G,n);
	cout<<"\n";
	cout<<"the dfs traversal is\n";
	clock_t start = clock();
        dfs(G,n);
	clock_t end = clock();
	cout<<"\nthe start and end times are\n";
	cout<<"v\ts\tf\n";
	for(int i=0;i<n;i++)
		cout<<i<<"\t"<<d[i]<<"\t"<<f[i]<<"\n";
	cout<<"\nExecution time : "<<((double)(end-start)/CLOCKS_PER_SEC);
    return 0;

}
void init_graph(graph& G,int n,int y){

	int v,w=1,x;
	G.vertex =  new node*[n];
	d = new int[n];
	parent = new int[n];
	color = new char[n];
	f = new int[n];
	t =0;
	   for(int i=0;i<n;i++){
		    d[i]=INFINITY;
		    f[i]=INFINITY;
		    parent[i]=NIL;
		    color[i] = 'W';
			cout<<"Enter the no of vertices adjacent to vertex "<<i<<" ";
			cin>>x;
			for(int j=0;j<x;j++){
				cout<<"vertex:";
				cin>>v;
				if(y){
					cout<<"weight:";
					cin>>w;
				}

				node* temp  = new node;
				temp->v=v;
				temp->w=w;
				temp->next=NULL;

				if(G.vertex[i]==NULL){
					G.vertex[i] = temp;
				}
				else{
					node* trav=G.vertex[i];
					while(trav->next!=NULL)
						trav = trav->next;
					trav->next = temp;
				}
			}
	   }
}
void print_graph(graph& G,int n){

	node* trav;
	for(int i=0;i<n;i++){
		cout<<i<<" -> ";
		trav = G.vertex[i];
		while(trav!=NULL)
			{
			cout<<"("<<trav->v<<","<<trav->w<<")"<<" ";
			trav = trav->next;
			}
		cout<<"\n";
	}
}
void dfs(graph& G,int n){
	for(int i=0;i<n;i++){
		if(color[i]=='W')
			dfs_visit(G,i);
	}
}
void dfs_visit(graph& G,int u){

	color[u] = 'G';
	t++;
	d[u] = t;
	node* trav;
	trav = G.vertex[u];
	while(trav!=NULL)
		{
		if(color[trav->v]=='W'){
			parent[trav->v] = u;
			dfs_visit(G,trav->v);
		}
		trav = trav->next;
		}
	color[u]='B';
	f[u] = ++t;
	cout<<u<<' ';
}

