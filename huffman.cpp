#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<string>
#define NODE_CHAR EOF
using namespace std;
struct node{
	float f;
	char ch;
	int left;
	int right;
};
int heap_size;
node* b;
char path[100];
void min_heap_ins(node* a,node key);
node min_heap_del(node* a);
int encode(node* a,int n);
void traverse(int k);
int main(){

	int n=7,i,j;
	node* a;
	cout<<"Enter the number of alphabets\n";
	cin>>n;
	n++;
	a = new node[n];
	heap_size=0;
	cout<<"Enter the character frequencies for each of the alphabets\n";
	for(i=1;i<n;i++){
		node t;
		cin>>t.f;
		min_heap_ins(a,t);
	}

	cout<<"The huffman codes are\n";
	clock_t start = clock();
	traverse(encode(a,n));
	clock_t end = clock();
	cout<<"\nExecution time : "<<((double)(end-start)/CLOCKS_PER_SEC);

}
void min_heap_ins(node* a,node key){

	int ptr,par;
	heap_size++;
    ptr = heap_size;
	while(ptr>1){
		par = ptr/2;
		if(key.f>=a[par].f){
			a[ptr] = key;
			return;
		}
		a[ptr] = a[par];
		ptr = par;
	}
	a[1] = key;
	return;

}
node min_heap_del(node* a){

	if(heap_size<1){
		cout<<"\nHeap is Empty";
		exit(0);
	}

	int ptr,l,r;
	node temp,last;
	temp = a[1];
	last = a[heap_size];
	heap_size--;
	ptr=1;
	l=2;
	r=3;
	while(r<=heap_size){
		if((last.f<=a[l].f)&&(last.f<=a[r].f))
			{a[ptr]=last;return temp;}
		if(a[r].f>=a[l].f){
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
	if((l==heap_size)&&(last.f>a[l].f)){
		a[ptr]=a[l];
		ptr = l;
	}
	a[ptr]=last;
	return temp;
}
int encode(node* a,int n){

	b = new node[2*n];//index from 0
	int k=-1,i;
	for(i=1;i<n-1;i++){
		node z;
		z.ch = NODE_CHAR;
		z.f = 0;

		b[++k] = min_heap_del(a);
		z.left = k;
		z.f = z.f+b[k].f;

		b[++k] = min_heap_del(a);
		z.right = k;
		z.f = z.f +b[k].f;

		min_heap_ins(a,z);

	}
	b[++k] = a[1];
	return k;
}
void traverse(int k){
  static int i = -1;

	if(b[k].ch!=NODE_CHAR){
		path[i+1] ='\0';
		cout<<b[k].f<<":"<<path<<"\n";
		return;
	}
	else{
		path[++i]='0';
		traverse(b[k].left);
		i--;
		path[++i]='1';
		traverse(b[k].right);
		i--;
	}

}
