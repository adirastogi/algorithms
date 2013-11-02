
#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
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
int* parent,*set,**a;//a is the queue
int heap_size =0;
void min_heap_ins(int& key);
int min_heap_del();
void init_graph(graph& G,int n,int y);
void print_graph(graph& G,int n);
void dijkstra(graph& G,int n,int s);
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
	dijkstra(G,n,s);
	clock_t end = clock();
	cout<<"\nThe shortest paths from source vertex "<<s<<" are\n";
	print_paths(G,n,s);
	cout<<"\nExecution time : "<<((double)(end-start)/CLOCKS_PER_SEC);
    return 0;

}
void min_heap_ins(int& key){

	int ptr,par;
	heap_size++;
    ptr = heap_size;
	while(ptr>1){
		par = ptr/2;
		if(key>=(*a[par])){
			a[ptr] = &key;
			return;
		}
		a[ptr] = a[par];
		ptr = par;
	}
	a[1] = &key;
	return;

}
int min_heap_del(){

	if(heap_size<1){
		return -1;
	}

	int ptr,l,r;
	int* temp,*last;
	temp = a[1];
	last = a[heap_size];
	heap_size--;
	ptr=1;
	l=2;
	r=3;
	while(r<=heap_size){
		if((*last<=*a[l])&&(*last<=*a[r]))
			{
			a[ptr]=last;
			return temp-d;
			}
		if(*a[r]>=*a[l]){
			a[ptr]=a[l];
			ptr=l;
		}
		else{
			a[ptr]=a[r];
			ptr=r;
		}
		l =2*ptr;
		r =l+1;
	}
	if((l==heap_size)&&(*last>*a[l])){
		a[ptr]=a[l];
		ptr = l;
	}
	a[ptr]=last;
	return temp-d;
}
void init_graph(graph& G,int n,int y){

	int v,w=1,x;
	G.vertex =  new node*[n];
	d = new int[n];
	parent = new int[n];
	set = new int[n];
	a = new int*[n+1];
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
void dijkstra(graph& G,int n,int s){

	int u,k=-1;
	node* trav;
	d[s]=0;
	for(int i=0;i<n;i++)
		min_heap_ins(d[i]);
	while((u=min_heap_del())!=-1){
		set[++k]=u;
		trav = G.vertex[u];
			while(trav!=NULL)
				{
				relax(u,trav->v,trav->w);
				trav = trav->next;
				}

	}

}
void shortest_path(graph& G,int s,int v){

	if(v==s)
		cout<<s<<" ";
	else if(parent[v]==NIL)
		cout<<"No path exists between "<<s<<" and "<<v<<" ";
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

