#include<stdio.h>
#include<stdlib.h>
struct disjoint_set{
	int parent[100001];
	int rank[100001];
	int operation;
};
typedef struct disjoint_set DST;
DST* start_it(){
	DST *z;
	z=(DST*)malloc(sizeof(struct disjoint_set));
	for(int i=0;i<100001;i++){
		z->parent[i]=-1;
		z->rank[i]=0;
	}
	z->operation=0;
}
void make_set(DST *S,int k){
	S->parent[k]=k;
	S->rank[k]=0;
}
int find_set_1(DST *S,int k){
	S->operation++;
	if(S->parent[k]==-1)
	return -1;
	else{
		while(k!=S->parent[k]){
			S->operation++;
			k=S->parent[k];
		}
		return k;
	}
}
int find_set_2(DST *S,int k){
	S->operation++;
	if(S->parent[k]==-1)
	return -1;
	else{
		while(k!=S->parent[k]){
			S->operation++;
			k=S->parent[k];
		}
		return k;
	}
}
int find_set_3(DST *S,int k){
	S->operation++;
	if(S->parent[k]==-1)
	return -1;
	if(k!=S->parent[k])
	S->parent[k]=find_set_3(S,S->parent[k]);
	return S->parent[k];
}
int find_set_4(DST *S,int k){
	S->operation++;
	if(S->parent[k]==-1)
	return -1;
	if(k!=S->parent[k])
	S->parent[k]=find_set_4(S,S->parent[k]);
	return S->parent[k];
}
int union_set_1(DST *S,int x,int y){
	int p,q;
	p=find_set_1(S,x);
	q=find_set_2(S,y);
	if(p==-1||q==-1)
	return -1;
	else if(p!=-1&&q!=-1&&p==q){
		return p;
	}
	else{
		S->parent[q]=p;
		return p;
	}
}
int union_set_2(DST *S,int x,int y){
	int p,q;
	p=find_set_2(S,x);
	q=find_set_2(S,y);
	if(p==-1||q==-1)
	return -1;
	else if(p!=-1&&q!=-1&&p==q){
		return p;
	}
	else{
		if(S->rank[p]<S->rank[q]){
			S->parent[p]=q;
			return q;
		}
		else{
			S->parent[q]=p;
			if(S->rank[p]==S->rank[q])
				S->rank[p]++;
			return p;
		}
	}
}
int union_set_3(DST *S,int x,int y){
//	printf("-sd");
	int p,q;
	p=find_set_3(S,x);
	q=find_set_3(S,y);
	if(p==-1||q==-1)
	return -1;
	else if(p!=-1&&q!=-1&&p==q){
		return p;
	}
	else if(p!=-1&&q!=-1&&p!=q){
		S->parent[q]=p;
		return p;
	}
}
int union_set_4(DST *S,int x,int y){
	int p,q;
	p=find_set_4(S,x);
	q=find_set_4(S,y);
	if(p==-1||q==-1)
		return -1;
		else if(p!=-1&&q!=-1&&p==q)
		return p;
		else{
				if(S->rank[p]<S->rank[q]){
			S->parent[p]=q;
			return q;
		}
		else{
			S->parent[q]=p;
			if(S->rank[p]==S->rank[q])
				S->rank[p]++;
			return p;
		}
		}
}
int main(){
		DST *a,*b,*c,*d;
		a=start_it();
		b=start_it();
		c=start_it();
		d=start_it();
		char x;
		int k,n;
		while(1){
			scanf("%c",&x);
			if(x=='m'){
				scanf("%d",&k);
				if(a->parent[k]==-1&&b->parent[k]==-1&&c->parent[k]==-1&&d->parent[k]==-1){
					printf("%d\n",k);
					make_set(a,k);
					make_set(b,k);
					make_set(c,k);
					make_set(d,k);
				}
				else{
					printf("-1\n");
				}
			}
			if(x=='f'){
				scanf("%d",&k);
				int z;
				z=find_set_1(a,k);
				printf("%d ",z);
				z=find_set_2(b,k);
				printf("%d ",z);
				z=find_set_3(c,k);
				printf("%d ",z);
				z=find_set_4(d,k);
				printf("%d\n",z);
			}
			if(x=='u'){
				scanf("%d%d",&k,&n);
				int z;
				z=union_set_1(a,k,n);
				printf("%d ",z);
				z=union_set_2(b,k,n);
				printf("%d ",z);
				z=union_set_3(c,k,n);
				printf("%d ",z);
				z=union_set_4(d,k,n);
				printf("%d\n",z);
			}
			if(x=='s'){
				printf("%d %d %d %d\n",a->operation,b->operation,c->operation,d->operation);
				return 0;
			}
		}
}
