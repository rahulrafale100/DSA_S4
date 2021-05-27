#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node *left;
	struct node *right;
	int height;
};
struct AVL{
	struct node *root;
};
typedef struct node *Node;
typedef struct AVL *Tree;
Node create_node(int k){
	Node z;
	z=(Node)malloc(sizeof(struct node));
	z->data=k;
	z->height=1;
	z->left=NULL;
	z->right=NULL;
	return z;
}
int maximum(int a,int b){
	if(a<b)
	return b;
	else
	return a;
}
int find_height(Node z){
	if(z==NULL)
	return 0;
	else
	return z->height;
}
Node find_node(Node x,int k){
	if(x->data==k)
	return x;
	else if(k<x->data)
	return find_node(x->left,k);
	else 
	return find_node(x->right,k);
}
int balance_factor(Node z){
	if(z==NULL)
	return 0;
	int p,q,r;
	p=find_height(z->left);
	q=find_height(z->right);
	r=p-q;
	return r;
}
Node do_left_rotate(Node x){
	Node p;
	p=x->right;
	x->right=p->left;
	p->left=x;
	x->height=1+maximum(find_height(x->left),find_height(x->right));
	p->height=1+maximum(find_height(p->left),find_height(p->right));
	return p;
}
Node do_right_rotate(Node x){
	Node p;
	p=x->left;
	x->left=p->right;
	p->right=x;
	x->height=1+maximum(find_height(x->left),find_height(x->right));
	p->height=1+maximum(find_height(p->left),find_height(p->right));
	return p;
}
Node insert_node(Node x,int k){
	if(x==NULL){
		return create_node(k);
	}
	else if(k<x->data){
		x->left=insert_node(x->left,k);
	}
	else{
		x->right=insert_node(x->right,k);
	}
	x->height=1+maximum(find_height(x->left),find_height(x->right));
	int d;
	d=balance_factor(x);
	if(d>1){
		if(k<x->left->data)
			return do_right_rotate(x);
			else{
				x->left=do_left_rotate(x->left);
				return do_right_rotate(x);
			}
	}
	if(d<-1){
		if(k>x->right->data)
			return do_left_rotate(x);
			else{
				x->right=do_right_rotate(x->right);
				return do_left_rotate(x);
			}
	}
	return x;
}
int do_search(Node x,int k){
	if(x==NULL)
	return 0;
	else if(x->data==k)
	return 1;
	else if(k<x->data)
	return do_search(x->left,k);
	else
	return do_search(x->right,k);
	
}
void insert(Tree T,int k)
{
	T->root=insert_node(T->root,k);
}
int search(Tree T,int k){
	return do_search(T->root,k);
}
void get_balance(Tree T,int k){
	int f;
	f=search(T,k);
	if(f==0)
	printf("FALSE\n");
	else{
		int d;
		Node x;
		x=find_node(T->root,k);
		d=balance_factor(x);
		printf("%d\n",d);
	}
}
Node minimum(Node x){
	if(x->left==NULL)
	return x;
	else
	return minimum(x->left);
}
Node delete_it(Node x,int k){
	if(x==NULL)
	return x;
	if(k<x->data)
	x->left=delete_it(x->left,k);
	else if(k>x->data)
	x->right=delete_it(x->right,k);
	else{
		if(x->left==NULL||x->right==NULL){
			Node z;
			if(x->left==NULL){
				z=x->right;
			}
			else
			z=x->left;
			if(z==NULL){
				z=x;
				x=NULL;
			}
			else{
				x->data=z->data;
				x->height=z->height;
				x->left=z->left;
				x->right=z->right;
			}
			free(z);
		}
		else{
			Node z;
			z=minimum(x->right);
			x->data=z->data;
			x->right=delete_it(x->right,z->data);
		}
	}
	if(x==NULL)
	return x;
	x->height=1+maximum(find_height(x->left),find_height(x->right));
	int d;
	d=balance_factor(x);
	if(d>1){
		int p;
		p=balance_factor(x->left);
		if(p>=0){
			return do_right_rotate(x);
		}
		if(p<0)
		{
			x->left=do_left_rotate(x->left);
			return do_right_rotate(x);
		}
	}
	else if(d<-1){
		int p;
		p=balance_factor(x->right);
		if(p<=0)
		return do_left_rotate(x);
		else if(p>0)
		{
			x->right=do_right_rotate(x->right);
			return do_left_rotate(x);
		}
	}
	return x;
}
void deletenode(Tree T,int k){
	int f;
	f=search(T,k);
	if(f==0)
	printf("FALSE\n");
	else{
		T->root=delete_it(T->root,k);
		printf("%d\n",k);
	}
}
void preorder(Node z){
		
		if(z!=NULL){
		printf("(");
		printf(" %d ",z->data);
		preorder(z->left);
		preorder(z->right);
		printf(") ");
	}
	else{
		printf("( ) ");
	}
}
void print_tree(Tree T){
	preorder(T->root);
}
int main(){
	Tree T;
	T=(Tree)malloc(sizeof(struct AVL));
	T->root=NULL;
	char c;
	while(1){
		scanf("%c",&c);
		if(c=='i'){
			int k;
			scanf("%d",&k);
			insert(T,k);
		}
		if(c=='s'){
			int k,f;
			scanf("%d",&k);
			f=search(T,k);
			if(f==0)
			printf("FALSE\n");
			else
			printf("TRUE\n");
		}
		if(c=='b'){
			int k,f;
			scanf("%d",&k);
			get_balance(T,k);
		}
		if(c=='d'){
			int k;
			scanf("%d",&k);
			deletenode(T,k);
		}
		if(c=='p'){
			print_tree(T);
			printf("\n");
		}
		if(c=='e'){
			return 0;
		}
	}
}
