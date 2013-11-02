#include<iostream>

using namespace std;

struct node{
	node* left;
	node* right;
	node* parent;
	int data;
};

void insert(node* root, node* n){

	if(n->data<root->data)
		if(root->left==NULL){
			root->left = n;
			n->parent = root;
		}
		else
			insert(root->left,n);
	else if(n->data>root->data)
		if(root->right==NULL){
			root->right = n;
			n->parent = root;
		}
		else
			insert(root->right,n);
}

void inorder(node* root){
	if(root==NULL)
		return;
	else{
		inorder(root->left);
		cout<<"\t"<<root->data;
		inorder(root->right);
	}

}
node* get_new_node(int number){
	
	node* n = new node;
	n->data = number;
	n->parent = NULL;
	n->right = NULL;
	n->left = NULL;
	return n;	

}

int diameter(node* root, int* height){
	if(root==NULL){
		*height = 0;
		return 0;
	}

	if(root->left==NULL && root->right==NULL){
		*height = 1;
		return 1;
	}

	else{
		int height_l,height_r;
		diameter(root->left,&height_l);
		diameter(root->right,&height_r);
		*height = ((height_l>height_r)?height_l:height_r)+1;
		return height_l+height_r+1;

	}
	


}
int main(){

	int arr[] = {12,45,646,21,123,522,121,535,75,2};
	node* root = get_new_node(arr[0]);
	for(int i=1;i<10;i++){
		insert(root,get_new_node(arr[i]));
	}
	//inorder(root);
	cout<<endl;
	int h;
	int k = diameter(root,&h);
	cout<<"d:\t"<<k<<"h:\t"<<h;
		//inorder(root);
	cout<<endl;
	return 0;
}