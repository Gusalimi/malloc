/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:02:05 by gsaile            #+#    #+#             */
/*   Updated: 2024/10/16 14:18:33 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

// TODO:

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

    if (!prev && !next)
        g_zones[LARGE] = NULL;
    else if (!prev)
        g_zones[LARGE] = next;
    if (prev)
        prev->next = next;
    if (next)
        next->prev = prev;
    munmap(header, header->size);

}

void free(void *ptr) {
    t_block *block_header;

	if (!ptr)
		return ;

	pthread_mutex_lock(&malloc_mutex);

    if (is_large(ptr)) {
        free_large(ptr);
        pthread_mutex_unlock(&malloc_mutex);
        return ;
    }

    block_header = (t_block *)((char *)ptr - sizeof(t_block));
    if (block_header->freed == TRUE) {
        ft_putstr_fd("Warning : Double free\n", 2);
    }
	block_header->freed = TRUE;
    if (heap_is_empty(block_header)) {
        while (block_header->prev)
            block_header = block_header->prev;
        t_heap *heap = (t_heap *)((char *)block_header - sizeof(t_heap));
        t_heap *prev = heap->prev;
        t_heap *next = heap->next;
        if (!prev && !next)
            g_zones[heap->zone_type] = NULL;
        munmap(heap, heap->size);
        if (prev)
             prev->next = next;
        if (next)
             next->prev = prev;
    }
	pthread_mutex_unlock(&malloc_mutex);
}
