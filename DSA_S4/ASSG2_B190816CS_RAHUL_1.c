#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct hash_tbl{
	int *t;
	int size;
	int c1;
	int c2;
	int prime;
};
typedef struct hash_tbl Table;
int * hash_table(int n){
	int *a;
	a=(int*)malloc(n*sizeof(int));
	for(int i=0;i<n;i++){
		a[i]=-1;
	}
	return a;
}
int resolution(int k,Table T){
	int i=0,u,x,y,n;
	n=T.size;x=T.c1;y=T.c2;
	u=(k+(i*x)+(y*i*i))%n;
	while(i!=n&&T.t[u]!=-1){
		i++;
		u=(k+(i*x)+(y*i*i))%n;
	}
	if(i!=n){
		return u;
	}
	else
	return -1;
	
}
int re_search(Table T,int k,int v){
	int i=0,u,x,y,n;
	n=T.size;x=T.c1;y=T.c2;
	u=(k+(i*x)+(y*i*i))%n;
	while(i!=n&&T.t[u]!=v){
		i++;
		u=(k+(i*x)+(y*i*i))%n;
	}
	if(i!=n)
	return u;
	else
	return -1;
}
int search(Table T,int k){
	int u=k%T.size;
	if(T.t[u]==k)
	return u;
	else{
		return re_search( T,u,k);
	}
}
void insert(Table T,int k){
	int u=k%T.size;
	if(T.t[u]!=-1){
		u=resolution(u,T);
	}
	if(u!=-1){
		T.t[u]=k;
	}
}
void insert1(Table T,int k){
	int i=0,u,n=T.size,p=T.prime;
	u=(k%n+(i*(p-(k%p))))%n;
	while(i!=n&&T.t[u]!=-1){
		i++;
		u=(k%n+(i*(p-(k%p))))%n;
	}
	if(i!=n){
		T.t[u]=k;
	}
}
int search1(Table T,int k){
	int i=0,u,n=T.size,p=T.prime;
	u=(k%n+(i*(p-(k%p))))%n;
	while(i!=n&&T.t[u]!=k){
		i++;
		u=(k%n+(i*(p-(k%p))))%n;
	}
	if(i!=n)
	return u;
	else
	return -1;
}
void delete2(Table T,int k){
	int f;
	f=search1(T,k);
	T.t[f]=-1;
}
void delete1(Table T,int k){
	int z;
	z=search(T,k);
	T.t[z]=-1;
}
int main(){
	char c;
	scanf("%c",&c);
	int n;
	scanf("%d",&n);
	Table T;
	T.t=hash_table(n);
	T.size=n;
//	for(int i=0;i<n;i++){
//		printf("%d",T.t[i]);
//	}
	if(c=='a'){
		int a;int b;
		scanf("%d",&a);
		scanf("%d",&b);
		T.c1=a;
		T.c2=b;
		while(1){
		char p;
		scanf("%c",&p);
		if(p=='i'){
			int k,u;
			scanf("%d",&k);
			insert(T,k);
		}
		if(p=='s'){
			int k;
			scanf("%d",&k);
			int z;
			z=search(T,k);
			if(z!=-1)
			printf("1\n");
			else
			printf("-1\n");
		}
		if(p=='d'){
			int k;
			scanf("%d",&k);
			int z;
			delete1(T,k);
			
		}
		if(p=='p'){
			for(int i=0;i<n;i++){
				printf("%d ",i);
				if(T.t[i]==-1){
					printf("()\n");
				}
				else{
					printf("(%d)\n",T.t[i]);
				}
			}
		}
		if(p=='t'){
			return 0;
		}
	}
	}
	if(c=='b'){
		int x=0,z,flag;
		z=n;
		while(x==0){
			z--;
			flag=0;
	    for(int i=2;i*i<=z;i++){
	    	if(z%i==0){
	    		flag=1;
	    		break;
			}
		}
		if(flag==0){
			x=1;
			T.prime=z;
		}
}
///printf("%d",T.prime);
		while(1){
			char p;
			scanf("%c",&p);
			if(p=='i'){
				int k;
				scanf("%d",&k);
				insert1(T,k);
			}
			if(p=='s'){
			  int k,f;
			  scanf("%d",&k);
			  f=search1(T,k);
			  if(f!=-1)
			  printf("1\n");
			  else
			  printf("-1\n");
			}
			if(p=='d'){
			  int k,f;
			  scanf("%d",&k);
			  delete2(T,k);
			}
			if(p=='p'){
					for(int i=0;i<n;i++){
				printf("%d ",i);
				if(T.t[i]==-1){
					printf("()\n");
				}
				else{
					printf("(%d)\n",T.t[i]);
				}
			}
			}
			if(p=='t')
			{
				return 0;
			}
		}
	}
}
