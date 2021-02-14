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
		snprintf(fileName, sizeof(fileName),"%d", i);
		in[i] = openFile(fileName, "r");
	}
	FILE* out = openFile(output_file, "w");
	MinHeapNode* harr = malloc(sizeof(MinHeapNode) * k);
	int i;
	for (i = 0; i < k; i++)
	{
		if (fscanf(in[i], "%d ", &harr[i].m_element) != 1)
			break;
		harr[i].m_index = i;
	}
	MinHeap* hp = create(harr, i);
	int count = 0;
	while (count != i)
	{
		MinHeapNode root = getMin(hp);
		fprintf(out, "%d ", root.m_element);
		if (fscanf(in[root.m_index], "%d ", &root.m_element) != 1)
		{
			root.m_element = INT_MAX;
			count++;
		}
		replaceMin(hp, root);
	}
	for (int i = 0; i < k; i++)
		fclose(in[i]);

	fclose(out);
}

/* Using a merge-sort algorithm, create the initial runs and divide them evenly among the output files */
void createInitialRuns(char* input_file, int run_size, int num_ways)
{
	FILE* in = openFile(input_file, "r");

	FILE* out[num_ways];
	char fileName[2];
	for (int i = 0; i < num_ways; i++)
	{
		snprintf(fileName, sizeof(fileName),"%d", i);
		out[i] = openFile(fileName, "w");
	}

	int* arr = (int*)malloc(run_size * sizeof(int));

	bool more_input = true;
	int next_output_file = 0;

	int i;
	while (more_input) {
		for (i = 0; i < run_size; i++) {
			if (fscanf(in, "%d ", &arr[i]) != 1) {
				more_input = false;
				break;
			}
		}
		mergeSort(arr, 0, i - 1);
		for (int j = 0; j < i; j++)
			fprintf(out[next_output_file],"%d ", arr[j]);
		next_output_file++;
	}
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