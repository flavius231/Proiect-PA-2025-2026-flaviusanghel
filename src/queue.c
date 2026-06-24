#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/queue.h"

/* =========================================================
 * queue.c
 * Coadă FIFO susținută de o listă simplu înlănțuită.
 * Stochează copii alocate pe heap ale șirurilor.
 * ========================================================= */

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

Queue *queue_create(void)
{
    /* TODO: alocă și inițializează cu zero o structură Queue */
    Queue *q=(Queue*)malloc(sizeof(Queue));
    if(q==NULL) return NULL;
    q->front=NULL;
    q->rear=NULL;
    q->size=0;
    return q;
}

void queue_free(Queue *q)
{
    /* TODO: golește coada eliberând fiecare nod și datele sale */
    if(q==NULL)
    return;
    QueueNode *temp=q->front;
    while(temp!=NULL){
        QueueNode *next_node=temp->next;
        if(temp->data)
        free(temp->data);
        free(temp);
        temp=next_node;
    }
    free(q);
}

/* ----------------------------------------------------------
 * Mutație
 * ---------------------------------------------------------- */

int queue_enqueue(Queue *q, const char *data)
{
    /* TODO: duplică data, alocă QueueNode, adaugă la capătul rear */
    if(q==NULL || data==NULL) return 0;
     QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
     if(node==NULL) return 0;
    node->data=strdup(data);
    node->next  = NULL;
    if (q->front==NULL) {
        q->front = node;
        q->rear  = node;
    } else {
        q->rear->next = node;
        q->rear       = node;}
        q->size++;
        return 1;
}

char *queue_dequeue(Queue *q)
{
    /* TODO: elimină nodul din față, returnează datele sale (apelantul
     *       eliberează) */
     if(q==NULL ||q->front==NULL) return NULL;
    QueueNode *temp   = q->front;
    char *data=temp->data;
    q->front      = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    q->size--;
    return data;

}

/* ----------------------------------------------------------
 * Inspecție
 * ---------------------------------------------------------- */

int queue_is_empty(const Queue *q)
{
    /* TODO: returnează 1 când size == 0 */
    if(q==NULL || q->size==0) return 1;
    return 0;
}

void queue_print(const Queue *q)
{
    /* TODO: iterează de la front la rear, afișează fiecare șir de date */
    if(q==NULL) return ;
    QueueNode *temp=q->front;
    while(temp!=NULL)
    {
        printf("%s\n",temp->data);
        temp=temp->next;
    }
}
