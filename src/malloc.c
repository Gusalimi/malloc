/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:39:02 by gsaile            #+#    #+#             */
/*   Updated: 2024/10/03 14:05:46 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	TODO:
//	Check if remaining size sufficient to create a new block (with header)
//		=> Otherwise negative sizes that will overflow
//	Use getrlimit because of error
//		a.out(60820,0x1f38ef240) malloc: nano zone abandoned due to inability to reserve vm space.
//	Check why the new address is 0xXX000 away from the first one (instead of right after)

#include "../include/malloc.h"
#include <stdio.h>

t_heap	*g_zones[3] = { 0 };

void	get_infos(size_t size, size_t *alloc_size, int *zone_type) {
	if (!alloc_size || !zone_type)
		return ;
	if (size <= (size_t)TINY_BLOCK_ALLOC_SIZE) {
		*zone_type = TINY;
		*alloc_size = TINY_HEAP_ALLOC_SIZE;
	} else if (size <= (size_t)SMALL_BLOCK_ALLOC_SIZE) {
		*zone_type = SMALL;
		*alloc_size = SMALL_HEAP_ALLOC_SIZE;
	} else {
		*zone_type = LARGE;
		*alloc_size = size;
	}
}

t_heap	*get_last_zone(t_heap *zone) {
	t_heap	*last;

	if (!zone)
		return (NULL);
	last = zone;
	while (last->next)
		last = last->next;
	return (last);
}

void	update_block(t_block *block, size_t size) {
	t_block *old_next;

	if (block->size == size || block->size - size - sizeof(t_block) <= 0)
		return ;
	old_next = block->next;
	block->size = size;
	block->freed = FALSE;
	block->next = (t_block *)(block + sizeof(t_block) + size);
	// printf("%p\n", block->next);
	block->next->size = block->size - size - sizeof(t_block);
	block->next->freed = TRUE;
	block->next->next = old_next;
}

t_block	*find_block(t_heap *zone, size_t size) {
	t_block	*block;

	while (zone) {
		block = (t_block *)(zone + sizeof(t_heap));
		while (block) {
			// printf("find_block : %p %i %zu\n", block, block->freed, block->size);
			if (block->freed && block->size >= size) {
				update_block(block, size);
				return block;
			}
			block = block->next;
		}
		zone = zone->next;
	}
	return (NULL);
}

t_heap	*new_heap(size_t alloc_size, size_t block_size) {
	t_heap	*zone;
	t_block	*block;

	zone = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (zone == MAP_FAILED) {
		return (NULL);
	}

	zone->prev = NULL;
	zone->next = NULL;

	block = (t_block *)(zone + sizeof(t_heap));
	block->freed = FALSE;
	block->size = block_size;
	block->prev = NULL;
	// Next block is the whole heap without the heap and block metadatas and the current block
	block->next = block + sizeof(t_block) + block_size;
	block->next->freed = TRUE;
	block->next->size = alloc_size - sizeof(t_heap) - block_size - (sizeof(t_block) * 2);
	block->next->next = NULL;

	return zone;
}

void	*non_empty_zone(int zone_type, size_t size, size_t alloc_size) {
	t_heap	*zone;
	t_block	*block;
	// printf("non_empty_zone\n");

	zone = g_zones[zone_type];

	block = find_block(zone, size);
	if (block)
		return block + sizeof(t_block);

	zone = get_last_zone(zone);
	zone->next = new_heap(alloc_size, size);

	return (NULL);
}

void	*empty_zone(int zone_type, size_t size, size_t alloc_size) {
	// printf("empty_zone\n");
	t_block	*block;

	g_zones[zone_type] = new_heap(alloc_size, size);

	block = (t_block *)(g_zones[zone_type] + sizeof(t_heap));

	return block + sizeof(t_block);
}

void	*new_large(size_t size) {
	t_heap	*ptr;
	t_heap	*last;

	size_t alloc_size = (size + sizeof(t_heap) + 15) & ~15;
	ptr = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED) {
		return (NULL);
	}

	ptr->prev = NULL;
	ptr->next = NULL;
	
	last = get_last_zone(g_zones[LARGE]);
	if (last) {
		ptr->prev = last;
		last->next = ptr;;
	}
	return (ptr);
}


void *malloc(size_t size) {
	size_t	alloc_size = 0;
	int		zone_type = 0;
	void	*ptr;

	// ft_printf("============ Hello malloc ============\n");

	if (size <= 0)
		return NULL;

	if (size <= (size_t)SMALL_BLOCK_ALLOC_SIZE)
		size = (size + 15) & ~15; // Alignment

	get_infos(size, &alloc_size, &zone_type);

	if (zone_type == LARGE)
		return new_large(size);

	if (g_zones[zone_type])
		ptr = non_empty_zone(zone_type, size, alloc_size);
	else
		ptr = empty_zone(zone_type, size, alloc_size);

	// printf("%p\n", ptr);

	return ptr;
}


