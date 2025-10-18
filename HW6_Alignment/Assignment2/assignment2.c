#include <stdio.h>

struct A 
{
	//char c;
	//int a;
	double d;
	int a;
	char c;
};

int
main()
{
	struct A a;

	printf("Size od struct a: %zu\n", sizeof(a));
	printf("&d: %p\n", (void*)&a.d);
	printf("&a: %p\n", (void*)&a.a);
        printf("&c: %p\n", (void*)&a.c);
	//printf("&a: %p\n", (void*)&a.a);
	//printf("&d: %p\n", (void*)&a.d);
	return 0;

}
