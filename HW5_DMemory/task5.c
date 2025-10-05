#include <stdio.h>
#include <stdlib.h>

int
main()
{
	int n;
	int* grades;

	printf("Enter the number of students: ");
	scanf("%d", &n);
	if (n <= 0) {
		printf("Invalid number of students.\n");
		return 1;
	}

	grades = (int*)malloc(n * sizeof(int));

	if (grades == NULL) {
		printf("Memory allocation failed.\n");
		return 0;
	}

	printf("Enter the grades: ");

	int highest = 0;
	int lowest = 100;
	for (int i = 0; i < n; ++i) {
		scanf("%d", &grades[i]);
		if (grades[i] < 0) {
			printf("Invalid grade.\n");
			return 1;
		}
		if (grades[i] < lowest) {
			lowest = grades[i];
		} else if (grades[i] > highest) {
			highest = grades[i];
		}
	}

	printf("Highest grade: %d\n", highest);
	printf("Lowest grade: %d\n", lowest);

	free(grades);
	return 0;

}
