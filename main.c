#include "include/malloc.h"
#include <stdio.h>
#include <string.h>

int main() {
    char *p1 = malloc(3147483648);
    char *p2 = malloc(12);
    char *p3 = malloc(467);
    char *p4 = malloc(15);
//    show_alloc_mem();
    free(p1);
    free(p2);
    free(p3);
    free(p4);
//    show_alloc_mem();
    return 0;
}
