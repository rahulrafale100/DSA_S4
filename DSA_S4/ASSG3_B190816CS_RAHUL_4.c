#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	int degree;
	struct node *left;
	struct node *right_sibling;
	struct node *parent;
};
struct heap{
	struct node *head;
};
struct q_node
{
	struct node *info;
	struct q_node *link;
};
struct queue
{
	int size;
	struct q_node *front;
	struct q_node *back;
};

typedef struct node *Node;
typedef struct heap *Heap;
typedef struct q_node *qn;
typedef struct queue *Q;
 Node Node_list[1000001][2];
 
qn create_queue_node(Node p)
{
	qn n;
	n = (qn)malloc(sizeof(struct q_node));
	n->info =p;
	n->link = NULL;
	return n;
}

Q form_queue()
{
	Q  n;
	n = (Q)malloc(sizeof(struct queue));
	n->front =NULL; 
	n->back= NULL;
	n->size = 0;
	return n;
}

int empty(Q q)
{
	return (q->size == 0);
}

Q enqueue(Q q, Node x)
{
	qn new_node = create_queue_node(x);
	if(q->front==NULL)
	{
		q->front = new_node;
		q->back = new_node;
		q->size++;
		return q;
	}
	q->back->link = new_node;
	q->back = new_node;
	q->size++;
	return q;
}

qn dequeue(Q q)
{
	qn ans = q->front;
	q->front = q->front->link;
	q->size--;
	return ans;
}

Heap make_heap(){
	Heap H;
	H=(Heap)malloc(sizeof(struct heap));
	H->head=NULL;
	return H;
}
Node create_node(int k){
	Node x;
	x=(Node)malloc(sizeof(struct node));
	x->data=k;
	x->degree=0;
	x->left=NULL;
	x->parent=NULL;
	x->right_sibling=NULL;
	return x;
}
Heap insert_before(Heap h,Node x){
	if(h->head==NULL)
	{
		h->head=x;
		h->head->right_sibling=NULL;
		return h;
	}
	x->right_sibling=h->head;
	h->head=x;
	return h;
}
Heap link_it(Heap H,Node x){
	if(H->head==NULL){
		H->head=x;
		H->head->right_sibling=NULL;
		return H;
	}
	Node z;
	z=H->head;
	while(z->right_sibling!=NULL){
		z=z->right_sibling;
	}
	z->right_sibling=x;
	x->right_sibling=NULL;
	return H;
}
Heap merge_heap(Heap H1,Heap H2){
	Heap Hk;
	Hk=make_heap();
	Node n1,n2;
	n1=H1->head;n2=H2->head;
	while(n1!=NULL&&n2!=NULL){
		if(n1->degree<n2->degree){
			Node temp;
			temp=n1->right_sibling;
			Hk=link_it(Hk,n1);
			n1=temp;
		}
		else{
				Node temp;
			temp=n2->right_sibling;
			Hk=link_it(Hk,n2);
			n2=temp;
		}
	}
	if(n1!=NULL){
		while(n1!=NULL){
				Node temp;
			temp=n1->right_sibling;
			Hk=link_it(Hk,n1);
			n1=temp;
		}
	}
	if(n2!=NULL){
		while(n2!=NULL){
			Node temp;
			temp=n2->right_sibling;
			Hk=link_it(Hk,n2);
			n2=temp;
		}
	}
	return Hk;
}

Heap union_heap(Heap H1,Heap H2){
	Heap z;
	z=(Heap)malloc(sizeof(struct heap));
	z=merge_heap(H1,H2);
	if(z->head==NULL)
		return z;
		Node prev=NULL;
		Node p=z->head;
		Node next=p->right_sibling;
	while(next!=NULL){
		if(p->degree!=next->degree||(next->right_sibling!=NULL&&next->right_sibling->degree==p->degree)){
			prev=p;
			p=next;
		}
		else{
			if(p->data<=next->data){
				p->right_sibling=next->right_sibling;
				next->right_sibling=p->left;
				next->parent=p;
				p->left=next;
				p->degree++;
			}
			else{
				if(prev==NULL)
					z->head=next;
				else
					prev->right_sibling=next;
					
			
				p->right_sibling=next->left;
				p->parent=next;
				next->left=p;
				next->degree++;
				p=next;
				}
			}
			next=p->right_sibling;
		}
	return z;
	
}
Heap link_node(Heap H1,int k){
	Node z=create_node(k);
	if(H1->head==NULL){
		H1->head=z;
		return H1;
	}
	Node p;
	p=H1->head;
	while(p->right_sibling!=NULL){
		p=p->right_sibling;
	}
	p->right_sibling=z;
	return H1;
}
Heap insert(Heap H,int k){
	Heap H1;
	H1=make_heap();
	H1=link_node(H1,k);
	if(k>=0)
	Node_list[k][0]=H1->head;
	else
	Node_list[abs(k)][1]=H1->head;
	H=union_heap(H,H1);
	return H;
}
Node minimum(Heap H){
	int value=100000000;
	Node x=H->head;
	Node k=NULL;
	while(x!=NULL){
		if(x->data<=value)
		{
			value=x->data;
			k=x;
		}
		x=x->right_sibling;
	}
	return k;
}
Node extract_min(Heap H){
	Node min_ptr=minimum(H);
	if(min_ptr==NULL){
		printf("-1\n");
		return min_ptr;
	}
	else{
	//	printf("%d\n",min_ptr->data);
	int k=min_ptr->data;
	if(k>=0)
	Node_list[k][0]=NULL;
	else
	Node_list[abs(k)][1]=NULL;
		Node curr=H->head;
		Node prev=NULL;
		Node temp;
		while(curr!=NULL&&curr!=min_ptr){
			prev=curr;
			curr=curr->right_sibling;
		}
		if(curr!=NULL){
			if(prev==NULL)
				H->head=curr->right_sibling;
				else
				prev->right_sibling=curr->right_sibling;
		}
		Heap H1;
		H1=make_heap();
		temp=min_ptr->left;
		while(temp!=NULL){
			Node k=temp->right_sibling;
			H1=insert_before(H1,temp);
			temp=k;
		}
		Heap H2;
		H2=union_heap(H,H1);
		return H2->head;
	}
}
Heap decrease_key(Heap H,Node x,int k ){
	if(k>x->data){
		printf("-1\n");
		return H;
	}
	else{
		int q;
		q=x->data-abs(k);
	//	printf("%d\n",q);
		Node t;
        if(x->data>=0)
		t=Node_list[x->data][0];
        else
        t=Node_list[abs(x->data)][1];
        if(x->data>=0)
		Node_list[abs(x->data)][0]=NULL;
        if(x->data<0)
        Node_list[abs(x->data)][1]=NULL;
		x->data=x->data-abs(k);
		Node y=x->parent;
        if(x->data>=0)
			Node_list[x->data][0]=x;
            else
            Node_list[abs(x->data)][1]=x;
		
		while(y!=NULL&&y->data>x->data){
            if(x->data>=0)
			Node_list[x->data][0]=y;
            else
            Node_list[abs(x->data)][1]=y;
            if(y->data>=0)
            Node_list[y->data][0]=x;
            else
			Node_list[abs(y->data)][1]=x;
			int b=x->data;
			x->data=y->data;
			y->data=b;
			x=y;
			y=x->parent;
		}
	
		return H;
	}
}
Heap delete_node(Heap H,Node x){
	if(x==NULL){
		printf("-1\n");
		return H;
	}
	else{
		int q=x->data;
		printf("%d\n",q);
		H=decrease_key(H,x,-100000);
		H->head=extract_min(H);
		return H;
	}
}

void print_binomial_heap(Heap H)
{
	Node h=H->head;
	Node t=NULL;
	while(h!=NULL){
		printf("%d ",h->data);
		if(h->left!=NULL)
		t=h->left;
	Q myqueue;
	myqueue = form_queue();
	if (t)
		myqueue = enqueue(myqueue,t);
	while(!empty(myqueue))
	{
		Node curr = dequeue(myqueue)->info;
		while(curr!=NULL)
		{
			printf("%d ",curr->data);
			if(curr->left)
				myqueue = enqueue(myqueue,curr->left);
			curr = curr->right_sibling;
		}
	}
	h=h->right_sibling;
//	printf("%d ",h->data);
	}
}
int main(){
	Heap H;
	H=make_heap();
	char c;
	int k;
	while(1){
		scanf("%c",&c);
		if(c=='i'){
			scanf("%d",&k);
			H=insert(H,k);
		}
		if(c=='m'){
			Node x;
			x=minimum(H);
			if(x==NULL)
			printf("-1\n");
			else{
				printf("%d\n",x->data);
			}
		}
		if(c=='x'){
			Node x=NULL,g;
			g=minimum(H);
			if(g!=NULL){
				printf("%d\n",g->data);
			x=extract_min( H);}
			if(x!=NULL)
			H->head=x;	
		}
		if(c=='r'){
			int y,z;
			scanf("%d%d",&y,&z);
            Node x;
			if(y>=0)
			x=Node_list[y][0];
            else
            x=Node_list[abs(y)][1];
			if(x==0)
			printf("-1\n");
			else{
				if(y>=z)
				printf("%d\n",y-z);
			H=decrease_key(H,x,z);
			}
		}
		if(c=='d'){
			scanf("%d",&k);
			Node x=NULL;
            if(k>=0)
			x=Node_list[k][0];
            else
            x=Node_list[abs(k)][1];
			H=delete_node(H,x);
		}
		if(c=='p'){
			print_binomial_heap(H);
			printf("\n");
		}
		if(c=='e')
		return 0;
	}
}
