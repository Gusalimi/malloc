/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:02:05 by gsaile            #+#    #+#             */
/*   Updated: 2024/10/15 17:19:42 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"
#include <stdio.h>

// TODO:
// - Check if double free

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

bool is_large(void *ptr) {
    t_heap *head = g_zones[LARGE];
    while (head) {
        if ((char *)head + sizeof(t_heap) == ptr)
            return TRUE;
        head = head->next;
    }
    return FALSE;
}

void free_large(void *ptr) {
    t_heap  *header = (t_heap *)((char *)ptr - sizeof(t_heap));
    t_heap  *prev = header->prev;
    t_heap  *next = header->next;

    munmap(header, header->size);
    if (!prev && !next)
        g_zones[LARGE] = NULL;
    if (prev)
        prev->next = next;
    if (next)
        next->prev = prev;

}

void free(void *ptr) {
    t_block *block_header;

	if (!ptr)
		return ;

    if (is_large(ptr)) {
        free_large(ptr);
        return ;
    }

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
