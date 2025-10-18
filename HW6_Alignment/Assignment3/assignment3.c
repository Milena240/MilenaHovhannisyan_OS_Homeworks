#include <stdio.h>

#pragma pack(push, 1)
struct PackedStruct
{
	char c;
	int a;
	double d;
};
#pragma pack(pop)

struct Struct
{
	char c;
	int a;
	double d;
};

int
main()
{
	struct PackedStruct pstruct;
	struct Struct struct_;

	printf("Struct size: %zu\n", sizeof(struct_));
	printf("&c: %p\n&a: %p\n&d: %p\n", (void*)&struct_.c, (void*)&struct_.a, (void*)&struct_.d);

	printf("Struct size with #pigma: %zu\n", sizeof(pstruct));
        printf("&c: %p\n&a: %p\n&d: %p\n", (void*)&pstruct.c, (void*)&pstruct.a, (void*)&pstruct.d);

	return 0;
}
