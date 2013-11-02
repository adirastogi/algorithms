
#include<iostream>
using namespace std;
struct node{
        int data;
        node* next;
};

void insertBeg(node** head,node* n){
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

void loopTailTo(node* head,node* knot){

        if(head==NULL)
                return;

        //get to end
        node* trav = head;
        while(trav->next)
                trav = trav->next;

        //tie knot
        trav->next = knot;

}

bool listLoop(node* head, bool fixLoop){
	
	node* fast, *slow;
        fast = slow = head;

        //single or no node in LL(to guard against null for fast)
        if(!head ||!head->next)
                return false;

        do{
                slow = slow->next;
                fast = fast->next->next;
        }while(slow!=fast && fast->next && fast->next->next);

        if(slow==fast){
		cout<<"\nfound loop at:"<<slow->data;
                if(fixLoop){
			cout<<"\nfixing the loop:";
			if(slow==head){
				cout<<"\ncomplete loop. breaking at head..";
				node* trav=head;
				while(trav->next!=head) trav = trav->next;
				trav->next = NULL;
				cout<<"\nknot broken at: "<<trav->data;
				
			}
			else{
				cout<<"\nlist is a lasso. breaking at knot point..";
				node* trav = head;
				while(trav->next!=slow->next){
					cout<<"\n"<<trav->data<<"\t"<<slow->data;
					trav = trav->next;
					slow = slow->next;
				}
				slow->next = NULL;
				cout<<"\nknot broken at : "<<slow->next->data<<" to : "<<trav->next->data;
			}
		}
		return true;
	}	
	else{
		cout<<"\nfound no loop";
	 	return false;
	}

}
void printList(node* head){
	node* trav = head;
	while(trav)
		cout<<trav->data<<"  ";
}
int main(){

        int a[10] = {32,4,2,5,64,89,1,12,56,21};
	//int a[1] = {50};        
	node* head = NULL;
        node* knot = NULL;
        for(int i=0;i<10;i++){
                node* n = new node;
                n->data = a[i];
                n->next=NULL;
                if(n->data==64)
                        knot = n;
                insertBeg(&head,n);
        }
        loopTailTo(head,knot);
        bool x = listLoop(head,true);
	cout<<"\n";
	printList(head);	
        

}
