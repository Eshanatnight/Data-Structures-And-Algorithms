#ifndef MinHeap_H
#define MinHeap_H

#include "MinHeapNode.h"

typedef struct MinHeap
{
    MinHeapNode* harr; /* Pointer To Heap */
    int heap_size; /* Size OF Heap*/
}MinHeap;

MinHeap* create(MinHeapNode* a, int size);

void MinHeapify(MinHeap* heap, int i);

void merge(int arr[], int l, int m, int r);

void mergeSort(int arr[], int l, int r);

MinHeapNode getMin(MinHeap* heap);

int left(int i);

int right(int i);

void replaceMin(MinHeap* heap, MinHeapNode x);
#endif