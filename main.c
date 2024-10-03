#include "include/malloc.h"
#include <stdio.h>
#include <string.h>

int main() {
    char *ptr = malloc(1000000);
	char *p2 = malloc(1050000);
    if (ptr) {
        printf("Memory allocated successfully at (%p).\n", ptr);
		strcpy(ptr, "Hello");
    }
    if (p2) {
        printf("Memory allocated successfully at (%p).\n", p2);
		strcpy(p2, "World");
    }
	printf("%s %s\n", ptr, p2);
    return 0;
}
