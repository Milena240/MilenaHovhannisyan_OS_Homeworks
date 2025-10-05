#include <stdio.h>
#include <stdlib.h>

int
main()
{
	int* arr;
	const int initSize = 10;
	const int newSize = 5;
	
	arr = (int*)malloc(initSize * sizeof(int));

	if (arr == NULL) {
		printf("Initial memory allocation failed.\n");
		return 1;
	}

	printf("Enter %d integers: ", initSize);
	for (int count = 0; count < initSize; ++count) {
		scanf("%d", &arr[count]);
	}

	int* newArr = (int*)realloc(arr, newSize * sizeof(int));

	if (newArr = NULL) {
		printf("Memory reallocation failed.\n");
		free(arr);
		return 1;
	}

	newArr = arr;

	printf("Array after resizing: ");
	for (int count = 0; count < newSize; ++count) {
		printf("%d ", arr[count]);
	}
	printf("\n");

	free(arr);
	return 0;
}
