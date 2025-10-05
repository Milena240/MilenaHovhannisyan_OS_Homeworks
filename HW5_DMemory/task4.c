#include <stdlib.h>
#include <stdio.h>

int
main()
{
        const int count = 3;
	const int newCount = 5;
        const int size = 50;
        char** arr;

        arr = (char**)malloc(count * sizeof(char*));

        if (arr == NULL) {
                printf("Memory allocation failed.\n");
                return 1;
        }

        for (int i = 0; i < count; ++i) {
                arr[i] = (char*)malloc(size * sizeof(char));
                if (arr[i] == NULL) {
                        printf("Memory allocation failed.\n");
			free(arr);
                        return 1;
                }
        }

        printf("Enter %d strings: ", count);
        for (int i = 0; i < count; ++i) {
                scanf("%49s", arr[i]);
        }

	char** newArr = (char**)realloc(arr, newCount * sizeof(char*));
	if (newArr == NULL) {
		printf("Memory reallocation failed.\n");
		for(int i = 0; i < count; ++i) free(arr[i]);
		free(arr);
		return 1;
	}

	arr = newArr;

	for (int i = count; i < newCount; ++i) {
		arr[i] = (char*) malloc(size * sizeof(char));
		if (arr[i] == NULL) {
			printf("Memory allocation failed.\n");
			for(int j = 0; j < i; ++j) free(arr[j]);
			free(arr);
			return 1;
		}
	}

	printf("Enter %d more strings: ", newCount - count);
	for (int i = count; i < newCount; ++i) {
		scanf("%49s", arr[i]);
	}

	printf("All strings: ");
	for (int i = 0; i < newCount; ++i) {
		printf("%s ", arr[i]);
	}
	printf("\n");

	for (int i = 0; i < newCount; ++i) {
		free(arr[i]);
	}
	free(arr);

	return 0;

}

