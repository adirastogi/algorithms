
#include<iostream>
#include<stdlib.h>
#include<time.h>
#define INFINITY 100000
using namespace std;
struct node{
	float key;
	node* left;
	node* right;
};
void optimal_bst(float* p,float* q,int n);
node* build_tree(int i,int j);
node* get_dummy(float d);
void traverse(node* r);

float* dummy;
float* keys;
int** root;
int main(){


	int n,i,j;
	float* p;
	float* q;
	cout<<"Enter the No of Keys in the Tree\n";
	cin>>n;
	n++;
    keys = new float[n];//index from 1
    p = new float[n];//index from 1
    q = new float[n];
    dummy = new float[n];
    if(keys==NULL||p==NULL||q==NULL||dummy==NULL){cout<<"Error!";exit(0);}

    cout<<"Enter the key values in sorted order\n";
    for(i=1;i<n;i++)
    	cin>>keys[i];
    cout<<"Enter the probabilities p(i) for the keys\n";
    for(i=1;i<n;i++)
        cin>>p[i];
    cout<<"Enter the probabilities q(i) for the dummy keys\n";
    for(i=0;i<n;i++)
        cin>>q[i];
    for(i=0;i<n;i++){
    	if(i==0)
    		dummy[0] = keys[1]-1;
    	else if(i==n-1)
    		dummy[n-1] = keys[n-1]+1;
    	else{
    		dummy[i] = (keys[i]+keys[i+1])/2;
    	}
    }
    cout<<"\nThe dummy keys are:\n";
    for(i=0;i<n;i++)
        cout<<dummy[i]<<"\t";

    clock_t start = clock();
    optimal_bst(p,q,n);
    clock_t end = clock();

    cout<<"\nThe root matrix is\n";
    for(i=0;i<n;i++){
    	for(j=0;j<n;j++)
    		cout<<root[i][j]<<" ";
    		cout<<"\n";
    	}

    cout<<"The constructed tree is:\n";
    traverse(build_tree(1,n-1));

   cout<<"\nExecution time : "<<((double)(end-start)/CLOCKS_PER_SEC);

    return 0;

}
void optimal_bst(float* p,float* q,int n){

	int i,j,l,r;
	float temp;
	float** e = new float*[n+1];
	float** w = new float*[n+1];
     root = new int*[n];
	for(i=0;i<n+1;i++){
		e[i] =new float[n];
		w[i] =new float[n];
	}
	for(i=0;i<n;i++)
		root[i] = new int[n];
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			root[i][j]=0;
	}

	for(i=1;i<n+1;i++){
		e[i][i-1] = q[i-1];
		w[i][i-1] = q[i-1];
    }

	for(l=1;l<n;l++){
		for(i=1;i<n-l+1;i++){
			j = l+i-1;
			e[i][j] = INFINITY;
			w[i][j] = w[i][j-1]+p[j]+q[j];
			for(r=i;r<=j;r++){
				temp = e[i][r-1]+e[r+1][j]+w[i][j];
				if(temp<e[i][j]){
					e[i][j]= temp;
					root[i][j] = r;
				}
			}

		}
	}

}
node* build_tree(int i,int j){

	if(i==j){
		node* n = new node;
		n->left = get_dummy(dummy[i-1]);
		n->right = get_dummy(dummy[i]);
		n->key = keys[i];
		return n;
	}
	else{
		int r= root[i][j];
		node* n = new node;
		n->key = keys[r];
		if(r==i){
			n->left = get_dummy(dummy[r-1]);
			n->right = build_tree(r+1,j);
		}
		else if(r==j){
			n->right = get_dummy(dummy[r]);
			n->left = build_tree(i,r-1);
		}
		else{
			n->left = build_tree(i,r-1);
			n->right = build_tree(r+1,j);
		}

		return n;

	}

}
node* get_dummy(float  d){
	node* n = new node;
	n->left = NULL;
	n->right = NULL;
	n->key = d;
	return n;
}
void traverse(node* r){

	if(r==NULL)
		return;
	else{
		traverse(r->left);
		cout<<r->key<<"\t";
		traverse(r->right);
	}
}
