#include<stdio.h>
#include<stdlib.h>
struct bst_node{
	int data;
	struct bst_node *left;
	struct bst_node *right;
	struct bst_node *parent;
};
struct bst{
	struct bst_node *root;
};
typedef struct bst_node *bn;
typedef struct bst *tree;
bn create_node(int k){
	bn z;
//	printf("%d ",k);
	z=(bn)malloc(sizeof(struct bst_node));
	z->data=k;
	z->left=NULL;
	z->right=NULL;
	return z;
}
bn make_bst(int ar[],int x,int y){
	if(x>y)
	return NULL;
	int m=(y+x)/2;
	bn cn=create_node(ar[m]);
	//printf("%d ",cn->data);
	cn->left=make_bst(ar,x,m-1);
	cn->right=make_bst(ar,m+1,y);
	return cn;
}
void bracket_rep(bn z){
		
		if(z!=NULL){
			printf("(");
		printf(" %d ",z->data);
		bracket_rep(z->left);
		bracket_rep(z->right);
		printf(") ");
	}
	else{
		printf("( ) ");
	}
}

int get_height(bn z){
	if(z==NULL)
	return 0;
	int lh=get_height(z->left);
	int rh=get_height(z->right);
	if(lh>rh)
	return (lh+1);
	else
	return (rh+1);
}
void level_sum(bn z,int level, int sum[]){
	if(z==NULL)
	return ;
	sum[level]+=z->data;
	level_sum(z->left,level+1,sum);
	level_sum(z->right,level+1,sum);
}
int main(){
	int n;
	scanf("%d",&n);
	int ar[n];
	for(int i=0;i<n;i++){
		scanf("%d",&ar[i]);
	}
	tree T;
	T=(tree)malloc(sizeof(struct bst));
	T->root=NULL;
	T->root=make_bst(ar,0,n-1);
	bracket_rep(T->root);
	printf("\n");
	int height ;
	height=get_height(T->root);
//	print_lsum(T->root,height);
	int sum[height];
	for(int i=0;i<height;i++){
		sum[i]=0;
	}
	level_sum(T->root,0,sum);
	for(int i=0;i<height;i++){
		printf("%d ",sum[i]);
	}
	return 0;
}
