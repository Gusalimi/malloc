/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:02:05 by gsaile            #+#    #+#             */
/*   Updated: 2024/10/15 15:27:32 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"
#include <stdio.h>

// TODO:
// - Check if double free
// - Munmap if empty heap
// - Set to NULL in global if last_heap
// BUG: Segfault with malloc(INT_MAX+1) (Potentially due to large zone)

bool heap_is_empty(t_block *block) {
    while (block && block->prev)
        block = block->prev;
    while (block) {
        if (block->freed == FALSE)
            return (FALSE);
        block = block->next;
    }
    return (TRUE);
}

void free(void *ptr) {
    t_block *block_header;

	if (!ptr)
		return ;

    block_header = (t_block *)((char *)ptr - sizeof(t_block));
    if (block_header->freed == TRUE) {
    }
	block_header->freed = TRUE;
    if (heap_is_empty(block_header)) {
        t_heap *heap = (t_heap *)((char *)block_header - sizeof(t_heap));
        t_heap *prev = heap->prev;
        t_heap *next = heap->next;
        if (!prev && !next) {
            g_zones[heap->zone_type] = NULL;
        }
        munmap(heap, heap->size);
        if (prev)
             prev->next = next;
        if (next)
             next->prev = prev;
    }
}
