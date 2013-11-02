#include<iostream>

//traversal codes for a BST
#define LNR 0
#define RNL 1
#define	NLR 2
#define	LRN 3
#define RLN 4
#define NRL 5

//utility min max functions
#define MAX(a,b,c) (((a)->data >(b)->data)?(((a)->data > (c)->data)?(a):(c)):(((b)->data > (c)->data)?(b):(c)))
#define MIN(a,b,c) (((a)->data <(b)->data)?(((a)->data < (c)->data)?(a):(c)):(((b)->data < (c)->data)?(b):(c)))
using namespace std;

//Binary Search Tree data structure
struct node{
	node* left;
	node* right;
	node* parent;
	int data;
};

//calculate the diameter of a binary tree

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

//find the maximum BST stubtree in a Binary Tree
node* maxbstsubtree(node* root, int& minval, int& maxval, int& count){

  if(!root){
     minval = INT_MAX;
     maxval = INT_MIN;
     count= 0;
     return NULL;
  
  }

  if(!root->left && !root->right){
     count =1;
     minval = root->data;
     maxval = root->data;
     return root;
  }
  

  int maxl, minl, maxr, minr,countl,countr;
  
  node* left = maxbstsubtree(root->left,minl,maxl,countl);
  node* right = maxbstsubtree(root->right,minr,maxr,countr);
  
  if(left==root->left && maxl<root->data && right==root->right && minr>root->data){
  
     count = countl + countr +1;
	 //INT_MAX and INT_MIN will be returned by a null node. make sure they are not passed on
     minval = (minl==INT_MAX)?root->data:minl;
     maxval = (maxr==INT_MIN)?root->data:maxr;
     return root;
  }
  else if(countl > countr){
     count = countl;
     minval = minl;
     maxval = maxl;
     return left;
  }
  else if(countr >= countl){
     count = countr;
     minval = minr;
     maxval = maxr;
     return right;
  } 
 
}

//convert a binary search tree to a linked list
void bst_to_list(node* root, node*& head, node*& tail){
	
	if(!root){
		head = tail = NULL;
		return ;
	}

	if(!root->left&&!root->right){
		head = root;
		tail = root;
		return;
	}

	node* lhead,*ltail,*rhead,*rtail;
	
	bst_to_list(root->left,lhead,ltail);
	bst_to_list(root->right,rhead,rtail);
	
	if(ltail)
		ltail->right = root;
	root->left = ltail;
	if(rhead)
		rhead->left = root;
	root->right = rhead;

	head = (lhead)?lhead:root;
	tail = (rtail)?rtail:root;
	return;

}

//convert a linked list to a binary search tree
node* list_to_bst(node* head,node* tail){
	
	if(!head)
		return NULL;

	if(head==tail){
		head->left=head->right = NULL;
		return head;
	}
	else if(tail->right == head) return NULL;
		//left sublist empty(no case for empty right sublist because of floor partition)
		


	//find middle of list
	int check = 0;
	node* current, * mid;
	mid =current = head;
	while(current!=tail){
		current = current->right;
		check = (check+1)%2;
		if(check==0)
			mid =mid->right;
	}

	node* root = mid;
	node* left = list_to_bst(head,root->left);
	node* right = list_to_bst(root->right,tail);
	root->left = left;
	root->right = right;
	return root;

}

//clear the tree , i.e. delete the tree
void clear_tree(node* root){
	
	if(root==NULL)
		return;
	else{
		clear_tree(root->left);
		clear_tree(root->right);
	}
	
	if(root==root->parent->left)
		root->parent->left = NULL;
	else root->parent->right = NULL;

	delete root;
}

//get the successor of a node n in the Binary Search Tree
node* successor(node* root,node* n){
	if(n->right!=NULL){
		node* temp = n->right;
		while(temp->left!=NULL)
			temp = temp->left;
		return temp;
	}
	else{
		node* par = n->parent;
		while(par!=NULL && n==par->right){
			n = par;
			par = par->parent;
		}
		return par;
	}
}

//insert into a binary search tree
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

//find a value in binary search tree
node* find(node* root, int data){

	if(root==NULL)
		return NULL;
	else if (root->data==data)
		return root;
	else if (root->data<data)
		return find(root->right,data);
	else 
		return find(root->left,data);
}

//delete a node in the binary search tree
node* delete_node(node* root,node* n){
	

	node** par;
	//check if we are not deleting root accidentally by
	//using heuristic, we set the parent of root to itself.
	//so any updates to parent's left and right are made to root itself;
	if(n==root){
		node* temp = root;
		if(root->left==NULL && root->right==NULL)
			root= NULL;
		else if(n->left==NULL)
			root = root->right;
		else if(root->right==NULL)
			root = root->left;
		delete temp;
	}
		
			
	
	
		if(n->parent->right==n)
			par = &(n->parent->right);
		else
			par = &(n->parent->left);

		if(n->left==NULL && n->right==NULL){
			*par = NULL;
			delete n;
		}
		else if(n->left==NULL){
			*par = n->right;
			delete n;
		}else if(n->right==NULL){
			*par = n->left;
			delete n;
		}
		else {
			node* s = successor(root,n);
			n->data = s->data;
			delete_node(root,s);
		}
	return root;
	//the general case applies to root as well.
	
}

//get the predecessor node of a node in binary search tree
node* predecessor(node* root,node* n){
	
	if(n->left!=NULL){
		node* temp = n->left;
		while(temp->right!=NULL)
			temp = temp->right;
		return temp;
	}
	else{
		node* par = n->parent;
		while(par!=NULL && n==par->left){
			n = par;
			par = par->parent;
		}
		return par;
	}
}

//trim the binary search tree to contain values only between n1 and n2 - TBD
bool trim(node* root, int n1, int n2){
	
	node* pos1 = find(root,n1);
	node* pos2 = find(root,n2);

	if(pos1 ==NULL || pos2 ==NULL)
		return false;
	else{
		clear_tree(pos1->left);
		node* pre = predecessor(root,pos1);
		while(pre!=NULL){
			if(pre->left!=NULL)
				clear_tree(pre->left);
			node* temp = pre;
			pre = predecessor(root,pre);
			if(temp!=root)
				delete_node(root,temp);
		}
		//only one predecessor remains.either uts immeduate preecessor. or the
		//smallest element.

		clear_tree(pos2->right);
		node* suc = successor(root,pos2);
		while(suc!=NULL){
			if(suc->right!=NULL)
				clear_tree(suc->right);
			node* temp = suc;
			suc = successor(root,suc);
			if(temp!=root)
				delete_node(root,temp);
		}
		return true;
	}
	
}

//print inorder traversal of binary search tree
void inorder(node* root){
	if(root==NULL)
		return;
	else{
		inorder(root->left);
		cout<<root->data<<"\t";
		inorder(root->right);
	}

}

//allocate a new node 
node* get_new_node(int number){
	
	node* n = new node;
	n->data = number;
	n->parent = NULL;
	n->right = NULL;
	n->left = NULL;
	return n;	

}

//get the node order of three nodes in a Binary Search Tree
int node_order(node* left, node* root, node* right){

	bool lgtn = (left && left->data > root->data) || false;
	bool rgtn = (!right || right->data > root->data) && true;
	bool lgtr = (left && right && left->data > right->data) || false;  

	if(!lgtn && rgtn && !lgtr)
		return LNR;
	else if(!rgtn && lgtn && lgtr)
		return RNL;
	else if(lgtn && !lgtr && rgtn)
		return NLR;
	else if (!lgtr && !rgtn && !lgtn)
		return LRN;
	else if(lgtr && !lgtn && !rgtn)
		return RLN;
	else return NRL;
}

//find two nodes in a binary search tree whose values have been swapped
bool misplaced_nodes(node* root, node*& minval, node*& maxval){

	bool found_nodes = false;

	if(!root)
		return false;

	if(!(root->left )&&(!root->right)){
		minval = maxval = root;
		return false;
	}

	node* leftmin,*leftmax,*rightmin,*rightmax;
	leftmin = leftmax = rightmin = rightmax = NULL;
	bool found_left=false, found_right=false;

	if(root->left)
		found_left=misplaced_nodes(root->left,leftmin,leftmax);
	
	if(root->right)
		found_right=misplaced_nodes(root->right,rightmin,rightmax);
	
	//null checks to guard against null value comparison later
	leftmax = (leftmax)?leftmax:root;
	rightmin = (rightmin)?rightmin:root;
	leftmin = (leftmin)?leftmin:root;
	rightmin = (rightmin)?rightmin:root;


	if(found_left || found_right){
		found_nodes = true;
	}
	else{

		int order = node_order(leftmax,root,rightmin);
		if(order==LNR ||){
		//inorder is fine keep looking
			minval = MIN(leftmax,root,rightmin);
			maxval = MAX(leftmax,root,rightmin);
			found_nodes = false;
		}
		else if(order==RLN){
		//coninue, order is wrong but we need to pass the min and max
			found_nodes = false;
		}
		else if(order ==NRL){
		//coninue, order is wrong but we need to pass the min and max
			found_nodes = false;
		}
		else if(order==RNL){
		//left and right are the misplaced nodes
			found_nodes = true;
		}
		else if(order==NLR){
		//left and node are the misplaced nodes.
			found_nodes = true;
		}
		else if(order==LRN){
		//right and node are the misplced nodes.
			found_nodes = true;
		}
	}

	//if either of leftmax or rightmin is null, set them to root for 3way min/max com

	minval = MIN(leftmin,root,rightmin);
	maxval = MAX(leftmax,root,rightmax);
	
	return found_nodes;
}

int main(){

	int arr[] = {1234,45,646,21,123,522,121,535,75,2};
	node* root = get_new_node(arr[0]);
	for(int i=1;i<10;i++){
		insert(root,get_new_node(arr[i]));
	}
	cout<<"Inorder traversal of original tree\n";
	inorder(root);
	cout<<endl;
	
	/*cout<<"Traversal of generated Linked List\n";
	node* head=NULL,*tail=NULL;
	bst_to_list(root,head,tail);
	node* trav  = head;
	while(trav){
		cout<<trav->data<<"\t";
		trav = trav->right;
	}
	cout<<endl;
	
	cout<<"Inorder traversal of reconstructed tree\n";
	node* root2 = list_to_bst(head,tail);
	inorder(root2);
	*/
	node* n1, *n2;
	misplaced_nodes(root,n1,n2); 

	
	return 0;
}
