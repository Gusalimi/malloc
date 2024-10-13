#include "include/malloc.h"
#include <stdio.h>
#include <string.h>

int main() {
    char *p1 = malloc(100);
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
	// free(p1);
    free(p1);
    char *p3 = malloc(90);
    // if (p3) {
    //     printf("Memory allocated successfully at (%p).\n", p3);
	// 	strcpy(p3, "HEHE");
    // }
    // printf("free(p2)\n");
    free(p2);
    free(p3);
    return 0;
}
