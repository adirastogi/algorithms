#include<iostream>
using namespace std;
struct node{

	int data;
	node* next;

};

void insertbeg(node** head,node* n){
    if(*head == NULL){
		*head = n; 
		return;
	}
	else{
		n->next = *head; 
		*head = n; 
		return;
	}
	
}
void unlinknode(node* ptr, node* prev){
     prev->next = ptr->next;
     ptr->next = NULL;
}
void listqsort(node** head, node* null_ptr){
   
   if(*head==null_ptr)
	   return;
	
   node* prev;
   node* ptr = *head ;
   node* x = *head;
   while(ptr!=null_ptr){
   
		if(ptr->data<x->data){
			unlinknode(ptr,prev);
			insertbeg(head,ptr);
			ptr = prev;
		}
     
		prev = ptr;
		ptr =ptr->next;
     
   }
   
   listqsort(head,x);
   listqsort(&(x->next),null_ptr);

}
node** reverse(node** head){
	node* h = *head;
	//node** nexthead = &(h->next);
	if(h->next==NULL)
		return head;
	node* tail_reversed = h->next;
	node** head_reversed  = reverse(&tail_reversed);
	tail_reversed->next = h;
	h->next = NULL;
	return head_reversed;
}
int ispalindrome(node** head){

	/*single or no element in list*/
	if(!(*head) || (*head)->next==NULL )
		return 1;

	/*find the middle of the list*/
	int retcode = 0;
	node* slow=*head, *fast = *head;
	while(fast->next && fast->next->next){
		fast = fast->next->next;
		slow = slow->next;
	}

	/*reverse the second half*/
	node* nextnode = slow->next;
	node** head2 = &nextnode;
	head2 = reverse(head2);
	slow->next = NULL;
	node* trav1 = *head;
	node* trav2 = *head2;

	/*compare the two halves*/
	while(trav1 && trav2 &&  trav1->data == trav2->data ){
		trav1 = trav1->next;
		trav2 = trav2->next;
	}


	/*if they are palindromes, trav2 must have reached the end of the second list*/
	if(!trav2)retcode = 1;
	else retcode = 0;

	/*put the halves back together*/
	head2 = reverse(head2);
	slow->next = *head2;

	return retcode;
}
int main(){

	node** head = new node*;
	*head = NULL;	

	int a[] = {2,3};
	for(int i=0;i<2;i++){
		node* n = new node;
		n->data = a[i];
		n->next = NULL;
		insertbeg(head,n);	
	}

	//listqsort(head,NULL);
	node* ptr = *head;
	while(ptr){
		cout<<ptr->data<<"\t";
		ptr = ptr->next;
	}

	cout<<"The list is ";
	ispalindrome(head)?cout<<"a palindrome\n":cout<<"not a plaindrome\n";

}
