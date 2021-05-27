#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node *left;
	struct node *right;
};
struct BST{
	struct node *root;
};
typedef struct node *Node;
typedef struct BST  *Tree;
Node create_node(int k){
	Node x;
	x=(Node)malloc(sizeof(struct node));
	x->data=k;
	x->left=NULL;
	x->right=NULL;
	return x;
}
void  insert(Tree z,Node x){
 Node y=NULL;
 Node p=z->root;
 while(p!=NULL){
 	y=p;
 	if(x->data<p->data){
 		p=p->left;
	 }
	 else
	 p=p->right;}
	if(y==NULL){
		z->root=x;
	}
	else if(x->data<y->data)
	 y->left=x;
	 else
	 y->right=x;
 
}
Node find_lca(Tree T ,int x,int y){
	Node p=T->root;
	while(x<p->data&&y<p->data||x>p->data&&y>p->data){
		if(x<p->data&&y<p->data){
			p=p->left;
		}
		else if(x>p->data&&y>p->data){
			p=p->right;
		}
	}
	return p;
}
int max(int a,int b){
	if(a>b)
	return a;
	else
	return b;
}
int maxel(Node x,int k){
	int p=INT_MIN;
	while(x->data!=k){
		if(x->data<k){
			p=max(p,x->data);
			x=x->right;
		}
		else{
			p=max(p,x->data);
			x=x->left;
		}
	}
	return p;
}
int main(){
	Tree T;
	T=(Tree)malloc(sizeof(struct BST));
	T->root=NULL;
	int a[100000];
	int n=0,t=4;
	char c;
	while(1){
		scanf("%d",&a[n]);
		n++;
	scanf("%c",&c);
	if(c=='\n')
	break;
	}
	int x,y;
	scanf("%d%d",&x,&y);
	for(int i=0;i<n;i++){
		Node p,q;
		p=create_node(a[i]);
		insert(T,p);
	}
	Node LCA;
	LCA=find_lca(T,x,y);
	
	int ans;
	ans=max(maxel(LCA,x),maxel(LCA,y));
	printf("%d",ans);
	return 0;
}
