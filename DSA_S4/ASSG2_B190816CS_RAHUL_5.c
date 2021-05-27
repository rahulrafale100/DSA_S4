#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	int data;
	struct node *left;
	struct node *right;
};
struct BST{
	struct node *root;
};
typedef struct node *Node;
typedef struct BST *Tree;
Node create_node(int k){
	Node p;
	p=(Node)malloc(sizeof(struct node));
	p->data=k;
	p->left=NULL;
	p->right=NULL;
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
Node to_tree(char s[],int x,int y){
	Node p;
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
Node minimum(Node z){
  	while(z->left!=NULL){
  		z=z->left;
	}
	return z;
}
Node search (Node z,int k){
	if(z==NULL||z->data==k){
		return z;
	}
	else if(k<z->data){
		return search(z->left,k);
	}
	else{
		return search(z->right,k);
	}	
}
Node maximum(Node z){
	if(z!=NULL){
	while(z->right!=NULL){
		z=z->right;
	}}
	return z;
}
Node predecessor(Tree T,Node z){
	if(z->left!=NULL){
		Node y=maximum(z->left);
		return y;
		}
		else{
				Node x,y;
		y=T->root;
		x=NULL;
		while(y!=NULL){
			if(z->data<y->data){
				y=y->left;
			}
			else if(z->data>y->data){
				x=y;
				y=y->right;
			}
			else
			break;
		}
		return x;	
		}
}
Node successor(Tree T,Node z){
	if(z->right!=NULL){
		return minimum(z->right);
	}
	else{
		Node x,y;
		y=T->root;
		x=NULL;
		while(y!=NULL){
			if(z->data<y->data){
				x=y;
				y=y->left;
			}
			else if(z->data>y->data){
				y=y->right;
			}
			else
			break;
		}
		return x;
	}
}
void inorder(Node z){
	if(z!=NULL){
		inorder(z->left);
		printf("%d ",z->data);
		inorder(z->right);
	}
}
int main(){
	Tree T;
	T=(Tree)malloc(sizeof(struct BST));
	T->root=NULL;
	char s[1000000];
	gets (s);
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
	char c;
	int k;
	Node cn;
	int arr[100000],p=0;
	auto void inorderk(Node);
	inorderk(T->root);
	void inorderk(Node z){
		if(z!=NULL){
			int d;
			inorderk(z->left);
			d=z->data;
			arr[p]=d;
			p++;
			inorderk(z->right);
		}
	}
	while(1){
		scanf("%c",&c);
		if(c=='r'){
			scanf("%d",&k);
			cn=search(T->root,k);
			if(cn!=NULL){
			Node y=predecessor(T,cn);
			if(y==NULL){
				printf("-1\n");
			}
			else{
				printf("%d\n",y->data);
			}
			}
			else{
				printf("-1\n");
			}
		}
		if(c=='u'){
				scanf("%d",&k);
			cn=search(T->root,k);
			if(cn!=NULL){
			Node y=successor(T,cn);
			if(y==NULL){
				printf("-1\n");
			}
			else{
				printf("%d\n",y->data);
			}}
			else{
				printf("-1\n");
			}
		}
		if(c=='i'){
			inorder(T->root);
			printf("\n");
		}
		if(c=='s'){
			scanf("%d",&k);
			if(k<=p)
			printf("%d\n",arr[k-1]);
			else{
				printf("-1\n");
			}
		}
		if(c=='l'){
			scanf("%d",&k);
			if(k<=p){
				int l=p-k;
				printf("%d\n",arr[l]);
			}
			else{
				printf("-1\n");
			}
		}
		if(c=='e'){
			return 0;
		}
		}
	}
