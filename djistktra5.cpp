

#include<iostream>
#include<math.h>
using namespace std;
#define HEAP_PARENT(i) ((i-1)/2)
#define HEAP_LEFT(i) (2*i+1)
#define HEAP_RIGHT(i) (2*i+2)
 
struct heapNode 
{ 
	int v; 
	float rtime;
    int red; 
}; 

struct heap 
{ 
	int currsize;	 
	int *pos;	  
	struct heapNode **arr; 
}; 

struct heapNode* newheapNode(int v, float rtime,int red) 
{ 
	struct heapNode* heapNode = (struct heapNode*) malloc(sizeof(struct heapNode)); 
	heapNode->v = v; 
	heapNode->rtime = rtime; 
    heapNode->red=red;
	return heapNode; 
} 

struct heap* makeheap(int n) 
{ 
	struct heap* heap = (struct heap*) malloc(sizeof(struct heap)); 
	heap->pos = (int *)malloc(n * sizeof(int)); 
	heap->currsize = 0;  
	heap->arr = (struct heapNode**) malloc(n * sizeof(struct heapNode*)); 
	return heap; 
} 
void changeposition(struct heap* heap,struct heapNode* heapnode,int i){
    heap->pos[heapnode->v]=i;
    return;
}
 
void swap(struct heapNode** a, struct heapNode** b) 
{ 
	struct heapNode* t = *a; 
	*a = *b; 
	*b = t; 
} 
 
void sort(struct heap* heap, int i) 
{ 
	int k,c1,c2; 
	k = i; 
	c1 = HEAP_LEFT(i); 
	c2 = HEAP_RIGHT(i); 
    if(c1>heap->currsize && c2>heap->currsize)
        return;
    if (c2 < heap->currsize && heap->arr[c2]->rtime < heap->arr[k]->rtime ) 
	    k = c2;
	if (c1 < heap->currsize && heap->arr[c1]->rtime < heap->arr[k]->rtime ) 
	    k = c1; 
    if (k != i) 
	{ 
		heapNode *s= heap->arr[k]; 
		heapNode *t = heap->arr[i]; 
 
		changeposition(heap,s,i); 
		changeposition(heap,t,k);  
		swap(&heap->arr[k], &heap->arr[i]); 
        sort(heap,k); 
	} 
} 
struct heapNode* takeout(struct heap* heap) 
{ 
	if (heap->currsize==0) 
		return NULL; 

	struct heapNode* root = heap->arr[0]; 
	struct heapNode* last = heap->arr[heap->currsize - 1]; 
	heap->arr[0] = last; 
 
    changeposition(heap,last,0);
	changeposition(heap,root,heap->currsize-1);  
	heap->currsize--; 
	sort(heap, 0); 

	return root; 
} 

void keychange(struct heap* heap, int v, float rtime,int red) 
{ 
	int i = heap->pos[v];  
	heap->arr[i]->rtime = rtime;
    heap->arr[i]->red=red; 
 
	while (i>0 && heap->arr[i]->rtime < heap->arr[HEAP_PARENT(i)]->rtime) 
	{  
		changeposition(heap,heap->arr[i],HEAP_PARENT(i)); 
		changeposition(heap,heap->arr[HEAP_PARENT(i)],i); 
		swap(&heap->arr[i], &heap->arr[HEAP_PARENT(i)]); 
 
		i = HEAP_PARENT(i); 
	} 
} 
struct heap* build_heap(int d,int src){
    struct heap* heap=makeheap(d);
    for(int t=0;t<d;t++){
        heap->arr[t] = newheapNode(t,1000000.0000000,0);
        heap->pos[t]=t;
    }
    heap->arr[src] =newheapNode(src,1000000.0000000,0);
    heap->pos[src] =src;
    return heap;
}
class graphlistnode{
    public:
        int reach;
        int red;
        float length;
        graphlistnode *next;
};
class Graph 
{  
    public:
	    graphlistnode** arr; 
}; 

graphlistnode* newgraphlistnode(int reach, float length,int red) 
{ 
	graphlistnode* new1 = new graphlistnode(); 
	new1->reach = reach; 
	new1->length = length; 
	new1->next = NULL; 
    new1->red=red;
	return new1; 
}  
Graph* makeGraph(int n) 
{ 
	Graph* graph = new Graph(); 
	graph->arr = (struct graphlistnode**) malloc(n * sizeof(struct graphlistnode*)); 
	for (int i = 0; i < n; i++) 
		graph->arr[i] = NULL; 

	return graph; 
} 
 
Graph* edge(struct Graph* graph, int src, int reach, float length,int red) 
{  
	graphlistnode* new2 = newgraphlistnode(reach, length,red); 
	new2->next = graph->arr[src]; 
	graph->arr[src] = new2; 
 
	new2 = newgraphlistnode(src, length,red); 
	new2->next = graph->arr[reach]; 
	graph->arr[reach] = new2;
    return graph; 
} 
 
void dijkstra(struct Graph* graph, int src,int target,int k,float g,int n) 
{ 
	float reach_time[n];	  
	for (int v = 0; v < n; v++) 
	{ 
		reach_time[v] = 1000000.0000000;  
	} 
    struct heap* heap=build_heap(n,src);
	reach_time[src] = 0; 
	keychange(heap, src, reach_time[src],0);  
    heap->currsize = n; 
	while (heap->currsize!=0) 
	{ 
        struct heapNode* heapNode = takeout(heap);
		int u = heapNode->v;
        int red1=heapNode->red;
        if(u==target){
           break;
        }

		graphlistnode* walk = graph->arr[u]; 
		while (walk != NULL) 
		{ 
			int v = walk->reach; 
            int red =walk->red; 
			if (heap->pos[v] < heap->currsize && reach_time[u] != 1000000.0000000 && walk->length + reach_time[u] < reach_time[v] && k>=red1+red) 
			{ 
				reach_time[v] = reach_time[u] + walk->length;

                //cout << v << " "<< rtime[v] << endl 
				keychange(heap, v, reach_time[v],red1+red); 
			} 
			walk = walk->next; 
		} 
	} 
    //cout << reach_time[target]; 
	if(reach_time[target]<g){
        cout << "Yes" << endl;
    } 
    else
    {
        cout << "No" << endl;
    }
    
} 
 
int main() 
{ 
	int k,n,m,i=0;
    float g;
    cin >> g;
    cin >> k;
    cin >> n;
    cin >> m;
    struct Graph* graph = makeGraph(n);
    for(i=1;i<=m;i++){
        int n1,n2,c;
        float p;
        cin >> n1;
        cin >> n2;
        cin >> p;
        cin >> c;
        p=-1*log10(1-p);
        //cout << p << endl;
	    graph=edge(graph, n1-1, n2-1, p,c); 
    }
    //g=-1*log10(g);
	dijkstra(graph, 0,n-1,k,g,n); 

	return 0; 
} 
