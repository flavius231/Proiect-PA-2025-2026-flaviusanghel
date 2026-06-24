#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "../include/heap.h"

/* =========================================================
 * heap.c
 * Min-heap de perechi (node_id, dist) pentru Dijkstra.
 * Folosește un tablou dinamic cu indexarea standard
 * părinte/copil:
 *   parinte(i)       = (i - 1) / 2
 *   copil_stang(i)   = 2 * i + 1
 *   copil_drept(i)   = 2 * i + 2
 * ========================================================= */

/* ----------------------------------------------------------
 * Helper intern de swap
 * ---------------------------------------------------------- */

static void swap(HeapNode *a, HeapNode *b) __attribute__((unused));
static void swap(HeapNode *a, HeapNode *b)
{
    /* TODO: interschimbă cele două elemente HeapNode */
    HeapNode aux=*a;
    *a=*b;
    *b=aux;
}

/* ----------------------------------------------------------
 * Funcții de sift
 * ---------------------------------------------------------- */

static void sift_up(MinHeap *h, int i) __attribute__((unused));
static void sift_up(MinHeap *h, int i)
{
    /* TODO: mută elementul de la indexul i în sus până când
     *       proprietatea heap este respectată */
        while(i>0){
     int dad=(i-1)/2;
    if(h->data[i].dist<h->data[dad].dist){//dist deoarece imi trebuie nodul cel mai aproape de sursa(ca prioritate)
        swap(&h->data[i],&h->data[dad]);
        i=dad;
    }
    else break;
        }
}

static void sift_down(MinHeap *h, int i) __attribute__((unused));
static void sift_down(MinHeap *h, int i)
{
    /* TODO: mută elementul de la indexul i în jos până când
     *       proprietatea heap este respectată */

    while(1){
        int left=2*i+1,right=2*i+2,min=i;//compar stanga dreapta sa gasesc min si interschimb
        if(left<h->size && h->data[left].dist<h->data[min].dist)
        min=left;
        if(right<h->size && h->data[right].dist<h->data[min].dist)
        min=right;
        
        if(min!=i){
            swap(&h->data[i],&h->data[min]);
            i=min;
        }
        else break;
    }
}

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

MinHeap *heap_create(int initial_capacity)
{
    /* TODO: alocă MinHeap și tabloul său de date */
    MinHeap *h=malloc(sizeof(MinHeap));
    if(h==NULL) return NULL;
    h->data=calloc(initial_capacity,sizeof(HeapNode));
    if(h->data==NULL) {
        free(h);
        return NULL;}
    h->size=0;
    h->capacity=initial_capacity;
    return h;
}

void heap_free(MinHeap *h)
{
    /* TODO: eliberează tabloul de date, apoi structura */
    if(h==NULL) return;
    if(h->data!=NULL) free(h->data);
    free(h);
}

/* ----------------------------------------------------------
 * Operații de bază
 * ---------------------------------------------------------- */

int heap_parent(int i) { return (i <= 0) ? -1 : (i - 1) / 2; }

int heap_push(MinHeap *h, int node_id, float dist)
{
    /* TODO: adaugă elementul, extinde dacă e necesar, execută sift up */
    if(h==NULL) return 0;
    if (h->size == h->capacity) {
        h->capacity *= 2;
    HeapNode *tmp = realloc(h->data, h->capacity * sizeof(HeapNode));
    if (tmp) h->data = tmp;
    else return 0;
    }
    int i = h->size++;
    while (i > 0 && dist < h->data[heap_parent(i)].dist) {
        h->data[i] = h->data[heap_parent(i)];
        i = heap_parent(i);
    }
    h->data[i].node_id = node_id;
    h->data[i].dist = dist;
    return 1;
}

HeapNode heap_pop(MinHeap *h)
{
    /* TODO: interschimbă rădăcina cu ultimul element, micșorează,
     *       execută sift down, returnează vechea rădăcină */
    if(h==NULL || h->size==0) {
        HeapNode gol={-1,-1.0f};
        return gol;
    }
    HeapNode aux=h->data[0];
   h->data[0]=h->data[h->size-1];
   h->size--;
   if(h->size>0)
   sift_down(h,0);
    return aux;
}

int heap_is_empty(const MinHeap *h)
{
    /* TODO: returnează 1 când size == 0 */
    if(h==NULL || h->size==0)
    return 1;
    return 0;
}

int heap_decrease_key(MinHeap *h, int node_id, float new_dist)
{
    /* TODO: găsește node_id, actualizează dist dacă e mai mic,
     *       execută sift up */
    if(h==NULL) return 0;
     int i=0;
     for(i=0;i<h->size;i++){
        if(h->data[i].node_id==node_id){
            if(h->data[i].dist>new_dist)
            {
                h->data[i].dist=new_dist;
                sift_up(h,i);
                        }
                        return 1;
        }
    }
     return 0;
     
}
