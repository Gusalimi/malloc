/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:05:47 by gsaile            #+#    #+#             */
/*   Updated: 2024/10/18 14:02:13 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

void	enlarge_block(t_block *block, size_t size) {
	t_block	*old_next;

	if (block->size == size || block->size + block->next->size <= size + sizeof(t_block)) {
		block->size = size;
		return ;
	}
	old_next = block->next;
	block->next = (t_block *)((char *)block + size);
	block->next->next = old_next->next;
	block->next->freed = old_next->freed;
	block->next->prev = block;
	block->next->size = old_next->size + (size - block->size);
	block->size = size;
}

void	shrink_block(t_block *block, size_t size) {
	t_block *old_next;

	if (block->size == size || ((long)block->size - (long)size - (long)sizeof(t_block)) <= 0)
	{
		block->freed = FALSE;
		return ;
	}
	old_next = block->next;
	block->freed = FALSE;
	block->next = (t_block *)((char *)block + sizeof(t_block) + size);
	block->next->size = (long)block->size - (long)size - (long)sizeof(t_block);
	block->next->freed = TRUE;
    block->next->prev = block;
	block->next->next = old_next;
	block->size = size;
}