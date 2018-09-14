//Robert Trew - 15315527
//15-12-17
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define START_SIZE 30

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

struct edge* edge_init (char id);
void sorted_edges (struct edge **e, struct edge *e_n);

// Functions which manipulate vertices. 

//struct vertex* vertex_new      ( char id );
int            vertex_init     ( struct vertex *v, char id );
int            vertex_add_edge ( struct vertex *v, char id );
void           vertex_print    ( struct vertex *v );
void           vertex_free     ( struct vertex *v, int num );

// Functions which manipulate the graph

struct graph*  graph_new        ();
int            graph_init       ( struct graph *g);
struct vertex* graph_get_vertex ( struct graph *g, char id );
int            graph_add_vertex ( struct graph *g, char id );
int            graph_add_edge   ( struct graph *g, char id1, char id2 );
int            graph_randomize  ( struct graph *g, int numv, int nume );
void           graph_print      ( struct graph *g );
void           graph_free       ( struct graph *g );

// Searching Functions
void graph_search (struct graph *g, char id, char type); //Helper function
void DFS (struct graph *g, int visit[], char id); //Depth First Search
void BFS (struct graph *g, int visit[], char id); //Breadth First Search
void enqueue (char q[], char id, int size);
char pop (char q[], int size);
int is_empty (char q[], int size);

// Miscellaneous Functions

void error ( const char *function, int line, char *message, ... );
int hash (char id);

int
main(int argc, char *argv[]) {
    printf("Compiled!\n");
    struct graph *graph;

    graph = graph_new();

    for (char c = 'A'; c <= 'F'; c++) {
        graph_add_vertex(graph, c);
    }
    graph_add_edge (graph, 'A', 'B');
    graph_add_edge (graph, 'A', 'D');
    graph_add_edge (graph, 'A', 'E');
    graph_add_edge (graph, 'B', 'C');
    graph_add_edge (graph, 'B', 'D');
    graph_add_edge (graph, 'C', 'B');
    graph_add_edge (graph, 'C', 'D');
    graph_add_edge (graph, 'D', 'F');
    graph_add_edge (graph, 'E', 'D');
    graph_add_edge (graph, 'F', 'C');
    // Do stuff
    printf("Normal Print\n");
    graph_print(graph);    
    printf("\nDFS Print\n");
    graph_search(graph, 'A', 'D');
    printf("\n\nBFS Print\n");
    graph_search(graph, 'A', 'B');
    printf("\n");
    // terminate
    graph_free(graph);

    return EXIT_SUCCESS;
}

struct edge*
edge_init (char id) {
    struct edge *e = malloc(sizeof(struct edge));
    if (!e) {
        error (__FUNCTION__, __LINE__, "Got a NULL edge");
        return 0;
    }
    e->id = id;
    e->weight = 0;
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
        printf("%c, ", e->id);
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
vertex_add_edge ( struct vertex *v, char id ) {
    if ( !v ) { 
        error(__FUNCTION__, __LINE__, "Got a NULL vertex");
        return 0;
    }
    struct edge *e = edge_init(id);
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
graph_add_edge ( struct graph *g, char id1, char id2 ) {
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
    return vertex_add_edge( v1, v2->id );;
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
        free(g);
    }
}

void 
DFS (struct graph *g, int visit[], char id) {
    struct edge *e = malloc(sizeof(struct edge));
    *e = *g->vertices[hash(id)].edges;
    printf("%c, ", id);
    visit[hash(id)] = 1;
    while (e) {
        if(!visit[hash(e->id)]) {
            DFS(g, visit, e->id);
        }
        e = e->next;
    }
    free(e);
}

void
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
}

void
BFS (struct graph *g, int visit[], char id) {
    struct edge* e = malloc(sizeof(struct edge));
    char* q = malloc(sizeof(char) * g->num_vertices);
    if (!q || !e) {
        error (__FUNCTION__, __LINE__, "Could not malloc memory");
        return;
    }
    memset (q, '\0', sizeof(q));
    visit[hash(id)] = 1;
    q[0] = id;
    while(!is_empty(q, g->num_vertices)) {
        id = q[0];
        printf("%c, ", id);
        pop(q, g->num_vertices);
        //Get all adjacent vertices
        *e = *g->vertices[hash(id)].edges;
        for (int i = 0; i < g->vertices[hash(id)].num_edges; i++) {
            if (!e || !visit[hash(e->id)]) {
                visit[hash(e->id)] = 1;
                enqueue(q, e->id, g->num_vertices);
                if (!e->next) {break;}
                e = e->next;
            }
        }
    }
    free(e);
}

void 
enqueue (char q[], char id, int size) {
    for (size_t i = 0; i < size; i++) {
        if (q[i] == '\0') {
            q[i] = id;
            break;
        }
    }
}

char
pop (char q[], int size) {
    size_t i;
    char ret = q[0];
    for (i = 0; i < size; i++) {
        q[i] = q[i + 1];
    }
    return ret;
}

int
is_empty (char q[], int size) {
    for (size_t i = 0; i < size; i++) {
        if (q[i] != '\0') {
            return 0;
        }
    }
    return 1;
}

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

void
error ( const char *function, int line, char *message, ... ) {
    fprintf( stderr, "ERROR: %4d : %s : ", line, function);
    va_list argp;
    va_start(argp, message);
    vfprintf(stderr, message, argp);
    va_end(argp);
    printf("\n");
}