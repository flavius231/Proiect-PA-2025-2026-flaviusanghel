#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/graph.h"

/* =========================================================
 * graph.c
 * Implementarea grafului direcționat ponderat cu liste de
 * adiacență.
 * ========================================================= */

/* ----------------------------------------------------------
 * Funcții ajutătoare pentru relații
 * ---------------------------------------------------------- */

const char *relation_type_to_str(RelationType type)
{
    /* TODO: returnează șir cu litere mici pentru fiecare enum de relație */
    if(type == WORKS_AT)
        return "works_at";

    if(type == FRIEND_OF)
        return "friend_of";

    if(type == LOCATED_IN)
        return "located_in";

    if(type == PARTICIPATES_IN){
        return "participates_in";
    }

        return "UNKNOWN";
}

RelationType str_to_relation_type(const char *str)
{
    /* TODO: parsează șirul relației la valoarea enum */
    if(strcmp(str,"works_at")==0)
        return WORKS_AT;
    
    if(strcmp(str,"friend_of")==0)
        return FRIEND_OF;

    if(strcmp(str,"located_in")==0)
        return LOCATED_IN;
    
    if(strcmp(str,"participates_in")==0)
        return PARTICIPATES_IN;
       
    return (RelationType)-1;
}

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

Graph *graph_create(int initial_capacity)
{
    /* TODO: alocă structura Graph și tabloul de noduri */
    Graph *g = malloc(sizeof(Graph));
    if (g == NULL) return NULL;
    g->nodes = calloc(initial_capacity, sizeof(GraphNode));
    if (g->nodes==NULL) {
        free(g);
        return NULL;
    }
    g->size=0;
    g->capacity=initial_capacity;
    return g;
}

void graph_free(Graph *g)
{
    /* TODO: eliberează șirul de nume al fiecărui nod și lista de muchii,
     *       apoi tabloul și structura */
    if (g == NULL) return;
    for (int i = 0; i < g->size; i++) {
        free(g->nodes[i].entity.name);
        EdgeNode *curr=g->nodes[i].edges;
        while (curr!=NULL) {
            EdgeNode *temp=curr;
            curr=curr->next;
            free(temp);
        }
    }
    free(g->nodes);
    free(g);
}

/* ----------------------------------------------------------
 * Mutație
 * ---------------------------------------------------------- */

int graph_add_node(Graph *g, const char *name, EntityType type)
{
    /* TODO: extinde tabloul dacă e necesar, inițializează noul GraphNode,
     *       returnează id-ul */
    if (g==NULL || name==NULL) {
        return -1;
    }
    if (g->size>=g->capacity) {
        int new_capacity=g->capacity * 2;
        GraphNode *new_nodes = realloc(g->nodes, new_capacity * sizeof(GraphNode));
        if (new_nodes == NULL) {
            return -1; 
        }
        g->nodes=new_nodes;
        int old_capacity=g->capacity;
        g->capacity=new_capacity;
        for (int i = old_capacity; i < new_capacity; i++) {
            g->nodes[i].edges = NULL;
            g->nodes[i].entity.name = NULL;
        }
    }
    int current_id=g->size;
    GraphNode *new_node=&g->nodes[current_id];
    new_node->entity.name=strdup(name); 
    if (new_node->entity.name==NULL) {
        return -1;
    }
    new_node->entity.type=type;
    new_node->entity.id=current_id;
    new_node->edges=NULL;
    g->size++;
    return current_id;
}

int graph_add_edge(Graph *g, int src_id, int dest_id,
                   RelationType type, float cost)
{
    /* TODO: alocă EdgeNode, adaugă la finalul listei de muchii a sursei
     *       pentru a păstra ordinea de inserare */
    if(g != NULL && src_id >= 0 && dest_id >= 0 && src_id < g->size && dest_id < g->size) {
        
        EdgeNode *nou = malloc(sizeof(EdgeNode));
        if(nou == NULL) return -1;
        nou->dest_id = dest_id;
        nou->cost = cost;
        nou->type = type;
        nou->next = NULL;
        if(g->nodes[src_id].edges == NULL) {
            g->nodes[src_id].edges = nou;
        } else {
            EdgeNode *temp = g->nodes[src_id].edges;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = nou;
        }
        return 0; 
    }
    return -1;
}

/* ----------------------------------------------------------
 * Funcții ajutătoare pentru interogare
 * ---------------------------------------------------------- */

int graph_find_id(const Graph *g, const char *name)
{
    /* TODO: scanare liniară returnând id-ul potrivit sau -1 */
    if (g == NULL || name == NULL) return -1;
    for (int i = 0;i<g->size;i++) {
        if (strcmp(g->nodes[i].entity.name, name) == 0) {
            return i;
        }
    }
    return -1;
}

GraphNode *graph_get_node(const Graph *g, int id)
{
    /* TODO: verifică limitele și returnează pointerul */
    if (g==NULL || id<0 || id>=g->size) {
        return NULL;
    }
    return &g->nodes[id];
}

/* ----------------------------------------------------------
 * Afișare
 * ---------------------------------------------------------- */

void graph_print(const Graph *g)
{
    /* TODO: afișează fiecare nod și lista sa de muchii */
    if (g == NULL) return;
    for (int i = 0; i<g->size; i++) {
    printf("%d %s:",i,g->nodes[i].entity.name);
        EdgeNode *curr = g->nodes[i].edges;
            while (curr != NULL) {
                printf(" [%d %s %.2f]",curr->dest_id,relation_type_to_str(curr->type),curr->cost);
                curr = curr->next;
            }printf("\n");
    }
}
