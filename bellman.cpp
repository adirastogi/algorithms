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
void init_graph(graph& G,int n,int y);
void print_graph(graph& G,int n);
int bellman_ford(graph& G,int n,int s);
void relax(int u,int v,int w);
void shortest_path(graph& G,int s,int v);
void print_paths(graph& G,int n,int s);
int main(){

	int n,y,s;
	graph G;
	cout<<"Enter the no of vertices in the graph\n";
	cin>>n;
	cout<<"Weighted or unweighted ?(1 or 0) ";
	cin>>y;
	init_graph(G,n,y);
	cout<<"\nThe graph is\n";
	print_graph(G,n);
	cout<<"\n";
	cout<<"Enter the source vertex ";
	cin>>s;
	clock_t start = clock();
	if(bellman_ford(G,n,s)!=0){
		cout<<"\nThe shortest paths from source vertex "<<s<<" are\n";
		print_paths(G,n,s);
	}
	else{
		cout<<"\nThe graph contains a negative weight cycle. Aborting";
		exit(0);
	}
	clock_t end = clock();
	cout<<"\nExecution time : "<<((double)(end-start)/CLOCKS_PER_SEC);
    return 0;

}
void init_graph(graph& G,int n,int y){

	int v,w=1,x;
	G.vertex =  new node*[n];
	d = new int[n];
	parent = new int[n];
	   for(int i=0;i<n;i++){
		    d[i]=INFINITY;
		    parent[i]=NIL;
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
void relax(int u,int v,int w){

	if(d[v]>(d[u]+w)){
		d[v]=d[u]+w;
		parent[v]=u;
	}
}
int bellman_ford(graph& G,int n,int s){

	d[s] = 0;
	node* trav;
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n;j++){
		trav = G.vertex[j];
		while(trav!=NULL)
			{
			relax(j,trav->v,trav->w);
			trav = trav->next;
			}
		}
	}

	for(int i=0;i<n-1;i++){
		trav = G.vertex[i];
		while(trav!=NULL)
			{
			if(d[trav->v]> (d[i]+ trav->w))
				return 0;
			trav=trav->next;
			}
	}

	return 1;
}
void shortest_path(graph& G,int s,int v){

	if(v==s)
		cout<<s<<" ";
	else if(parent[v]==NIL)
		cout<<"No path exists between "<<s<<" and "<<v;
	else {
		shortest_path(G,s,parent[v]);
		cout<<v<<" ";
	}
}
void print_paths(graph& G,int n,int s){

	for(int i=0;i<n;i++){
		cout<<"vertex "<<i<<": ";
		shortest_path(G,s,i);
		cout<<"cost: "<<d[i];
		cout<<"\n";
	}
}
