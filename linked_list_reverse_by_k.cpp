#include<iostream>
using namespace std;
struct node{
	int data;
	node* next;


};

//reverse the linked list k nodes at a time
node* reverse_list(node* head,int k){
	
	if(head==NULL)
		return NULL;

	node *p,*q,*r,*t;

	p = NULL;
	q = head;
	t = head;
	int count = 0;
	while(count<k && q){
		r = q->next;
		q->next = p;
		p = q;
		q = r;
		count++;
	}

	node* h = p;
	t->next = reverse_list(q,k);
	return h;

}

//insert node at beg
void insert(node*& head,int k){
	node* n= new node;
	n->data = k;
	n->next = NULL;

	if (head==NULL)
		head = n;
	else{

		n->next = head;
		head = n;
	}

}

//create linked lists of alternate odd and even nodes
void split_oddeven(node* head, node*& odd, node*& even){

	if(!head)
		return;

	node* p = odd  = head;
	node* q = even = head->next;

	while(1){

		if(!p->next->next || !q->next->next)
			break;
		p->next = p->next->next;
		q->next = q->next->next;
		p = p->next;
		q = q->next;
		

	}
	if(!p->next)
		q->next=NULL;
	else if(!q->next)
		p->next = NULL;
}




void print_list(node* head){

	node* trav = head;
	while(trav){
		cout<<trav->data<<"\t";
		trav = trav->next;
	}
	cout<<endl;
}

int main(){
	
	int a[] = {3,2,15,6,33,76,86,23,21};
	node* head = NULL;
	

	for(int i=0;i<9;i++){
		node* n = new node ;
		insert(head,a[i]);
	}
	cout<<"Original list\n";
	print_list(head);
	
	node* odd,*even;
	split_oddeven(head,odd,even);

	cout<<"odd list\n";
	print_list(odd);
	cout<<"even list\n";
	print_list(even);
	//int k = 2;
	//node* rev_head = reverse_list(head,4);
	//trav = rev_head;
	
	cout<<"\nreversed list\n";
	
}