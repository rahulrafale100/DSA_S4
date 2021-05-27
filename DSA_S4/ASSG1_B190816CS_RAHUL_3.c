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
typedef struct tree_node *node;
typedef struct binary_tree *tree;
node create_node(int k){
	node p;
	p=(node)malloc(sizeof(struct tree_node));
	p->data=k;
	p->left=NULL;
	p->right=NULL;
	p->parent=NULL;
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
		s1=(char*)malloc(100*sizeof(char));
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
int find_height(node root){
	if(root==NULL)
	return 0;
	else{
		int lheight=find_height(root->left);
		int rheight=find_height(root->right);
		if(lheight>rheight){
			return (lheight+1);
		}
		else
		return (rheight+1);
	}
}
int is_bst_full(node root,int min,int max,int *sum){
	if(root==NULL)
	return 1;
	*sum+=root->data;
	if(root->data<min||root->data>max)
	return 0;
	return (is_bst_full(root->left,min,root->data,sum)&&is_bst_full(root->right,root->data,max,sum));
}
int is_bst_left(node root,int min,int max,int *sum){
	if(root==NULL)
	return 1;
	*sum+=root->data;
	if(root->data<min||root->data>max)
	return 0;
	return (is_bst_left(root->left,min,root->data,sum));
}
int is_bst_right(node root,int min,int max,int *sum){
	if(root==NULL)
	return 1;
	*sum+=root->data;
	if(root->data<min||root->data>max)
	return 0;
	return (is_bst_right(root->right,root->data,max,sum));
}
void level_order(node root,int level,int *c,int k){
	if(root==NULL){
		return;
	}
	if(level==1){
		int sum=0;
		if(is_bst_full(root,-1000001,1000001,&sum)){
		if(sum==k)
		*c=*c+1;}
		if(root->left!=NULL){
			sum=0;
		if(is_bst_left(root,-1000001,1000001,&sum)){
		if(sum==k)
		*c=*c+1;}}
		if(root->right!=NULL){
		sum=0;
		if(is_bst_right(root,-1000001,1000001,&sum)){
		if(sum==k)
		*c=*c+1;
		}}
	}
	else if(level>1){
		level_order(root->left,level-1,c,k);
		level_order(root->right,level-1,c,k);
	}
}
int main(){
		tree T;
	T=(tree)malloc(sizeof(struct binary_tree));
	T->root=NULL;
	char s[1000000];
	//scanf("%s",s);
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
	int k,h,l,u=0;
	scanf("%d",&k);
	h=find_height(T->root);
	int ans=0,cnt=0;
	for(int i=1;i<=h;i++){
		ans=0;
		level_order(T->root,i,&cnt,k);
	}
	if(cnt==0)
	printf("-1");
	else
	printf("%d",cnt);
}
