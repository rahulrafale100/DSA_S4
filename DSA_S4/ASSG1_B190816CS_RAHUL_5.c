#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct tree_node{
	int data;
	struct tree_node *left;
	struct tree_node *right;
	struct tree_node *parent;
};
struct binary_tree{
	struct tree_node *root;
};
int  check =0;
typedef struct tree_node *node;
typedef struct binary_tree *tree;
node create_node(int k){
	node p;
	p=(node)malloc(sizeof(struct tree_node));
	p->data=k;
	p->left=NULL;
	p->right=NULL;
	p->parent=NULL;
	return p;
}
int find(char s[],int x,int y){
	if(x>y)
	return -1;
	int t=0;
	for(int i=x;i<=y;i++){
		if(s[i]=='('){
			t++;
		}
		else if(s[i]==')'){
			if(t>0){
				t--;
			}
			if(t==0){
				return i;
			}
		}
	}
	return -1;
}
node to_tree(char s[],int x,int y){
	node p;
	if(x>y)
	return NULL;
	if(s[x]=='('&&s[x+1]==')')
	x=x+2;
	if(s[x]!='('){
		char *s1;
		s1=(char*)malloc(100000*sizeof(char));
		int i=0;
		while(s[x]!='('&&s[x]!=')'){
			s1[i]=s[x];
			x++;
			i++;
		}
		x--;
		if(i!=0){
		int k=atoi(s1);	
	//	printf("%d ",k);
		p=create_node(k);
		}
		
	}
	int flag=-1;
	if(x+1<=y&&s[x+1]=='('){
		flag=find(s,x+1,y);
	}
	if(flag!=-1){
		p->left=to_tree(s,x+2,flag-1);
		p->right=to_tree(s,flag+2,y-1);
	}
	return p;	
}

int main(){
	tree T;
	T=(tree)malloc(sizeof(struct binary_tree));
	T->root=NULL;
	char s[1000000];
//	scanf("%s",s);
     gets(s);
	int n=strlen(s);
	char s1[100000];
	int i=0,j=0;
	while(i<n){
		if(s[i]!=' '){
			s1[j]=s[i];
			j++;
		}
		i++;
	}
	T->root=to_tree(s1,1,j-2);
	int k;
	scanf("%d",&k);
	node z=T->root;
	int arr[100000],c=0;
	auto void inorder(node);
	inorder(T->root);
	void inorder(node z){
		if(z!=NULL){
			int d;
			inorder(z->left);
			d=z->data;
			arr[c]=d;
			c++;
			inorder(z->right);
		}
	}
	printf("%d",arr[k-1]);
}
