#include <stdio.h>
#include <stdlib.h>

void printArr(const int* arr, const int n);

int
main()
{
        int n;
        printf("Enter the number of elements: ");
        scanf("%d", &n);
        if (n <= 0) {
		printf("Invalid value of elements.\n");
		return 1;
	}

	int* arr = (int*)calloc(n, sizeof(int));
	if (arr == NULL) {
		printf("Memory allocation failed.\n");
		return 1;
	}

	printf("Array after calloc: ");
	printArr(arr, n);
	
	printf("Enter %d integers: ", n);
	int sum = 0;
	
	for (int count = 0; count < n; ++count) {
		scanf("%d", &arr[count]);
		sum += arr[count];
	}

	printf("Updated array: ");
        printArr(arr, n);

	printf("Average  of the array: %.6g\n", ((double)sum / (double)n));

	free(arr);
	return 0;
}


void
printArr(const int* arr, const int n)
{
	for (int count = 0; count < n; ++count) {
		printf("%d ", arr[count]);
	}
	printf("\n");
}
