#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	int degree;
	char c;
	struct node *left;
	struct node *right;
	struct node *parent;
	struct node *child;
};
struct heap{
	struct node *min;
	int n;
};
typedef struct node *Node;
typedef struct heap *Heap;
Node Node_list[1000001][2];
Heap make_heap(){
	Heap H;
	H=(Heap)malloc(sizeof(struct heap));
	H->min=NULL;
	H->n=0;
}
Node create_node(int n){
	Node z;
	z=(Node)malloc(sizeof(struct node));
	z->c='W';
	z->data=n;
	z->degree=0;
	z->left=z;
	z->parent=NULL;
	z->child=NULL;
	z->right=z;
	return z;
}
void insert(Heap H,Node x){
	if(x->data>=0)
	Node_list[x->data][0]=x;
	else
	Node_list[abs(x->data)][1]=x;
	if(H->min==NULL)
	H->min=x;
	else{
		H->min->left->right =x;
    x->right = H->min;
    x->left = H->min->left;
    H->min->left =x;
    if (x->data < H->min->data) {
      H->min = x;
    }
	}
	H->n++;
}
void fib_heap_link(Heap H, Node y, Node x) {
  y->right->left = y->left;
  y->left->right= y->right;

  if (x->right == x)
    H->min = x;

  y->left= y;
  y->right = y;
  y->parent = x;

  if (x->child == NULL) {
    x->child = y;
  }
  y->right= x->child;
  y->left = x->child->left;
  x->child->left->right = y;
  x->child->left= y;
  if ((y->data) < (x->child->data))
    x->child = y;

  (x->degree)++;
}
int cal_degree(int n) {
  int count = 0;
  while (n > 0) {
    n = n / 2;
    count++;
  }
  return count;
}
void consolidate(Heap H) {
  int degree, i, d;
  degree = cal_degree(H->n);
  Node A[degree];
  Node x;
  Node y;
  Node z;
  for (i = 0; i <= degree; i++) {
    A[i] = NULL;
  }
  x = H->min;
  do {
    d = x->degree;
    while (A[d] != NULL) {
      y = A[d];
      if (x->data > y->data) {
         Node exchange_help;
        exchange_help = x;
        x = y;
        y = exchange_help;
      }
      if (y == H->min)
        H->min = x;
      fib_heap_link(H, y, x);
      if (y->right == x)
        H->min = x;
      A[d] = NULL;
      d++;
    }
    A[d] = x;
    x = x->right;
  } while (x != H->min);


}
void extract_min(Heap H){
	Node temp,ptr;
	temp=H->min;
	ptr=H->min;
	Node x=NULL;
    if (temp->child != NULL) {
      x = temp->child;
      do {
        ptr = x->right;
        (H->min->left)->right = x;
        x->right = H->min;
        x->left = H->min->left;
        H->min->left = x;
        if (x->data < H->min->data)
          H->min = x;
        x->parent = NULL;
        x = ptr;
      } while (ptr != temp->child);
    }
	    temp->left->right = temp->right;
    temp->right->left = temp->left;
    H->min = temp->right;
//printf("1");
    if (temp == temp->right && temp->child== NULL)
      H->min = NULL;
    else {
      H->min = temp->right;
     // printf("%d ",H->min);
      consolidate(H);
    }
    H->n--;
  }
void cut(Heap H, Node z, Node pn) {

  if (z == z->right)
    pn->child = NULL;

  z->left->right = z->right;
  z->right->left = z->left;
  if (z == pn->child)
    pn->child = z->right;
  (pn->degree)--;

  z->left = z;
 z->right = z;
  H->min->left->right = z;
  z->right = H->min;
  z->left = H->min->left;
  H->min->left = z;

  z->parent = NULL;
  z->c='W';
}
void cascading_cut(Heap H, Node pn) {
  Node a;
  a = pn->parent;
  if (a != NULL) {
    if (pn->c == 'W') {
      pn->c = 'B';
    } else {
      cut(H, pn, a);
      cascading_cut(H, a);
    }
  }
}
  void decrease_key(Heap H, Node z, int k) {
  Node pn;
      z->data = k;
   
      pn = z->parent;
      if ((pn != NULL) && (z->data < pn->data)) {
        cut(H, z, pn);
        cascading_cut(H, pn);
      }
      if (z->data < H->min->data) {
        H->min = z;
      }
}
void delete_node(Heap H,int k){
	Node z;
	if(k>=0)
	z=Node_list[k][0];
	else
	z=Node_list[abs(k)][1];
	decrease_key(H,z,-1000000);
	extract_min(H);
}
int main(){
	Heap H;
	H=make_heap();
	char c;
	while(1){
		scanf("%c",&c);
		if(c=='i'){
			int n;
			scanf("%d",&n);
			Node x=create_node(n);
			insert(H,x);
		}
		if(c=='m'){
			int ans;
			ans=H->min->data;
			printf("%d\n",ans);
		}
		if(c=='x'){
			
			printf("%d\n",H->min->data);
			if(H->min->data>=0)
			Node_list[H->min->data][0]=NULL;
			else
				Node_list[abs(H->min->data)][1]=NULL;
			extract_min(H);
		}
		if(c=='r'){
			int x,y;
			scanf("%d%d",&x,&y);
			printf("%d\n",y);
			Node z;
			if(x>=0)
				z=Node_list[x][0];
				else
				z=Node_list[abs(x)][1];
			decrease_key(H,z,y);
			Node_list[abs(x)][0]=NULL;
			Node_list[abs(x)][1]=NULL;
		if(y>=0)
      	Node_list[y][0]=z;
      	else
      	Node_list[abs(y)][1]=z;
		}
		if(c=='d'){
			int k;
			scanf("%d",&k);
			delete_node(H,k);
			Node_list[abs(k)][0]=NULL;
			Node_list[abs(k)][1]=NULL;
		}
		if(c=='p'){
			Node z=H->min;
			printf("%d ",z->data);
			z=z->right;
			while(z!=H->min){
				printf("%d ",z->data);
				z=z->right;
			}
			printf("\n");
		}
		if(c=='e')
		return 0;
	}
}
