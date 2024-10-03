/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:59:34 by gsaile            #+#    #+#             */
/*   Updated: 2024/10/03 11:00:24 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

void	print_zone(t_heap *zone, char *zone_name) {
	t_heap	*current_heap;
	t_block	*current_block;
	void	*block_data;

	if (!zone) {
		ft_printf("%s : None\n", zone_name);
		return ;
	}
	ft_printf("%s : %p %d\n", zone_name, zone, zone->block_count);
	current_heap = zone;
	while (current_heap) {
		current_block = (t_block *)(current_heap+ sizeof(t_heap));
		while (current_block && current_block->freed == TRUE) {
			block_data = current_block + sizeof(t_block);
			ft_printf("%p - %p : %zu bytes\n", block_data, block_data + current_block->size, current_block->size);
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
