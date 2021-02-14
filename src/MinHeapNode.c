#include "MinHeapNode.h"

/* A utility function to swap two elements */
void swap(MinHeapNode* x, MinHeapNode* y)
{
	MinHeapNode temp = *x;
	*x = *y;
	*y = temp;
}