/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:39:02 by gsaile            #+#    #+#             */
/*   Updated: 2024/11/04 11:12:37 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	TODO:
//	Use getrlimit because of error
//		a.out(60820,0x1f38ef240) malloc: nano zone abandoned due to inability to reserve vm space.
//	Check why I return NULL on non_empty_zone() end

#include "../include/malloc.h"

t_heap				*g_zones[3] = { 0 };
pthread_mutex_t	malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

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
		*alloc_size = size + sizeof(t_heap);
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

t_block	*find_block(t_heap *zone, size_t size) {
	t_block	*block;

	while (zone) {
		block = (t_block *)((char *)zone + sizeof(t_heap));
		while (block) {
			if (block->freed && block->size >= size) {
				shrink_block(block, size);
				return block;
			}
			block = block->next;
		}
		zone = zone->next;
	}
	return (NULL);
}

t_heap	*new_heap(size_t alloc_size, size_t block_size, t_zone_types zone_type) {
	t_heap	*zone;
	t_block	*block;

	zone = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (zone == MAP_FAILED) {
		return (NULL);
	}

	zone->prev = NULL;
	zone->next = NULL;
    zone->size = alloc_size;
	zone->zone_type = zone_type;

	block = (t_block *)((char *)zone + sizeof(t_heap));
	block->freed = FALSE;
	block->size = block_size;
	block->prev = NULL;
	block->next = (t_block *)((char *)block + sizeof(t_block) + block_size);
	block->next->freed = TRUE;
	block->next->size = alloc_size - sizeof(t_heap) - block_size - (sizeof(t_block) * 2);
	block->next->prev = block;
	block->next->next = NULL;


	return zone;
}

void	*non_empty_zone(t_zone_types zone_type, size_t size, size_t alloc_size) {
	t_heap	*zone;
	t_block	*block;

	zone = g_zones[zone_type];

	block = find_block(zone, size);
	if (block)
		return (char *)block + sizeof(t_block);

	zone = get_last_zone(zone);
	zone->next = new_heap(alloc_size, size, zone_type);
	if (!zone->next)
		return (NULL);
	zone->next->prev = zone;

	return (zone->next + sizeof(t_heap) + sizeof(t_block));
}

void	*empty_zone(t_zone_types zone_type, size_t size, size_t alloc_size) {
	t_block	*block;

	g_zones[zone_type] = new_heap(alloc_size, size, zone_type);
	if (!g_zones[zone_type])
		return (NULL);

	block = (t_block *)((char *)g_zones[zone_type] + sizeof(t_heap));

	return (char *)block + sizeof(t_block);
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
	ptr->size = alloc_size;
	ptr->zone_type = LARGE;
	
	last = get_last_zone(g_zones[LARGE]);
	if (last) {
		ptr->prev = last;
		last->next = ptr;
	} else {
		g_zones[LARGE] = ptr;
	}

	return ((char *)ptr + sizeof(t_heap));
}


void *malloc(size_t size) {
	size_t	alloc_size = 0;
	int		zone_type = 0;
	void	*ptr;

	if (size <= 0)
		return NULL;

	pthread_mutex_lock(&malloc_mutex);
	if (size <= (size_t)SMALL_BLOCK_ALLOC_SIZE)
		size = (size + 15) & ~15; // Alignment

	get_infos(size, &alloc_size, &zone_type);

	if (zone_type == LARGE) {
		size = (size + 15) & ~15; // Alignment
		pthread_mutex_unlock(&malloc_mutex);
		return new_large(size);
	}

	if (g_zones[zone_type])
		ptr = non_empty_zone(zone_type, size, alloc_size);
	else
		ptr = empty_zone(zone_type, size, alloc_size);

	pthread_mutex_unlock(&malloc_mutex);
	return ptr;
}


