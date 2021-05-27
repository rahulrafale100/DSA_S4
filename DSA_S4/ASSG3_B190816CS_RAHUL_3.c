#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	char colour;
	struct node *left;
	struct node *right;
};
struct RB_Tree{
	struct node *root;
};
typedef struct node *Node;
typedef struct RB_Tree *Tree;
Node create_node(int n){
	Node x,null_node;
	x=(Node)malloc(sizeof(struct node));
	null_node=(Node)malloc(sizeof(struct node));
	null_node->data=INT_MAX;
	null_node->colour='B';
	null_node->left=NULL;
	null_node->right=NULL;
	x->data=n;
	x->colour='R';
	x->left=null_node;
//	x->left->colour='B';
	x->right=null_node;
	x->right->colour='B';
	return x;
}
Node do_right_rotate(Node x){
	Node p;
	p=x->left;
	x->left=p->right;
	p->right=x;
	return p;
}
Node do_left_rotate(Node x){
	Node p;
	p=x->right;
	x->right=p->left;
	p->left=x;
	return p;
}
Node insert_rb_tree(Node r,Node x){
	if(r->data==INT_MAX)
		return x;
	else{
		if(r->data<x->data){
			r->right=insert_rb_tree(r->right,x);
		if(r->right->colour=='B')
			return r;
		else{
			if(r->right->left->colour=='R'||r->right->right->colour=='R'){
				if(r->left->colour=='R'){
					r->left->colour='B';
					r->colour='R';
					r->right->colour='B';
					return r;
				}
				else{
					if(r->right->left->colour=='R')
						r->right=do_right_rotate(r->right);
					Node y;
					y=do_left_rotate(r);
					y->colour='B';
					y->left->colour='R';
					return y;
				}
			}
			else
				return r;
		}}
		else if(r->data>x->data){
			r->left=insert_rb_tree(r->left,x);
			if(r->left->colour=='B')
				return r;
			else{
				if(r->left->left->colour=='R'||r->left->right->colour=='R'){
					if(r->right->colour=='R'){
						r->left->colour='B';
						r->colour='R';
						r->right->colour='B';
						return r;
					}
					else{
						if(r->left->right->colour=='R')
							r->left=do_left_rotate(r->left);
						Node y;
						y=do_right_rotate(r);
						y->colour='B';
						y->left->colour='R';
						return y;
					}
				}
				else
					return r;
			}
		}
	}
}
void print_preorder(Node z){
		if(z->data!=INT_MAX){
		printf("(");
		printf(" %d ",z->data);
		printf("%c ",z->colour);
		print_preorder(z->left);
		print_preorder(z->right);
		printf(") ");
	}
	else{
		printf("( ) ");
	}
}
void PRINT_TREE(Tree T){
	print_preorder(T->root);
	printf("\n");
}
Tree INSERT_RB_TREE(Tree T,int n){
	Node x;
	x=create_node(n);
	//	printf("1");
	T->root=insert_rb_tree(T->root,x);
	if(T->root->colour=='R')
	T->root->colour='B';
	return T;
}
int main(){
	Tree T;
	T=(Tree)malloc(sizeof(struct RB_Tree));
	Node null_node;
	null_node=(Node)malloc(sizeof(struct node));
	null_node->data=INT_MAX;
	null_node->colour='B';
	null_node->left=NULL;
	null_node->right=NULL;
	T->root=null_node;
	char c[10];
	int n;
	while(1){
		scanf("%s",c);
		if(c[0]=='t'){
		break;}
		n=atoi(c);
		//printf("%d",n);
		T=INSERT_RB_TREE(T,n);
		//printf("1");
		PRINT_TREE(T);
	}
}
