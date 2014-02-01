#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynarr.h"

int cmpfunc(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}

int main(int argc, char **argv)
{
	int i;
	int *arr;

	if(argc < 2) {
		printf("pass a bunch of numbers to sort them\n");
		return 1;
	}

	/* create a new dynamic array of string pointers */
	arr = dynarr_alloc(0, sizeof *arr);

	for(i=1; i<argc; i++) {
		char *endp;
		int n = strtol(argv[i], &endp, 0);
		if(endp == argv[i]) {
			fprintf(stderr, "%s is not a number\n", argv[i]);
			dynarr_free(arr);
			return 1;
		}

		/* add a new string to the array (the argument is copied) */
		arr = dynarr_push(arr, &n);
	}

	qsort(arr, dynarr_size(arr), sizeof *arr, cmpfunc);

	for(i=0; i<dynarr_size(arr); i++) {
		printf("%d\n", arr[i]);
	}

	dynarr_free(arr);
	return 0;
}
