#include <stdio.h>
#include <stdlib.h>

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

	int* arr = (int*)malloc(n * sizeof(int));
	if (arr == NULL) {
		printf("Memory allocation failed.\n");
		return 1;
	}
	
	printf("Enter %d integers: ", n);
	int sum = 0;
	
	for (int count = 0; count < n; ++count) {
		scanf("%d", &arr[count]);
		sum += arr[count];
	}

	printf("Sum of the array: %d\n", sum);

	free(arr);
	return 0;
}
