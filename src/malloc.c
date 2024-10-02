/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:39:02 by gsaile            #+#    #+#             */
/*   Updated: 2024/10/01 16:28:17 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

t_heap	*g_zones[3] = { 0 };

void free(void *ptr) {
	(void)ptr;
	return ;
}

#include <stdio.h>
void *malloc(size_t size) {
	write(1, "Hello !\n", 8);
	size_t	alloc_size;
	int		zone_type;
	t_heap	*head;
	void	*ptr;

	if (size <= (size_t)TINY_BLOCK_ALLOC_SIZE) {
		zone_type = TINY;
		alloc_size = TINY_HEAP_ALLOC_SIZE;
	} else if (size <= (size_t)SMALL_BLOCK_ALLOC_SIZE) {
		zone_type = SMALL;
		alloc_size = SMALL_HEAP_ALLOC_SIZE;
	} else {
		zone_type = LARGE;
		alloc_size = size;
	}

	head = g_zones[zone_type];
	while (g_zones[zone_type])
		g_zones[zone_type] = g_zones[zone_type]->next;

	g_zones[zone_type] = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	ptr = g_zones[zone_type];
	g_zones[zone_type] = head;
    
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
	t_heap *current;

	ft_printf("TINY : %p\n", g_zones[TINY]);
	current = g_zones[TINY];
	while (current) {
		printf("%p\n", current);
		current = current->next;
	}
	ft_printf("SMALL : %p\n", g_zones[SMALL]);
	current = g_zones[SMALL];
	while (current) {
		printf("%p\n", current);
		current = current->next;
	}
	ft_printf("LARGE : %p\n", g_zones[LARGE]);
	current = g_zones[LARGE];
	while (current) {
		printf("%p\n", current);
		current = current->next;
	}
	return ;
}
