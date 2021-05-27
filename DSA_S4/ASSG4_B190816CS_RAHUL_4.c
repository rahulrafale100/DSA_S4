#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node *next;
	struct node *parent;
	char c;
};
struct Adjacent_list{
	int d;
	struct Adjacent_list *right;
};
struct graph{
	int n;
	struct Adjacent_list *root[1000];
	struct node *head[1000];
};
typedef struct node *Node;
typedef struct graph *Graph;
typedef struct Adjacent_list *Adj;
struct Queue_node{
	struct Adjacent_list *information;
	struct Queue_node *link;
};
struct Queue{
	int size;
	struct Queue_node *front;
	struct Queue_node *back;
};
typedef struct Queue_node *q_node;
typedef struct Queue *Q;
q_node create_q_node(Adj p){
	q_node z;
	z=(q_node)malloc(sizeof(struct Queue_node));
	z->information=p;
	z->link=NULL;
	return z;
}
Q form_queue(){
	Q z;
	z=(Q)malloc(sizeof(struct Queue));
	z->back=NULL;
	z->front=NULL;
	z->size=0;
	return z;
}
int empty(Q p){
	return (p->size==0);
}
Q enqueue(Q q,Adj x){
	q_node z;
	z=create_q_node(x);
	if(q->front==NULL){
	q->front=z;
	q->back=z;
	q->size++;
	return q;
	}
	q->back->link=z;
	q->back=z;
	q->size++;
	return q;
}
q_node dequeue(Q q){
	q_node x;
	x=q->front;
	q->front=q->front->link;
	q->size--;
	return x;
}
Adj create_node_adj(int k){
	Adj p;
	p=(Adj)malloc(sizeof(struct Adjacent_list));
	p->d=k;
	p->right=NULL;
	return p;
}
Node create_node(int x){
	Node z;
	z=(Node)malloc(sizeof(struct node));
	z->data=x;
	z->c='W';
	z->next=NULL;
	z->parent=NULL;
	return z;
}
void BFS(Graph G,Adj s){
	Node gn;
	gn=G->head[s->d];
	gn->c='G';
	gn->parent=NULL;
	printf("%d ",gn->data);
	Q q;
	q=form_queue();
	q=enqueue(q,s);
	while(!empty(q)){
		q_node p;
		p=dequeue(q);
		Adj x;
		x=p->information;
		int f=x->d;
		Adj v=G->root[f];
	//	v=v->right;
		while(v!=NULL){
			Node u=G->head[v->d];
			if(u->c=='W'){
				u->c='G';
				u->parent=G->head[x->d];
				printf("%d ",u->data);
				q=enqueue(q,v);
			}	
			v=v->right;
		}
		Node w;
		w=G->head[x->d];
		w->c='B';
	}
}
void DFS_Visit(Graph G,Node u){
	u->c='G';
	printf("%d ",u->data);
	Adj v;
	v=G->root[u->data];
	while(v!=NULL){
		Node x;
		x=G->head[v->d];
		if(x->c=='W'){
			x->parent=u;
			DFS_Visit(G,x);
		}
		v=v->right;
	}
	u->c='B';
}
void DFS(Graph G){
	for(int i=0;i<G->n;i++){
		Node u;
		u=G->head[i];
		if(u->c=='W'){
			//printf("%d ",u->data);
			DFS_Visit(G,u);
		}
	}
}
int main(){
	Graph G;
	G=(Graph)malloc(sizeof(struct graph));
	int n,m;
	scanf("%d%d",&n,&m);
	G->n=n;
	for(int i=0;i<n;i++){
		Node k;
		k=create_node(i);
		Adj t;
		t=create_node_adj(i);
		G->head[i]=k;
	//	G->root[i]=t;
	}
	for(int i=0;i<m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		Adj z;
		z=create_node_adj(y);
		Adj k;
		k=G->root[x];
		if(k==NULL){
			G->root[x]=z;
		}
		else{
			while(k->right!=NULL){
				k=k->right;
			//	printf("%d ",k->data);
			}
			k->right=z;
		}
	}
	int src;
	scanf("%d",&src);
	Adj p;
	p=G->root[src];
	BFS(G,p);
	printf("\n");
		for(int i=0;i<n;i++){
	Node p=G->head[i];
	p->c='W';
	}
	DFS(G);
	printf("\n");
//	for(int i=0;i<n;i++){
//	printf("%d ",i);
//		Adj z;
//		z=G->root[i];
//		while(z!=NULL){
//			printf("%d ",z->d);
//			z=z->right;
//		}
//	printf("\n");
//	}

	
}
