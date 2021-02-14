#include <stdio.h>
#include "fstream.h"
#include "MinHeap.h"
#include <time.h>
#include <stdlib.h>


int main()
{
	// No. of Partitions of input file.
	int num_ways = 10;

	// The size of each partition
	int run_size = 1000;

	char input_file[] = "input.txt";
	char output_file[] = "output.txt";

	FILE* in = openFile(input_file, "w");

	srand(time(NULL));

	// generate input
	for (int i = 0; i < num_ways * run_size; i++)
		fprintf(in, "%d ", rand());

	fclose(in);

	externalSort(input_file, output_file, num_ways,
				run_size);

	return 0;
}
