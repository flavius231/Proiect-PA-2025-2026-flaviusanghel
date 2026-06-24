#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include "../include/query.h"
#include "../include/heap.h"

/* =========================================================
 * query.c
 * Parsarea și dispatcharea interogărilor de graf:
 *   EXISTS, EDGE, NEIGHBORS, PATH (BFS), DIJKSTRA
 * ========================================================= */

/* ----------------------------------------------------------
 * Helper de parsare
 * ---------------------------------------------------------- */

QueryType parse_query_type(const char *line)
{
    /* TODO: potrivește cuvântul cheie de la începutul liniei */
    if(!line) return Q_UNKNOWN;
    if(strncmp(line,"EXISTS",6)==0) return Q_EXISTS;
    if(strncmp(line,"EDGE",4)==0) return Q_EDGE;
    if(strncmp(line,"NEIGHBORS",9)==0) return Q_NEIGHBORS;
    if(strncmp(line,"PATH",4)==0) return Q_PATH;
    if(strncmp(line,"DIJKSTRA",8)==0) return Q_DIJKSTRA;
    return Q_UNKNOWN;
}

/* ----------------------------------------------------------
 * EXISTS
 * ---------------------------------------------------------- */

void process_exists(const BST *tree, const char *name)
{
    /* TODO: caută în BST, afișează DA/NU */
    BSTNode *temp=tree->root;
    if(tree->root==NULL || name==NULL || temp==NULL){
        printf("EXISTS %s: NU\n",name);
        return;
    }
    int ok=0;
    while(temp!=NULL){
        if(strcmp(temp->graph_node->entity.name,name)==0)
        {
            printf("EXISTS %s: DA\n",name);
            ok=1;
            break;
        }
        if(strcmp(temp->graph_node->entity.name,name)>0)
        temp=temp->left;
       else if(strcmp(temp->graph_node->entity.name,name)<0)
        temp=temp->right;
    }
    if(ok==0) printf("EXISTS %s: NU\n",name);
}

/* ----------------------------------------------------------
 * EDGE
 * ---------------------------------------------------------- */

void process_edge(const Graph *g, const BST *tree,
                  const char *src_name, const char *dest_name)
{
    /* TODO: găsește ambele noduri via BST, scanează lista de muchii
     *       a sursei pentru destinație */
     if(tree==NULL || g==NULL || src_name==NULL || dest_name==NULL)
     {
        printf("NU\n");
        return;
     }
    GraphNode *nod_src=bst_search(tree,src_name),   
            *nod_dest=bst_search(tree,dest_name);
    if(nod_src==NULL || nod_dest==NULL)
     {
        printf("EDGE %s %s: NU\n",src_name,dest_name);
        return;
     }
     EdgeNode *temp = nod_src->edges;
     int ok=0;
     while(temp !=NULL)
     {
        if(temp->dest_id==nod_dest->entity.id)
        {
            printf("EDGE %s %s: DA\n", src_name, dest_name);
            ok=1;
            break;
        }
        temp=temp->next;
     }
     if(ok==0)
     printf("EDGE %s %s: NU\n",src_name,dest_name);
}

/* ----------------------------------------------------------
 * NEIGHBORS
 * ---------------------------------------------------------- */

void process_neighbors(const Graph *g, const BST *tree,
                       const char *name)
{
    /* TODO: găsește nodul, iterează lista de muchii, afișează
     *       numele vecinilor; dacă nu există muchii de ieșire
     *       afișează "NEIGHBORS <name>: NULL" */
     if(name==NULL || tree==NULL || g==NULL) {
        printf("NU\n");
        return;
    }
    GraphNode *nod=bst_search(tree,name);
    if(nod==NULL){
        printf("NEIGHBORS %s: NULL\n",name);
        return;
    }
    printf("NEIGHBORS %s:",nod->entity.name);
    EdgeNode *temp=nod->edges;
    if(nod->edges==NULL){
        printf(" NULL\n");
        return;
    }
    while(temp!=NULL){
        printf(" %s",g->nodes[temp->dest_id].entity.name);
        temp=temp->next;
    }
    printf("\n");
}

/* ----------------------------------------------------------
 * PATH (BFS)
 * ---------------------------------------------------------- */

void process_path_bfs(const Graph *g, const BST *tree,
                      const char *src_name, const char *dest_name)
{
    /* TODO: BFS de la src la dest, reconstruiește și afișează calea;
     *       dacă nu există cale afișează "PATH <src> <dest>: NU" */
     GraphNode *src=bst_search(tree,src_name),*dest=bst_search(tree,dest_name);
     if(!src || !dest){
        printf("PATH %s %s: NU\n",src_name,dest_name);
        return;}
     int *parent=calloc(g->size,sizeof(int)),src_id=src->entity.id,dest_id=dest->entity.id;
     for(int i=0;i<g->size;i++)
     parent[i]=-1;
    Queue *q=queue_create();
    queue_enqueue(q,src->entity.name);
    parent[src_id]=src_id;
    int ok=0;
    while(!queue_is_empty(q)){
        char *nume_curent=queue_dequeue(q);GraphNode *u_node=bst_search(tree,nume_curent);int u=u_node->entity.id;
        if(u==dest_id){
            ok=1;
            free(nume_curent);
            break;}
        EdgeNode *e=g->nodes[u].edges;
        while(e){
            if(parent[e->dest_id]==-1){
                parent[e->dest_id]=u;
                queue_enqueue(q,g->nodes[e->dest_id].entity.name);
            }
            e=e->next;       }free(nume_curent);}
    while(!queue_is_empty(q)){char *leftover=queue_dequeue(q); free(leftover);}
    if(ok){
    printf("PATH %s %s: ",src->entity.name,dest->entity.name);
        int curr=dest_id,*path=malloc(g->size*sizeof(int)),path_len=0;
        while(curr!= src_id){
            path[path_len++]=curr;
            curr=parent[curr];
        }
        path[path_len++]=src_id;
        for(int i=path_len-1;i>=0;i--){
        printf("%s",g->nodes[path[i]].entity.name); if(i>0) printf(" -> ");}
    printf("\n");
    free(path);
} else
     printf("PATH %s %s: NU\n",src->entity.name,dest->entity.name);
    free(parent);
    queue_free(q);
}

/* ----------------------------------------------------------
 * DIJKSTRA
 * ---------------------------------------------------------- */

void process_dijkstra(const Graph *g, const BST *tree,
                      const char *src_name, const char *dest_name)
{
    /* TODO: Dijkstra cu min-heap, afișează costul și calea;
     *       dacă nu există cale afișează "DIJKSTRA <src> <dest>: NU" */
   GraphNode *src=bst_search(tree,src_name),*dest=bst_search(tree,dest_name);
   if(!src || !dest){
    printf("DIJKSTRA %s %s: NU\n",src_name,dest_name);
    return; }
   int n=g->size,s=src->entity.id,d=dest->entity.id;
   float *dist=malloc(n*sizeof(float));int *parent=malloc(n*sizeof(int));
   for(int i=0;i<n;i++)
   {
    dist[i]=FLT_MAX;parent[i]=-1;
   }
   MinHeap *h=heap_create(n);
   dist[s]=0;parent[s]=s;
   heap_push(h,s,0);
   while(!heap_is_empty(h)){
    int u=heap_pop(h).node_id;
    if(u==d) break;
    for(EdgeNode *e=g->nodes[u].edges;e;e=e->next){
        if(dist[u]!=FLT_MAX && dist[u]+e->cost<dist[e->dest_id]){
            dist[e->dest_id]=dist[u]+e->cost;
            parent[e->dest_id]=u;
            heap_push(h,e->dest_id,dist[e->dest_id]);
        }}}
   if(dist[d]==FLT_MAX){
    printf("DIJKSTRA %s %s: NU\n",src_name,dest_name);
   }
   else{
    int path[n],len=0,curr=d;
    while(curr!=s){ path[len++]=curr;curr=parent[curr];}
    path[len++]=s;
    printf("DIJKSTRA %s %s: COST = %.2f; DRUM = ",src_name,dest_name,(float)dist[d]);
    for(int j=len-1;j>=0;j--){
    printf("%s",g->nodes[path[j]].entity.name);
    if(j>0) printf(" -> ");
}printf("\n");
   }
   free(dist);free(parent);heap_free(h);
}

/* ----------------------------------------------------------
 * Dispatcher batch
 * ---------------------------------------------------------- */

void process_all_queries(Queue *q, const Graph *g, const BST *tree)
{
    /* TODO: extrage fiecare linie, parsează tipul, dispatchează
     *       la handlerul corespunzător */
    if(q==NULL || g==NULL || tree==NULL) return;
    while(!queue_is_empty(q)){
        char *query=queue_dequeue(q);
        if(query==NULL)
        continue;
    
    char cmd[64]={0},aux1[128]={0},aux2[128]={0};
    int aux_read=sscanf(query,"%63s %127s %127s",cmd,aux1,aux2);
    if(aux_read>=2 && strcmp(cmd,"EXISTS")==0)
    process_exists(tree,aux1);
    else if(aux_read>=3 && strcmp(cmd,"EDGE")==0)
    process_edge(g,tree,aux1,aux2);    
    else if(aux_read>=2 && strcmp(cmd,"NEIGHBORS")==0)
    process_neighbors(g,tree,aux1);
    else if(aux_read>=3 && strcmp(cmd,"PATH")==0)
    process_path_bfs(g,tree,aux1,aux2);
    else if(aux_read>=3 && strcmp(cmd,"DIJKSTRA")==0)
    process_dijkstra(g,tree,aux1,aux2);
    free(query);
}
}
