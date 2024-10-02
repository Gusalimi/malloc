#include <stdlib.h>
#include <stdio.h>

int main() {
    char *ptr = malloc(100);
    if (ptr) {
        printf("Memory allocated successfully.\n");
    }
    return 0;
}
