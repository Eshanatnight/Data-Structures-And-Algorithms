#include "MinHeap.h"
#include <stdlib.h>

/* Builds a heap from a given array a[] of given size */
MinHeap* create(MinHeapNode* a, int size)
{
    MinHeap* newHeap = (MinHeap*) malloc(size * sizeof(MinHeapNode));
    newHeap->harr = a;
    int i = (newHeap->heap_size - 1) / 2;
    while (i >= 0) {
		MinHeapify(newHeap, i);
		i--;
	}

    return newHeap;
}

/* A recursive method to heapify a subtree with root at given index. This method assumes that the subtrees are already heapified */
void MinHeapify(MinHeap* heap, int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if(l < heap->heap_size && heap->harr[l].m_element < heap->harr[i].m_element)
        smallest = l;

    if (r < heap->heap_size && heap->harr[r].m_element < heap->harr[smallest].m_element)
		smallest = r;

	if (smallest != i)
    {
		swap(&(heap->harr[i]), &(heap->harr[smallest]));
		MinHeapify(heap, smallest);
	}
}

/* Merges two subarrays of arr[]. First subarray is arr[l..m] Second subarray is arr[m+1..r] */
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int L[n1], R[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	// Initial index of first subarray
	i = 0;

	// Initial index of second subarray
	j = 0;

	// Initial index of merged subarray
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j])
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	}

	/* Copy the remaining elements of L[],
		if there are any */
	while (i < n1)
		arr[k++] = L[i++];

	/* Copy the remaining elements of R[],
		if there are any */
	while (j < n2)
		arr[k++] = R[j++];
}

/* l is for left index and r is right index of the sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
	if (l < r) {
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l + (r - l) / 2;

		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

/* to get index of left child of node at index i */
int left(int i)
{
	return (2 * i + 1);
}

/* to get index of right child of node at index i */
int right(int i)
{
	return (2 * i + 2);
}

/* to get the root */
MinHeapNode getMin(MinHeap* heap)
{
	return heap->harr[0];
}

/* to replace root with new node x and heapify() new root */
void replaceMin(MinHeap* heap, MinHeapNode x)
{
	heap->harr[0] = x;
	MinHeapify(heap, 0);
}