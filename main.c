#include "include/malloc.h"
#include <stdio.h>

int main() {
	printf("int *:\n");
	void *ptr = malloc(sizeof(int));
	printf("\n150 bits:\n");
	ptr = malloc(150);
	printf("\n1050 bits:\n");
	ptr = malloc(1050);
	(void)ptr;
}
