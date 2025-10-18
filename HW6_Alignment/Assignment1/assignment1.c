#include <stdio.h>

int
main()
{
	int x = 5;
	char c = 'a';
	double d = 10.5;
	short s = 5;

	printf("Size of: \n");
	printf("\tint: %zu\n", sizeof(x));
	printf("\tchar: %zu\n", sizeof(c));
	printf("\tdouble: %zu\n", sizeof(d));
	printf("\tshort: %zu\n", sizeof(s));

	printf("Addresses: \n");
	printf("\t&int: %p\n", (void*)&x);
	printf("\t&char: %p\n", (void*)&c);
        printf("\t&double: %p\n", (void*)&d);
        printf("\t&short: %p\n", (void*)&s);

	return 0;
}
