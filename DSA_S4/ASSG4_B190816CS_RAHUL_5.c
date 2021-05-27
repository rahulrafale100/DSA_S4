#include<stdio.h>
#include<stdlib.h>
struct edge{
	int src;
	int dst;
	int wght;
};
struct graph{
	int v;
	int e;
	struct edge *Edge; 
};
typedef struct edge *edg;
typedef struct graph *Graph;
Graph create_graph(int n,int m){
	Graph G;
	G=(Graph)malloc(sizeof(struct graph));
	G->v=n;
	G->e=m;
	G->Edge=(edg)malloc(m*sizeof(struct edge));
	return G;
}
int find_neg_cycle(Graph G,int src){
	int distance[G->v];
	for(int i=0;i<G->v;i++){
		distance[i]=INT_MAX;
	}
	distance[src]=0;
	for(int i=0;i<G->v;i++){
		for(int j=0;j<G->e;j++){
			int u,v,w;
			u=G->Edge[j].src;
			v=G->Edge[j].dst;
			w=G->Edge[j].wght;
			if(distance[u]!=INT_MAX&&(distance[v]>(distance[u]+w)))
			distance[v]=distance[u]+w;
		}}
		for(int j=0;j<G->e;j++){
				int u,v,w;
			u=G->Edge[j].src;
			v=G->Edge[j].dst;
			w=G->Edge[j].wght;
			if(distance[u]!=INT_MAX&&(distance[v]>(distance[u]+w)))
				return 1;
		}
		return -1;
	}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	Graph G;
	G=create_graph(n,m);
	for(int i=0;i<m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		G->Edge[i].src=x;
		G->Edge[i].dst=y;
		G->Edge[i].wght=z;
	}
	int ans;
	ans=find_neg_cycle(G,0);
	printf("%d",ans);
//	for(int i=0;i<m;i++){
//		printf("%d %d %d\n",G->Edge[i].src,G->Edge[i].dst,G->Edge[i].wght);
//	}
}
