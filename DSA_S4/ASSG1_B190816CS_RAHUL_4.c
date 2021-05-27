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
typedef struct bst *bst;
bn create_node(int k){
	bn p;
	p=(bn)malloc(sizeof(struct bst_node));
	p->data=k;
	p->parent=NULL;
	p->left=NULL;
	p->right=NULL;
	return p;
}
void  insert(bst z,bn x){
 bn y=NULL;
 bn p=z->root;
 while(p!=NULL){
 	y=p;
 	if(x->data<p->data){
 		p=p->left;
	 }
	 else
	 p=p->right;}
	x->parent=y;
	if(y==NULL){
		z->root=x;
	}
	else if(x->data<y->data)
	 y->left=x;
	 else
	 y->right=x;
 
}
bn search (bn z,int k){
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
void  transplant(bst z, bn u,bn v){
	if(u->parent==NULL)
	 z->root=v;
	 else if( u==u->parent->left)
	  u->parent->left=v;
	  else
	  u->parent->right=v;
	   if(v!=NULL){
	   	v->parent=u->parent;
	   }
}
bn tree_minimum( bn z){
	while(z->left!=NULL){
		z=z->left;
	}
	return z;
}
void  delete_node(bst t,bn z){
	bn y;
	if(z->left==NULL)
	transplant(t,z,z->right);
	 else if(z->right==NULL)
	   transplant(t,z,z->left);
	   else {
	   	y=tree_minimum(z->right);
	   	if(y->parent!=z){
	   		transplant(t, y,y->right);
	   		y->right=z->right;
	   		y->right->parent=y;}
	   	transplant(t,z,y);
	   	y->left=z->left;
		   y->left->parent=y;	
	   }
	   printf("%d\n",z->data);
	   free(z);
}
void inorder(bn z){
	if(z!=NULL){
		inorder(z->left);
		printf("%d ",z->data);
		inorder(z->right);
	}
}
void preorder(bn z){
		if(z!=NULL){
		
		printf("%d ",z->data);
		preorder(z->left);
		preorder(z->right);
	}
}
void postorder(bn z){
	if(z!=NULL){
		postorder(z->left);
		postorder(z->right);
		printf("%d ",z->data);
	}
}
bn minimum(bn z){
  	while(z->left!=NULL){
  		z=z->left;
	}
	return z;
}
bn maximum(bn z){
	if(z!=NULL){
	while(z->right!=NULL){
		z=z->right;
	}}
	return z;
}
bn predecessor(bn z){
	if(z->left!=NULL){
		bn y=maximum(z->left);
		return y;
		}
		bn t=z->parent;
		while(t!=NULL&&z==t->left){
			z=t;
			t=z->parent;
		}
		return t;
}
bn successor(bn z){
	if(z->right!=NULL){
		return minimum(z->right);
	}
	bn y=z->parent;
	while(y!=NULL&&z==y->right){
		z=y;
		y=z->parent;
	}
	return y;
}
int get_level(bn z,int k,int level){
	if(z==NULL)
	return 0;
	if(z->data==k){
		return level;
	}
	int p=get_level(z->left,k,level+1);
	if(p!=0)
	return p;
	p=get_level(z->right,k,level+1);
	return p;
}
int level(bst T,int k){
	return get_level(T->root,k ,1);
}
int main(){
	bst z;
	z=(bst)malloc(sizeof(struct bst));
	z->root=NULL;
	char c;
	bn cn;
	while(1){
		scanf("%c",&c);
		if(c=='a'){
			int k;
			scanf("%d",&k);
		  cn=create_node(k);
		  insert(z,cn);
		  //preorder(z->root);	
		}
		if(c=='s'){
			int k;
			scanf("%d",&k);
			cn=search(z->root,k);
			if(cn==NULL){
				printf("%d\n",-1);
			}
			if(cn!=NULL){
				printf("%d\n",1);
			}
		}
		if(c=='m'){
			bn y=minimum(z->root);
			printf("%d\n",y->data);
		}
		if(c=='x'){
			bn y=maximum(z->root);
			printf("%d\n",y->data);
		}
		if(c=='d'){
			int k;
			scanf("%d",&k);
			cn=search(z->root,k);
			if(cn!=NULL)
			delete_node(z,cn);
			else
			printf("-1\n");
			}
		if(c=='r'){
			int k;
			scanf("%d",&k);
			cn=search(z->root,k);
			if(cn!=NULL){
			bn y=predecessor(cn);
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
			int k;
			scanf("%d",&k);
			cn=search(z->root,k);
			if(cn!=NULL){
			bn y=successor(cn);
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
		if(c=='l'){
			int k;
			scanf("%d",&k);
			bn c=search(z->root,k);
			if(c==NULL)
			printf("-1\n");
			else{
				int l;
				l=level(z,k);
				printf("%d\n",l);
			}
		}
		if(c=='i'){
			inorder(z->root);
			printf("\n");
		}
		if(c=='p'){
			preorder(z->root);
			printf("\n");
		}
		if(c=='t'){
			postorder(z->root);
			printf("\n");
		}
		if(c=='e')
		return 0;
		}
	}
