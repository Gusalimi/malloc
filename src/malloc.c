/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:39:02 by gsaile            #+#    #+#             */
/*   Updated: 2024/09/26 19:10:24 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

void free(void *ptr) {
	(void)ptr;
	return ;
}

#include <stdio.h>
void *malloc(size_t size) {
	printf("%d %d %d %d\n", TINY_HEAP_ALLOC_SIZE, TINY_BLOCK_ALLOC_SIZE, SMALL_HEAP_ALLOC_SIZE, SMALL_BLOCK_ALLOC_SIZE);
	void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
	if (ptr == MAP_FAILED) {
		perror("mmap failed");
		return NULL;
	}
	return ptr;
}

void *realloc(void *ptr, size_t size) {
	(void)size;
	return ptr;
}

