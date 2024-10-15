#include "include/malloc.h"
#include <stdio.h>
#include <string.h>

int main() {
    char *p1 = malloc(3147483648);
    show_alloc_mem();
    free(p1);
    show_alloc_mem();
    return 0;
}
