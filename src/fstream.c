#include "fstream.h"
#include "MinHeap.h"
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/* Utility Function to open a file */
FILE* openFile(char* fileName, char* mode)
{
	FILE* fp = fopen(fileName, mode);
	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	return fp;
}


/* Merges k sorted files. Names of files are assumed to be 1, 2, 3, ... k */
void mergeFiles(char* output_file, int n, int k)
{
	FILE* in[k];
	for (int i = 0; i < k; i++)
	{
		char fileName[2];

		// convert i to string
		snprintf(fileName, sizeof(fileName),"%d", i);

		// Open output files in read mode.
		in[i] = openFile(fileName, "r");
	}

	// FINAL OUTPUT FILE
	FILE* out = openFile(output_file, "w");

	// Create a min heap with k heap
	// nodes. Every heap node
	// has first element of scratch
	// output file
	MinHeapNode* harr = malloc(sizeof(MinHeapNode) * k);
	int i;
	for (i = 0; i < k; i++)
	{
		// break if no output file is empty and
		// index i will be no. of input files
		if (fscanf(in[i], "%d ", &harr[i].m_element) != 1)
			break;

		harr[i].m_index = i;

	}
	// Create the heap
	MinHeap* hp = create(harr, i);

	int count = 0;

	// Now one by one get the
	// minimum element from min
	// heap and replace it with
	// next element.
	// run till all filled input
	// files reach EOF
	while (count != i)
	{
		// Get the minimum element
		// and store it in output file
		MinHeapNode root = getMin(hp);
		fprintf(out, "%d ", root.m_element);

		// Find the next element that
		// will replace current
		// root of heap. The next element
		// belongs to same
		// input file as the current min element.
		if (fscanf(in[root.m_index], "%d ", &root.m_element) != 1)
		{
			root.m_element = INT_MAX;
			count++;
		}

		// Replace root with next
		// element of input file
		replaceMin(hp, root);
	}

	// close input and output files
	for (int i = 0; i < k; i++)
		fclose(in[i]);

	fclose(out);
}

/* Using a merge-sort algorithm, create the initial runs and divide them evenly among the output files */
void createInitialRuns(char* input_file, int run_size, int num_ways)
{
	// For big input file
	FILE* in = openFile(input_file, "r");

	// output scratch files
	FILE* out[num_ways];
	char fileName[2];
	for (int i = 0; i < num_ways; i++)
	{
		// convert i to string
		snprintf(fileName, sizeof(fileName),
				"%d", i);

		// Open output files in write mode.
		out[i] = openFile(fileName, "w");
	}

	// allocate a dynamic array large enough
	// to accommodate runs of size run_size
	int* arr = (int*)malloc(run_size * sizeof(int));

	bool more_input = true;
	int next_output_file = 0;

	int i;
	while (more_input) {
		// write run_size elements
		// into arr from input file
		for (i = 0; i < run_size; i++) {
			if (fscanf(in, "%d ", &arr[i]) != 1) {
				more_input = false;
				break;
			}
		}

		// sort array using merge sort
		mergeSort(arr, 0, i - 1);

		// write the records to the
		// appropriate scratch output file
		// can't assume that the loop
		// runs to run_size
		// since the last run's length
		// may be less than run_size
		for (int j = 0; j < i; j++)
			fprintf(out[next_output_file],
					"%d ", arr[j]);

		next_output_file++;
	}

	// close input and output files
	for (int i = 0; i < num_ways; i++)
		fclose(out[i]);

	fclose(in);
}

/* For sorting data stored on disk */
void externalSort(char* input_file, char* output_file, int num_ways, int run_size)
{
	// read the input file,
	// create the initial runs,
	// and assign the runs to
	// the scratch output files
	createInitialRuns(input_file,
					run_size, num_ways);

	// Merge the runs using
	// the K-way merging
	mergeFiles(output_file, run_size, num_ways);
}