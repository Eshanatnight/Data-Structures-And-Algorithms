#ifndef MinHeapNode_H
#define MinHeapNode_H

struct MinHeapNode {
	int m_element;

	int m_index;
};

typedef struct MinHeapNode MinHeapNode;

/* Prototype of a utility function to swap two min heap nodes */
void swap(MinHeapNode* x, MinHeapNode* y);


#endif