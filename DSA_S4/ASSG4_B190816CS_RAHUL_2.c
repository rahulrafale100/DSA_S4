#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
//Edege formation
struct edge {
    int u, v, w;
    struct edge *next;
};
//Arrays of endges
struct EdgeArray {
    int V, E;
    struct edge *head;
};
typedef struct edge *Edge;
typedef struct EdgeArray *Edge_Array;

//Adjacency list Node
struct AdjacencyListNode {
    int vertex_key;
    int weight;
    struct AdjacencyListNode *next;
};

//Adjacency List
struct AdjacencyList {
    struct AdjacencyListNode *head;
};
typedef struct AdjacencyList *Adj_list;
typedef struct AdjacencyListNode *Adj_list_node;

//Graph
struct graph {
    int V;
    struct AdjacencyList *array;
};
typedef struct graph *Graph;

//Disjoint Set Node 
struct DisjointSetNode{
    int rank;
	int  val;
    struct DisjointSetNode *parent;
};
//Disjoint Set
struct DisjointSet{
    int V;
    struct DisjointSetNode **set;
};
typedef struct DisjointSet* DST;    
typedef struct DisjointSetNode* DST_NODE;

//Struct to hold  a node in MST
struct MST_Node {
    int weight, parent;
    bool present;
};

//Struct to hold an MstArray
struct MST_Array {
    int V;
    struct MST_Node  *array;
};
typedef struct MST_Array* MST_ARRAY;
typedef struct MST_Node* MST_NODE;
//Creation of Adjacency Node
Adj_list_node NewAdjListNode(int v){
    Adj_list_node z = (Adj_list_node)malloc(sizeof(struct AdjacencyListNode));
    z->next = NULL;
    z->vertex_key = v;
    z->weight = 0;
    return z;
}

//Add in list
Adj_list_node append(Adj_list_node head, Adj_list_node z){
    if(head == NULL)
        return z;
    Adj_list_node tail = head;
    while(tail->next != NULL)
        tail = tail->next;
    tail->next = z;
    return head;
}
//Graph Initialize
Graph CreateGraph(){
    int V;
    scanf("%d", &V);

    Graph G = (Graph)malloc(sizeof(struct graph));
    G->V = V;
    G->array = (Adj_list)malloc(V*sizeof(struct AdjacencyList));

    for(int i=0; i<V; i++)
        G->array[i].head = NULL;

    for(int i=0; i<V; i++){
    	int k=0;
        char temp = ' ';
        while(temp != '\n'){
            int vertex;
            scanf(" %d%c", &vertex, &temp);
            if(k==0){
            	k++;
            	continue;
			}
            Adj_list_node x ;
            x= NewAdjListNode(vertex);
            G->array[i].head = append(G->array[i].head, x);
        }
    }

    int weight;
    for(int i=0; i<V; i++){
    	int k=0;
        Adj_list_node list_1 = G->array[i].head;
        int weight;
        while(list_1 != NULL){
            scanf(" %d", &weight);
            if(k==0){
            	k++;
            	continue;
			}
            list_1->weight = weight;
            list_1 = list_1->next;
        }
    }

    return G;
}
void append_Edge(Edge_Array E, int src, int dest, int weight){
    Edge ne = (Edge)malloc(sizeof(struct edge));
    ne->u = src;
    ne->v = dest;
    ne->w = weight;
    ne->next = NULL;

    if(E->head == NULL)
        E->head = ne;
    else {
        Edge *temp = &(E->head);
        while(*temp != NULL && (*temp)->w < ne->w)
            temp = &((*temp)->next);
        ne->next = *temp;
        *temp = ne;
    }
    E->E++;
}

Edge_Array MakeArrayEdges(Graph G){
    Edge_Array E = (Edge_Array)malloc(sizeof(struct EdgeArray));
    E->V = G->V;
    E->E = 0;
    E->head = NULL;

    for(int i=0; i<G->V; i++){
        Adj_list_node list_1 = G->array[i].head;
        while(list_1!=NULL){
            if(list_1->vertex_key > i)
                append_Edge(E, i, list_1->vertex_key, list_1->weight);
            list_1 = list_1->next;
        }
    }
    return E;
}

DST_NODE make_Set(int x){
    DST_NODE z;
	z= (DST_NODE)malloc(sizeof(struct DisjointSetNode));
    z->val = x;
    z->parent = z;
    z->rank = 0;
    return z;
}

DST_NODE find_set(DST_NODE x){
    if(x->parent != x) 
        x->parent = find_set(x->parent);
    return x->parent;
}

void Union(DST_NODE x, DST_NODE y){
    DST_NODE parent_x = find_set(x), parent_y = find_set(y);
    // printf("%d %d\n", xParent->val, yParent->val);
    if(parent_x->rank > parent_y->rank)
        parent_y->parent = parent_x;
    else {
        parent_x->parent = parent_y;
        if(parent_x->rank == parent_y->rank)
            parent_y->rank++;
    }
}

Edge_Array Kruskal_MST(Edge_Array E){
    DST S = (DST)malloc(sizeof(struct DisjointSet));
    Edge_Array MST = (Edge_Array)malloc(sizeof(struct EdgeArray));

    //Initializing Disjoint set
    S->V = E->V;
    S->set = (DST_NODE *)malloc((S->V)*sizeof(DST_NODE));
    for(int i=0; i<(S->V); i++)
        S->set[i] = make_Set(i);

    // //Initializing MST
    MST->E = 0;
    MST->V = E->V;
    MST->head = NULL;

    Edge head = E->head;
    while(head != NULL){
        if(find_set(S->set[head->u]) != find_set(S->set[head->v])){
            append_Edge(MST, head->u, head->v, head->w);
            Union(S->set[head->u], S->set[head->v]);
        }
        head = head->next;
    }
    return MST;
}
int MinElement(MST_ARRAY MST){
    int min_element, min_weight = INT_MAX;
    for(int i=0; i<MST->V; i++)
        if(MST->array[i].present == false && MST->array[i].weight < min_weight){
            min_weight = MST->array[i].weight;
            min_element = i;
        }
    return min_element;
}
MST_ARRAY Prims_MST(Graph G){
    //Intialization on MST array
    MST_ARRAY MST ;
	MST= (MST_ARRAY)malloc(sizeof(struct MST_Array));
    MST->V = G->V;
    MST->array = (MST_NODE)malloc((MST->V)*sizeof(struct MST_Node));
    for(int i=0; i<MST->V; i++){
        MST->array[i].weight = INT_MAX;
        MST->array[i].present = false;
        MST->array[i].parent = -1;
    }

    MST->array[0].parent = -1;
    MST->array[0].weight = 0;

    for(int i=0; i<MST->V; i++){
        int u = MinElement(MST);
        MST->array[u].present = true;
        
        Adj_list_node head = G->array[u].head;
        while(head != NULL){
            if(MST->array[head->vertex_key].present == false && head->weight < MST->array[head->vertex_key].weight){
                MST->array[head->vertex_key].parent = u;
                MST->array[head->vertex_key].weight = head->weight;
            }
            head = head->next;
        }
    }

    return MST;
}
int main() {
	char c;
	scanf("%c",&c);
	if(c=='a'){
    Graph G = CreateGraph();
    Edge_Array E = MakeArrayEdges(G);
    Edge_Array MST = Kruskal_MST(E);
    int min_cost = 0;
    Edge test = MST->head;
    while(test != NULL){
        min_cost += test->w;
        test = test->next;
    }
    printf("%d", min_cost);}
    else{
         Graph G = CreateGraph();
    MST_ARRAY MST = Prims_MST(G);
    int min_cost = 0;
    for(int i=0; i<MST->V; i++)
        min_cost += MST->array[i].weight;
    printf("%d", min_cost);
    }
    return 0;
}
