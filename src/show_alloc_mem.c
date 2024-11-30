/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:59:34 by gsaile            #+#    #+#             */
/*   Updated: 2024/11/30 12:06:51 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

bool	heap_is_empty(t_heap *heap) {
	t_block *block = (t_block *)((char *)heap + sizeof(t_heap));
	while (block) {
		if (block->freed == FALSE)
			return (FALSE);
		block = block->next;
	}
	return (TRUE);
}

bool	zone_is_empty(t_heap *heap) {
	while (heap) {
		if (!heap_is_empty(heap)) {
			return (FALSE);
		}
		heap = heap->next;
	}
	return (TRUE);
}

void	print_zone(t_heap *zone, char *zone_name, t_zone_types zone_type) {
	t_heap	*current_heap;
	t_block	*current_block;
	char	*block_data;

	if (!zone || zone_is_empty(zone)) {
		ft_printf("%s : None\n", zone_name);
		return ;
	}
	ft_printf("%s : %p\n", zone_name, g_zones[zone_type]);
	current_heap = zone;
	while (current_heap) {
		current_block = (t_block *)((char *)current_heap + sizeof(t_heap));
		while (current_block) {
			if (!current_block->freed && current_block->size > 0) {
				block_data = (char *)current_block + sizeof(t_block);
				ft_printf("%p - %p : %zu bytes\n", block_data, block_data + current_block->size, current_block->size);
			}
			current_block = current_block->next;
		}
		current_heap = current_heap->next;
	}
}

void	print_large_zone(void) {
	t_heap	*current_heap;
	char	*heap_data;

	if (!g_zones[LARGE]) {
		ft_printf("LARGE : None\n");
		return ;
	}
	ft_printf("LARGE : %p\n", g_zones[LARGE]);
	current_heap = g_zones[LARGE];
	while (current_heap) {
		heap_data = (char *)current_heap + sizeof(t_heap);
		(void)heap_data;
		ft_printf("%p - %p : %zu bytes\n", heap_data, heap_data + current_heap->size - sizeof(t_heap), current_heap->size - sizeof(t_heap));
		current_heap = current_heap->next;
	}
}

void show_alloc_mem() {
	pthread_mutex_lock(&malloc_mutex);
	print_zone(g_zones[TINY], "TINY", TINY);
	print_zone(g_zones[SMALL], "SMALL", SMALL);
	print_large_zone();
	pthread_mutex_unlock(&malloc_mutex);
}
