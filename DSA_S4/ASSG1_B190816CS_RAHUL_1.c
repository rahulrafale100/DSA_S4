#include<stdio.h>
#include<stdlib.h>
struct tree_node{
	int data;
	struct tree_node *left;
	struct tree_node *right;
	struct tree_node *parent;
};
struct binary_tree{
	struct tree_node *root;
	int level,n;
};
typedef struct tree_node *node;
typedef struct binary_tree *tree;
int find_power(int x,int n){
    int result =1;
    while(n){
        if(n%2){
            result=result*x;
        }
        n/=2;
        x=x*x;
    }
    return result;
}
void level_order(node root,int level,node p){
	if(level==2){
	if(root->left==NULL){
		root->left=p;
		p->parent=root;
		return ;
	}
	else if(root->right==NULL){
		root->right=p;
		p->parent=root;
		return;
	}}
	else if(level>2){
		level_order(root->left,level-1,p);
		if(p->parent==NULL){
			level_order(root->right,level-1,p);
		}
	}
}
void insert(tree T,int k){
		int p=find_power(2,T->level);
		node tn;
		tn=(node)malloc(sizeof(struct tree_node));
		tn->data=k;
		tn->left=NULL;
		tn->parent=NULL;
		tn->right=NULL;
		if(T->root==NULL){
			T->root=tn;
		
			return;
		}
		else{
		if(T->n>=p){
			T->level++;
		}
		level_order(T->root,T->level,tn);}
		
}
void preorder(node z){
		
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
void print(tree T){
	preorder(T->root);
}
int main(){
	tree T;
	T=(tree)malloc(sizeof(struct binary_tree));
	T->level=1;
	T->root=NULL;
	T->n=0;
	 int k;
	 char c;
	 while(1){
	 	scanf("%c",&c);
	 	if(c=='i'){
	 		scanf("%d",&k);
	 		T->n++;
	 		insert(T,k);
	 		}
		 if(c=='p'){
		 	print(T);
		 	printf("\n");
		 }
		 if(c=='e'){
		 	return 0;
		 }
	 }
}
