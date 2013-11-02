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
node * merge(node *a, node *b)
{
	node *i, *j, *k, *c;
	c = new node;
	k = new node ;
	i = a;
	j = b;
	node* tail = k->next;
	while(i!=NULL && j!=NULL)
	{
		if(i->data < j->data)
		{
			tail->next=i;
			tail =i ;
			i=i->next;
		}
		else
		{
			k->next=j;
			tail = j;
			j=j->next;
		}
	}
	if(i!=NULL)
		tail->next=i;
	else
		tail->next=j;
	return(k->next);
}
node* mergelist(node* head){

	if(!head || !(head->next))
		return 0;
	int increasing = 0;

	if(head->next->data > head->data)
		increasing = 1;

	node* trav = head;
	while(trav->next){
		if(increasing && trav->next->data > trav->data)
			trav = trav->next;
		else break;
	}

	node* head1 = head;
	node* head2 = trav->next;
	trav->next = NULL;
	return merge(head1,head2);
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

	int a[] = {2,1,5,4,3,2,1};
	node* head = NULL;


	for(int i=0;i<7;i++){
		node* n = new node ;
		insert(head,a[i]);
	}
	cout<<"Original list\n";
	print_list(head);

	node * ml = mergelist(head);
	//node* rev_head = reverse_list(head,4);
	//trav = rev_head;

	cout<<"\nreversed list\n";

}
