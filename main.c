#include "include/malloc.h"
#include <string.h>

int main() {
    // Test 1: Simple small allocation and free
    ft_printf("Test 1: Small allocation and free\n");
    void *ptr1 = malloc(32);  // Allocate 32 bytes
    if (ptr1 != NULL) {
        ft_printf("Allocated 32 bytes at %p\n", ptr1);
    }
    show_alloc_mem();  // Show allocated memory
    free(ptr1);
    ft_printf("\nFreed 32 bytes\n\n");
    show_alloc_mem();  // Show allocated memory after free
    ft_printf("\n\n");

    // Test 2: Allocate large memory block
    ft_printf("Test 2: Large allocation\n");
    void *ptr2 = malloc(1024 * 1024);  // Allocate 1MB
    if (ptr2 != NULL) {
        ft_printf("Allocated 1MB at %p\n", ptr2);
    }
    show_alloc_mem();
    free(ptr2);
    ft_printf("\nFreed 1MB\n\n");
    show_alloc_mem();
    ft_printf("\n\n");

    // Test 3: Allocate multiple blocks
    ft_printf("Test 3: Multiple allocations\n");
    void *ptr3 = malloc(64);   // 64 bytes
    void *ptr4 = malloc(128);  // 128 bytes
    void *ptr5 = malloc(256);  // 256 bytes
    ft_printf("Allocated 64 bytes at %p\n", ptr3);
    ft_printf("Allocated 128 bytes at %p\n", ptr4);
    ft_printf("Allocated 256 bytes at %p\n", ptr5);
    show_alloc_mem();
    free(ptr4);  // Free the middle block
    ft_printf("\nFreed 128 bytes\n\n");
    show_alloc_mem();
    free(ptr3);
    free(ptr5);
    ft_printf("\nFreed remaining blocks\n\n");
    show_alloc_mem();
    ft_printf("\n\n");

    // Test 4: Stress test with small allocations
    ft_printf("Test 4: Stress test with small allocations\n");
    void *ptrs[100];
    for (int i = 0; i < 100; i++) {
        ptrs[i] = malloc(16);  // Allocate 16 bytes
    }
    show_alloc_mem();
    for (int i = 0; i < 100; i++) {
        free(ptrs[i]);  // Free all allocated blocks
    }
    ft_printf("\nFreed 100 small blocks\n\n");
    show_alloc_mem();
    ft_printf("\n\n");

    // Test 5: Allocate 0 bytes (edge case)
    ft_printf("Test 5: Allocate 0 bytes (edge case)\n");
    void *ptr6 = malloc(0);  // Allocate 0 bytes
    if (ptr6 == NULL) {
        ft_printf("Allocation of 0 bytes returned NULL (expected behavior)\n");
    }
    show_alloc_mem();
    ft_printf("\n\n");

    // Test 6: Allocate after free (reuse)
    ft_printf("Test 6: Allocate after free (reuse memory)\n");
    ptr1 = malloc(128);
    free(ptr1);
    ptr1 = malloc(64);  // Allocate again, potentially reusing freed block
    ft_printf("Allocated 64 bytes after freeing 128 bytes at %p\n", ptr1);
    show_alloc_mem();
    free(ptr1);
    ft_printf("\nFreed 64 bytes\n\n");
    show_alloc_mem();


    // Test 7: Realloc behavior
    ft_printf("\nTest 7: Realloc behavior\n\n");

    // Realloc to a larger size
    void *ptr7 = malloc(64);  // Allocate 64 bytes
    ft_printf("Allocated 64 bytes at %p\n", ptr7);
    show_alloc_mem();

    ptr7 = realloc(ptr7, 128);  // Reallocate to 128 bytes
    if (ptr7 != NULL) {
        ft_printf("Reallocated to 128 bytes at %p\n", ptr7);
    }
    show_alloc_mem();

    // Realloc to a smaller size
    ptr7 = realloc(ptr7, 32);  // Reallocate to 32 bytes
    if (ptr7 != NULL) {
        ft_printf("Reallocated to 32 bytes at %p\n", ptr7);
    }
    show_alloc_mem();

    free(ptr7);
    ft_printf("\nFreed 32 bytes\n\n");
    show_alloc_mem();

    // Realloc a NULL pointer (should behave like malloc)
    ft_printf("Realloc NULL pointer\n");
    void *ptr8 = realloc(NULL, 64);  // Equivalent to malloc(64)
    if (ptr8 != NULL) {
        ft_printf("Reallocated NULL to 64 bytes at %p\n", ptr8);
    }
    show_alloc_mem();

    free(ptr8);
    ft_printf("\nFreed 64 bytes\n\n");
    show_alloc_mem();

    // Realloc to 0 bytes (should free the block)
    ptr8 = malloc(64);
    ft_printf("Allocated 64 bytes at %p\n", ptr8);
    show_alloc_mem();

    ptr8 = realloc(ptr8, 0);  // Equivalent to free(ptr8)
    if (ptr8 == NULL) {
        ft_printf("Reallocated 64 bytes to 0 (freed the block)\n");
    }
    show_alloc_mem();
    ft_printf("\n\n");

    // Test 8: Memory Defragmentation during free
    ft_printf("Test 8: Memory defragmentation during free\n");

    // Allocate multiple small blocks
    void *ptr9 = malloc(144);
    void *ptr10 = malloc(256);
    void *ptr11 = malloc(144);
    ft_printf("Allocated 144 bytes at %p, 256 bytes at %p, and 144 bytes at %p\n", ptr9, ptr10, ptr11);
    show_alloc_mem();

    // Free adjacent blocks (ptr9 and ptr10)
    free(ptr9);
    free(ptr10);
    ft_printf("\nFreed 144 and 256 bytes (adjacent blocks)\n");
    show_alloc_mem();

    // Allocate a large block that could reuse the defragmented space
    void *ptr12 = malloc(312);  // This should fit into the previously freed space if defragmentation works
    if (ptr12 != NULL) {
        ft_printf("Allocated 312 bytes at %p (after defragmentation)\n", ptr12);
    }
    show_alloc_mem();

    free(ptr12);
    free(ptr11);
    ft_printf("\nFreed 256 and 312 bytes\n\n");
    show_alloc_mem();

    return 0;
}

