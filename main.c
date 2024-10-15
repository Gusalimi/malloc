#include "include/malloc.h"
#include <stdio.h>
#include <string.h>

int main() {
    char *p1 = malloc(2147483648);
	char *p2 = malloc(105);
    // if (p1) {
    //     printf("Memory allocated successfully at (%p).\n", p1);
	// 	strcpy(p1, "Hello");
    // }
    // if (p2) {
    //     printf("Memory allocated successfully at (%p).\n", p2);
	// 	strcpy(p2, "World");
    // }
    // printf("free(p1)\n");
//    show_alloc_mem();
    write(1, "\n\n", 2);
	free(p1);
//    free(p1);
//    show_alloc_mem();
    write(1, "\n\n", 2);
    char *p3 = malloc(90);
    // if (p3) {
    //     printf("Memory allocated successfully at (%p).\n", p3);
	// 	strcpy(p3, "HEHE");
    // }
    // printf("free(p2)\n");
//    show_alloc_mem();
    write(1, "\n\n", 2);
    free(p2);
    free(p3);
//    show_alloc_mem();
    write(1, "\n\n", 2);
    return 0;
}
