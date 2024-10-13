/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:02:05 by gsaile            #+#    #+#             */
/*   Updated: 2024/10/13 14:09:37 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"
#include <stdio.h>

// TODO:
// - Check if double free
// - Munmap if empty heap
// - Set to NULL in global if last_heap

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
//    printf("ptr = %p | block_header = %p | block_header->prev = %p\n", ptr, block_header, block_header->prev);
    if (block_header->freed == TRUE) {
 //       ft_printf("Warning: double free detected (%p)\n", ptr);
    }
	block_header->freed = TRUE;
    if (heap_is_empty(block_header)) {
        t_heap *heap = (t_heap *)((char *)block_header - sizeof(t_heap *));
        // t_heap *prev = heap->prev;
        // t_heap *next = heap->next;
        munmap(heap, heap->size);
        // if (prev)
        //     prev->next = next;
        // if (next)
        //     next->prev = prev;
    }
}
