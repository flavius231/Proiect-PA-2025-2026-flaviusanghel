#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/bst.h"

/* =========================================================
 * bst.c
 * BST indexat după numele entității; nodurile conțin pointeri
 * în tabloul de noduri al grafului (fără duplicarea datelor).
 * ========================================================= */

/* ----------------------------------------------------------
 * Funcții auxiliare interne (statice, neexportate)
 * ---------------------------------------------------------- */

/* Eliberează recursiv nodii BSTNode (nu GraphNode-urile spre care
 * pointează — acelea aparțin Grafului). */
static void bst_free_recursive(BSTNode *node)
   __attribute__((unused));
static void bst_free_recursive(BSTNode *node)
{
    /* TODO: traversare post-ordine pentru eliberarea fiecărui BSTNode */
    if(node==NULL) return;
    bst_free_recursive(node->left);
    bst_free_recursive(node->right);
    free(node);
}

/* Inserare recursivă; returnează rădăcina (posibil nouă) a subarbore. */
static BSTNode *bst_insert_recursive(BSTNode *node, GraphNode *gn)
    __attribute__((unused));
static BSTNode *bst_insert_recursive(BSTNode *node, GraphNode *gn)
{
    /* TODO: compară numele, recursie stânga/dreapta, alocă la NULL */
    if(node==NULL){
        BSTNode *nou_nod=malloc(sizeof(BSTNode));
        if(nou_nod==NULL) return NULL;
        nou_nod -> graph_node = gn;
        nou_nod->left=NULL;
        nou_nod->right=NULL;
        return nou_nod;
    }
    if(strcmp(gn->entity.name, node->graph_node->entity.name)<0)
   node->left=bst_insert_recursive(node->left,gn);
    else if( strcmp(gn->entity.name, node->graph_node->entity.name)>0 ) 
    node->right=bst_insert_recursive(node->right,gn); 
    return node;
    
}

/* Căutare recursivă; returnează GraphNode* sau NULL. */
static GraphNode *bst_search_recursive(const BSTNode *node, const char *name)
   __attribute__((unused));
static GraphNode *bst_search_recursive(const BSTNode *node, const char *name)
{
    /* TODO: compară name, recursie stânga/dreapta */  
    if (node == NULL) {
        return NULL;
    }
    if(strcmp(name,node->graph_node->entity.name)==0){
        return node->graph_node;
    } 
    else if(strcmp(name,node->graph_node->entity.name)<0)
    return bst_search_recursive(node->left,name);
    
    else 
    return bst_search_recursive(node->right,name);
}

/* Traversare inordine pentru afișare. */
static void bst_inorder_recursive(const BSTNode *node)
   __attribute__((unused));
static void bst_inorder_recursive(const BSTNode *node)
{
    /* TODO: stânga -> vizitare -> dreapta */
    if(node==NULL) return;
    bst_inorder_recursive(node->left);
    printf("%d %s %s\n",node->graph_node->entity.id,node->graph_node->entity.name,entity_type_to_str(node->graph_node->entity.type));
    bst_inorder_recursive(node->right);
    
}

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

/* Alocă și inițializează un BST gol. Returnează NULL la eșec. */
BST *bst_create(void)
{
    /* TODO: alocă structura BST și inițializează root-ul cu NULL */
    BST *node=calloc(1,sizeof(BST));
    if(node==NULL) return NULL;
    node->root =NULL;
    return node;
}

/* Eliberează recursiv toți nodii BST, apoi structura BST. */
void bst_free(BST *tree)
{
    /* TODO: traversare post-ordine pentru eliberarea memoriei */
    if(tree==NULL) return;
    bst_free_recursive(tree->root);
    free(tree);
}

/* ----------------------------------------------------------
 * Mutație
 * ---------------------------------------------------------- */

int bst_insert(BST *tree, GraphNode *graph_node)
{
    /* TODO: deleghează la helper-ul recursiv, actualizează tree->root */
    if(tree==NULL || graph_node == NULL)
    return 0;
    BSTNode *temp=bst_insert_recursive(tree->root,graph_node);
    if(!temp) return 0;
    tree->root=temp;
    return 1;
}

/* ----------------------------------------------------------
 * Interogare
 * ---------------------------------------------------------- */

GraphNode *bst_search(const BST *tree, const char *name)
{
    /* TODO: deleghează la helper-ul recursiv */
    if(tree == NULL || name == NULL )
    return NULL;
    return bst_search_recursive(tree->root,name);
}

/* ----------------------------------------------------------
 * Afișare
 * ---------------------------------------------------------- */

void bst_inorder_print(const BST *tree)
{
    /* TODO: deleghează la helper-ul recursiv */
    if(tree==NULL) return;
    bst_inorder_recursive(tree->root);
}