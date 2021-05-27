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
		s1=(char*)malloc(10000*sizeof(char));
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
void find_element(node root,int level,int k){
	if(root==NULL)
	return;
	if(level==1){
		if(root->data==k||root->data==k){
			check=1;
	//	printf("%d ",root->data);
		}
	}
	if(level>1){
		find_element(root->left,level-1,k);
		find_element(root->right,level-1,k);
	}
}
void print_cousin(node root,int level,int k){
	if(level<2){
		return;
	}
	if(level==2){
		if(root->left!=NULL){
			if(root->left->data!=k){
				if(root->right!=NULL){
					if(root->right->data!=k){
						printf("%d ",root->left->data);
						check++;
					}
				}
				else{
						printf("%d ",root->left->data);
						check++;
				}
			}
		}
		if(root->right!=NULL){
		if(root->right->data!=k){
			if(root->left!=NULL){
					if(root->left->data!=k){
						printf("%d ",root->right->data);
						check++;
					}
				}
				else{
						printf("%d ",root->right->data);
						check++;
				}
			}
		}
	
	}
	else if(level>2){
	      print_cousin(root->left,level-1,k);
	      print_cousin(root->right,level-1,k);
	}
	
}
void  find_level(node root,int h,int k){
	//printf("h%d ",h);
	for(int i=1;i<=h;i++){
		find_element(root,i,k);
		if(check==1){
		print_cousin(root,i,k);	
	//	printf("L%d ",i);
		break;}
	}
}
void preorder(node z){
	if(z!=NULL){
		printf("%d ",z->data);
		preorder(z->left);
		preorder(z->right);
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
//	s1[j]='\0';
	//n=strlen(s1);
	
	//printf("%d ",j);
	T->root=to_tree(s1,1,j-2);
	int k,h,l,u=0;
	scanf("%d",&k);
//	preorder(T->root);
	h=find_height(T->root);
	find_level(T->root,h,k);
	if(check<=1){
		printf("-1");
	}
}
