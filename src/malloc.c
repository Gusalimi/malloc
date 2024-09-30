/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:39:02 by gsaile            #+#    #+#             */
/*   Updated: 2024/09/30 10:35:22 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

void free(void *ptr) {
	(void)ptr;
	return ;
}

#include <stdio.h>
void *malloc(size_t size) {
	if (size <= (size_t)TINY_BLOCK_ALLOC_SIZE)
		ft_printf("Tiny Block\n");
	else if (size <= (size_t)SMALL_BLOCK_ALLOC_SIZE)
		ft_printf("Small Block\n");
	else
		ft_printf("Large Block\n");
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

void show_alloc_mem() {
	return ;
}
