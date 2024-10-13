/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:59:34 by gsaile            #+#    #+#             */
/*   Updated: 2024/10/13 14:33:26 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"
#include <stdio.h>

// TODO:
// Implement %zu in ft_printf

void	print_zone(t_heap *zone, char *zone_name) {
	t_heap	*current_heap;
	t_block	*current_block;
	char	*block_data;

	if (!zone) {
		ft_printf("%s : None\n", zone_name);
		return ;
	}
	ft_printf("%s :\n", zone_name);
	current_heap = zone;
	while (current_heap) {
		current_block = (t_block *)((char *)current_heap + sizeof(t_heap));
		while (current_block) {
			if (!current_block->freed && current_block->size > 0) {
				block_data = (char *)current_block + sizeof(t_block);
				printf("%p - %p : %zu bytes\n", block_data, block_data + current_block->size, current_block->size);
			}
			current_block = current_block->next;
		}
		current_heap = current_heap->next;
	}
}

void show_alloc_mem() {
	print_zone(g_zones[TINY], "TINY");
	print_zone(g_zones[SMALL], "SMALL");
	print_zone(g_zones[LARGE], "LARGE");
}
