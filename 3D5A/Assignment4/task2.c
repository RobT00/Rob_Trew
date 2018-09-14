//Robert Trew - 15315527
//15-12-17
//Methods for dijkstra (and by extension minheap) from http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
//and http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
//and http://sybcs2011.blogspot.ie/2011/09/dijkstras-algorith-on-graph-represented.html
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define START_SIZE 30
#define INFINITY 99999

struct minheap_node {
    int id;
    int dist;
};

struct minheap {
    int size;
    int capacity;
    int *pos;
    struct minheap_node **a;
};

struct edge {
    char id;
    int weight;
    struct edge *next;
};

struct vertex {
    char id;
    int num_edges;
    struct edge *edges;
};

struct graph {
    int lim_vertices;
    int num_vertices; 
    struct vertex *vertices;
};

// Functions which manipulate edges

struct edge* edge_init (char id, int weight);
void sorted_edges (struct edge **e, struct edge *e_n);

// Functions which manipulate vertices. 

//struct vertex* vertex_new      ( char id );
int            vertex_init     ( struct vertex *v, char id );
int            vertex_add_edge ( struct vertex *v, char id, int weight );
void           vertex_print    ( struct vertex *v );
void           vertex_free     ( struct vertex *v, int num );

// Functions which manipulate the graph

struct graph*  graph_new        ();
int            graph_init       ( struct graph *g);
struct vertex* graph_get_vertex ( struct graph *g, char id );
int            graph_add_vertex ( struct graph *g, char id );
int            graph_add_edge   ( struct graph *g, char id1, char id2, int weight );
int            graph_randomize  ( struct graph *g, int numv, int nume );
void           graph_print      ( struct graph *g );
void           graph_free       ( struct graph *g );

// Searching Functions
void graph_search (struct graph *g, char id, char type); //Helper function
void DFS (struct graph *g, int visit[], char id); //Depth First Search
void BFS (struct graph *g, int visit[], char id); //Breadth First Search
void enqueue (char q[], char id);
char pop (char q[]);
int is_empty (char q[]);

// Miscellaneous Functions

void error ( const char *function, int line, char *message, ... );
int hash (char id);
void dijkstra (struct graph *g, char startnode);

int
main(int argc, char *argv[]) {
    printf("Compiled!\n");
    struct graph *graph;

    graph = graph_new();

    for (char c = 'A'; c <= 'G'; c++) {
        graph_add_vertex(graph, c);
    }
    graph_add_edge ( graph, 'A', 'B', 1 );
    graph_add_edge ( graph, 'A', 'C', 3 );
    graph_add_edge ( graph, 'A', 'F', 10 );
    graph_add_edge ( graph, 'B', 'C', 1 );
    graph_add_edge ( graph, 'B', 'D', 7 );
    graph_add_edge ( graph, 'B', 'E', 5 );
    graph_add_edge ( graph, 'B', 'G', 2 );
    graph_add_edge ( graph, 'C', 'D', 9 );
    graph_add_edge ( graph, 'C', 'E', 3 );
    graph_add_edge ( graph, 'D', 'E', 2 );
    graph_add_edge ( graph, 'D', 'F', 1 );
    graph_add_edge ( graph, 'D', 'G', 12);
    graph_add_edge ( graph, 'E', 'D', 2 );
    // Do stuff
    printf("Normal Print\n");
    graph_print(graph);    
    printf("\n");
    //dijkstra(graph, 'A');
    // terminate
    graph_free(graph);

    return EXIT_SUCCESS;
}

struct edge*
edge_init (char id, int weight) {
    struct edge *e = malloc(sizeof(struct edge));
    if (!e) {
        error (__FUNCTION__, __LINE__, "Got a NULL edge");
        return 0;
    }
    e->id = id;
    e->weight = weight;
    e->next = NULL;

    return e;
}

void
edge_print (struct edge *e) {
    if (!e) {
        error (__FUNCTION__, __LINE__, "Got a NULL edge");
        return;
    }
    while (e) {
        printf("%c (%d), ", e->id, e->weight);
        e = e->next;
    }
}

int
vertex_init ( struct vertex *v, char id ) {
    if (!v) {
        error(__FUNCTION__, __LINE__, "Got a NULL vertex");     
        return 0; 
    }
    v->id = id;
    v->num_edges = 0;
    return 1;
}

void
vertex_print ( struct vertex *v ) {
    if (!v) { 
        error(__FUNCTION__, __LINE__, "Got a NULL vertex");
        return;
    }

    printf("%c ->", v->id);
    edge_print(v->edges);

    printf("\n");
}

void
vertex_free ( struct vertex *v, int num ) {
    if (v) {
        for (int i = 0; i < num; i++) {
            free(v[i].edges);
        }
    }
    free(v);
}

int
vertex_add_edge ( struct vertex *v, char id, int weight ) {
    if ( !v ) { 
        error(__FUNCTION__, __LINE__, "Got a NULL vertex");
        return 0;
    }
    struct edge *e = edge_init(id, weight);
    if (!e) {  
        error(__FUNCTION__, __LINE__, "Could not create edge");        
        return 0;
    }
    sorted_edges(&v->edges, e);
    v->num_edges++;

    return 1;
}

struct graph *
graph_new () {
    struct graph *g;

    g = malloc(sizeof(struct graph));
    if (!graph_init (g)) {
        error(__FUNCTION__, __LINE__, "Graph allocation failed");
        graph_free(g);
        g = NULL;
    }
    return g;
}

int
graph_init (struct graph *g) {
    if (!g) { 
        error(__FUNCTION__, __LINE__, "Got a NULL graph");        
        return 0;
    };

    g->lim_vertices = START_SIZE;
    g->num_vertices = 0;
    g->vertices = malloc(sizeof(struct vertex) * g->lim_vertices);
    if(g->vertices == NULL) {
        error(__FUNCTION__, __LINE__, "Set of vertices allocation failed");
        return 0;
    }
    //Initialise adjacency list as empty
    for (int i = 0; i < g->lim_vertices; i++) {
        g->vertices[i].edges = NULL;
    }
    return 1;
}

struct vertex *
graph_get_vertex ( struct graph *g, char id ) {
    if (!g) { 
        error(__FUNCTION__, __LINE__, "Got a NULL graph");        
        return NULL;
    }
    struct vertex *v = NULL;
    int i = hash(id);
    while (i < g->lim_vertices) {
        if (g->vertices[i].id == id) {
            v = &g->vertices[i];
            break;
        }
        i++;
    }
    //Could return id if i has been incremented, shouldn't be an issue in this case however

    return v;
}

int
graph_add_vertex ( struct graph *g, char id ) {
    if (!g) {
        error(__FUNCTION__, __LINE__, "Got a NULL graph");
        return 0;
    }
    if (g->num_vertices >= g->lim_vertices) { //Capacity if 30, graph is uppercase letters, should not happen, would malloc larger
        error(__FUNCTION__, __LINE__, "Graph at maximum capacity");
        return 0;
    }
  
    struct vertex *v = graph_get_vertex(g, id);
    if (v) { 
        error(__FUNCTION__, __LINE__, "Vertex already in graph");
        return 0;
    }
 
    if (!vertex_init( &g->vertices[hash(id)], id )) { 
        error(__FUNCTION__, __LINE__, "Vertex initialization failed");
        return 0;
    }
    g->num_vertices++;
    return 1;
}

int
graph_add_edge ( struct graph *g, char id1, char id2, int weight ) {
    if (!g) {
        error(__FUNCTION__, __LINE__, "Got a NULL graph");
        return 0;
    }

    struct vertex *v1 = graph_get_vertex(g, id1);
    struct vertex *v2 = graph_get_vertex(g, id2);
    if (!v1 || !v2) { 
        error(__FUNCTION__, __LINE__, "%c not in graph", ((v1)? id2 : id1));
        return 0;
    }
    return (vertex_add_edge( v1, v2->id, weight ) && 
    vertex_add_edge(v2, v1->id, weight));
}

void
graph_print ( struct graph *g ) {
    if (!g) { 
        error(__FUNCTION__, __LINE__, "Got a NULL graph");
        return;
    }

    for ( int i=0; i<g->num_vertices; i++ ) {
        vertex_print( &g->vertices[i]);
    }
}

void
graph_free ( struct graph *g ) {
    if (g) {
        if (g->vertices) { vertex_free(g->vertices, g->lim_vertices); }
        /*for (int i = 0; i < g->lim_vertices; i++) {
            free(&g->vertices[i]);
        }*/
        free(g);
    }
}

/*void 
dijkstra (struct graph *g, int visit[], char id) {
    struct edge *e = malloc(sizeof(struct edge));
    char *q = malloc(sizeof(struct char));
    if (!e || !q) {
        error(__FUNCTION__, __LINE__, "Could not malloc");
        return;
    }
    *e = *g->vertices[hash(id)].edges;
    memset(q, '\0', g->num_vertices * sizeof(char));
    q[0] = id;
    while(e) {
        enqueue(q, g->vertices[hash(e->id)]);
    }
}*/

/*void
dijkstra (struct graph *g, char id) {
    int v_num = g->num_vertices;
    int *dist = malloc(sizeof(int) * v_num);
    if (!dist) {
        error(__FUNCTION__, __LINE__, "Cannot malloc memory");
        return;
    }
    struct minheap* min_heap = create_minheap(v_num);
    for (int i = 0; i < v_num; i++) {
        dist[v_num] = INT_MAX;
        min_heap->a[i] = new_minheap_node(i, dist[i]);
        min_heap->pos[i] = i;
    }
}*/

/*void 
DFS (struct graph *g, int visit[], char id) {
    struct edge *e = malloc(sizeof(struct edge));
    *e = *g->vertices[hash(id)].edges;
    printf("%c, ", id);
    visit[hash(id)] = 1;
   /*while (g->vertices[hash(id)].edges) {
        if (!visit[hash(g->vertices[hash(id)].edges->id)]) {
            DFS(g, visit, g->vertices[hash(id)].edges->id);
        }
        g->vertices[hash(id)].edges = g->vertices[hash(id)].edges->next;
    }
    while (e) {
        if(!visit[hash(e->id)]) {
            DFS(g, visit, e->id);
        }
        e = e->next;
    }
    free(e);
}*/

/*void
graph_search (struct graph *g, char id, char type) {
    if (!g) {
        error (__FUNCTION__, __LINE__, "Got a NULL graph");
        return;
    }
    if (!graph_get_vertex(g, id)) {
        error (__FUNCTION__, __LINE__, "Starting vertex not in graph");
        return;
    }
    int* visit = malloc(sizeof(int) * g->num_vertices);
    if (!visit) {
        error (__FUNCTION__, __LINE__, "Could not allocate memory for visted array");
        return;
    }
    memset(visit, 0, sizeof(int) * g->num_vertices);
    if (type == 'B') {BFS(g, visit, id);}
    else if (type == 'D') {DFS(g, visit, id);}
    free(visit);
}*/

/*void
BFS (struct graph *g, int visit[], char id) {
    struct edge* e = malloc(sizeof(struct edge));
    char* q = malloc(sizeof(char) * g->num_vertices);
    if (!q || !e) {
        error (__FUNCTION__, __LINE__, "Could not malloc memory");
        return;
    }
    //*e = *g->vertices[hash(id)].edges;
    memset (q, '\0', sizeof(q));
    visit[hash(id)] = 1;
    q[0] = id;
    while(!is_empty(q)) {
        id = q[0];
        printf("%c, ", id);
        pop(q);
        //Get all adjacent vertices
        /*for (int i = 0; i < g->vertices[hash(id)].num_edges; i++) {
            if (!g->vertices[hash(id)].edges || !visit[hash(g->vertices[hash(id)].edges->id)]) {
                visit[hash(g->vertices[hash(id)].edges->id)] = 1;
                enqueue(q, g->vertices[hash(id)].edges->id);
                g->vertices[hash(id)].edges = g->vertices[hash(id)].edges->next;
            }
        }
        *e = *g->vertices[hash(id)].edges;
        for (int i = 0; i < g->vertices[hash(id)].num_edges; i++) {
            if (!e || !visit[hash(e->id)]) {
                visit[hash(e->id)] = 1;
                enqueue(q, e->id);
                if (!e->next) {break;}
                e = e->next;
            }
        }
        /*for (int i = 0; i < g->vertices[hash(id)].num_edges; i++) {
            visit[hash(e->id)] = 1;
            enqueue(q, e->id);
            e = e->next;
            if (!e) {*e = *g->vertices[hash(id)].edges;}
        }
    }
    free(e);
}*/

/*void 
enqueue (char q[], char id) {
    for (int i = 0; i < sizeof(q)/sizeof(q[0]); i++) {
        if (q[i] == '\0') {
            q[i] = id;
            break;
        }
    }
}

char
pop (char q[]) {
    int i;
    char ret = q[0];
    for (i = 0; i < sizeof(q)/sizeof(q[0]); i++) {
        q[i] = q[i + 1];
    }
    return ret;
}

int
is_empty (struct minheap* min_heap) {
    return (min_heap->size == 0);
}*/

int 
hash (char id) {
    return id % 'A';
}

void
sorted_edges (struct edge **e, struct edge *e_n) {
    if (!e) {
        error (__FUNCTION__, __LINE__, "Got a NULL edge");
        return;
    }
    struct edge *tmp, *pre;
    tmp = *e;
    pre = *e;
    if (!(*e)) {
        e_n->next = NULL;
        (*e) = e_n;
    }
    else if (e_n->id <= (*e)->id) {
        e_n->next = (*e);
        (*e) = e_n;
    }
    else {
        tmp = *e;
        while (tmp->next && tmp->next->id <= e_n->id) {
            pre = tmp;
            tmp = tmp->next;
        }
        e_n->next = tmp->next;
        tmp->next = e_n;
    }
}

/*struct minheap_node* 
new_minheap_node (int id, int dist) {
    struct minheap_node* minheapnode = malloc(sizeof(struct minheap_node));
    minheapnode->id = id;
    minheapnode->dist = dist;
    return minheapnode;
}

struct minheap*
create_minheap (int capacity) {
    struct minheap* min_heap = malloc(sizeof(struct minheap));
    min_heap->pos = malloc(capacity * sizeof(int));
    min_heap->size = 0;
    min_heap->capacity = capacity;
    min_heap->array = malloc(capacity * sizeof(struct minheap_node*));
    return min_heap;
}

void 
swap(struct minheap_node **a, struct minheap_node **b) {
    struct minheap_node* t = *a;
    *a = *b;
    *b = t;
}

void
minheapify (struct minheap* min_heap, char idx) {
    int small, left, right;
    small = hash(idx);
    left = 2 * small + 1;
    right = 2 * small + 2;

    if (left < min_heap->size && 
    min_heap->a[left]->dist < min_heap->a[small]->dist) {
        small = right;
    }
    if (right < min_heap->size && 
    min_heap->a[right]->dist < min_heap->a[small]->dist) {
        small = right;
    }
    if (small != hash(idx)) {
        minheap_node* small_node = min_heap->a[small];
        minheap_node* idx_node = min_heap->a[hash(idx)];
        min_heap->pos[hash(small_node->id)] = hash(idx);
        min_heap->pos[hash(idx_node->id)] = small;
        swap(&min_heap->a[small], &&min_heap->a[hash(idx)]);
        minheapify(min_heap, small);
    }
}

struct minheap_node* 
ex_min(struct minheap* min_heap) {
    if(is_empty(min_heap)) {return NULL;}
    struct minheap_node* root = min_heap->a[0];
    struct minheap_node* last = min_heap->a[min_heap->size - 1];
    min_heap->a[0] = last;
    min_heap->pos[hash(root->v)] = min_heap->size-1;
    min_heap->pos[hash(last->id)] = 0;
    --min_heap->size;
    minheapify(min_heap, 0);
    return root;
}

void
decrease_key (struct minheap* min_heap, char id, it dist) {
    int i = min_heap->pos[hash(id)];
    min_heap->a[i]->dist = dist;
    while (i && min_heap->a[i]->dist < min_heap->array[(i - 1)/2]->dist) {
        min_heap->pos[hash(min_heap->a[i]->id)] = (i - 1)/2;
        min_heap->pos[hash(min_heap->a[(i - 1)/2]->id)] = i;
        swap(&min_heap->a[i], &min_heap->a[(i - 1)/2]);
        i = (i - 1)/2;
    }
}

int 
is_minheap (struct minheap* min_heap, char id) {
    if (min_heap->pos[hash(id)] < min_heap->size) {
        return 1;
    }
    return 0;
}*/

void
error ( const char *function, int line, char *message, ... ) {
    fprintf( stderr, "ERROR: %4d : %s : ", line, function);
    va_list argp;
    va_start(argp, message);
    vfprintf(stderr, message, argp);
    va_end(argp);
    printf("\n");
}

void 
dijkstra(struct graph *g, char startnode)
{
	int distance[g->lim_vertices];
    char pred[g->lim_vertices];
	int visited[g->lim_vertices],nextnode;
    int count,mindistance;
    char i,j;
	/*pred[] stores the predecessor of each node
	count gives the number of nodes seen so far*/
	/* A node picked up for expansion is marked as visited[node no.]=1*/
       //initialize
	struct edge *p;
    i = 'A';
	for(hash(i);hash(i)<g->num_vertices;i++)
	  {
		distance[i]=INFINITY;
		pred[i]=startnode;
        visited[i]=0;
	  }
	distance[hash(startnode)]=0;
	count=0;
	while(count<g->num_vertices-1)
	  {
		mindistance=INFINITY ;
// nextnode is the node at minimum distance
i = 'A';
		for(hash(i);hash(i)<g->num_vertices;i++)
			if(distance[i] < mindistance && !visited[i])
			   {
				mindistance=distance[i];
				nextnode=i;
			   }
//check if a better path exist through nextnode
		visited[nextnode]=1;
		for(p=g->vertices[hash(nextnode)].edges;p!=NULL;p=p->next)
			if(!visited[hash(p->id)])
				if(mindistance+p->weight<distance[hash(p->id)])
				   {
					distance[hash(p->id)]=mindistance+p->weight;
					pred[hash(p->id)]=nextnode;
				   }
		count++;
	  }

 //print the path and distance of each node
 i = 'A';
	for(hash(i);hash(i)<g->num_vertices;i++)
		if(i!=hash(startnode))
		  {
			printf("\n Distance of %c = %c ",i,distance[i]);
			printf("       Path = %c ",i);
			j=i;
			do
			  {
				j=pred[j];
				printf("<- %c ",j);
			  }while(j!=hash(startnode));
		  }
    printf("\n");
}
