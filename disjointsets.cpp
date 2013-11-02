
#include<iostream>
#include<stdlib.h>
#include<time.h>
#define MAX_ELEMENTS 100
using namespace std;
struct element{
	int data;
	int rank;
	element* parent;
};
element e[MAX_ELEMENTS];
int n = 0;
void make_set(int x);
void link(element& x,element& y);
void union_set(int x,int y);
element* find_set(int x);
int main(){

	int ans,i,j;
	clock_t start,end;
	start = clock();
	do
	{
		cout<<"\n1.Make set";
		cout<<"\n2.Find set";
		cout<<"\n3.Union sets";
		cout<<"\n4.Exit";
		cout<<"\n Enter your choice(1-5):";
		cin>>ans;
		switch(ans)
		{
			case 1:cout<<"\n enter an element: ";;
			       cin>>i;
			       if(i<0||i>MAX_ELEMENTS-1)
					cout<<"Invalid value of the element";
			       else
					make_set(i);
			       break;
			case 2:cout<<"\n enter an element whose representative element is to be found:";
			       cin>>i;
			       if(i<0||i>MAX_ELEMENTS-1)
			      	cout<<"Invalid value of the element";
			       else
					cout<<"Representative element of "<<i<<" is:"<<((find_set(i))->data);
			       break;
			case 3:cout<<"\n enter an element: ";
			       cin>>i;
			       cout<<"\n enter another element: ";
			       cin>>j;
			       if(i<0||i>(MAX_ELEMENTS-1)||j<0||j>(MAX_ELEMENTS-1))
					cout<<"Invalid value of the element";
			       else
					union_set(i,j);
			       break;
			case 4:exit(0);break;
			default:cout<<"Invalid choice";
		}
	}while(ans>=1&&ans<=4);
        end = clock();
	cout<<"\nExecution time : "<<((double)(end-start)/CLOCKS_PER_SEC);
}
void make_set(int x){

	n++;
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

