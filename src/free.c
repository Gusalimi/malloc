/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:02:05 by gsaile            #+#    #+#             */
/*   Updated: 2024/11/30 12:11:58 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

void	defragment(t_block *block) {
	t_block	*first;
	t_block	*last;
	t_block	*end;

	first = block;
	last = block;
	while (first->prev && first->prev->freed) {
		first = first->prev;
	}
	while (last->next && last->next->freed) {
		last = last->next;
	}

	end = last->next;
	while (first->next && first->next != end) {
		merge_blocks(first, first->size + first->next->size);
	}
}

bool	is_large(void *ptr) {
	t_heap	*head = g_zones[LARGE];

	while (head) {
		if ((char *)head + sizeof(t_heap) == ptr)
			return TRUE;
		head = head->next;
	}
	return FALSE;
}

void	free_large(void *ptr) {
	t_heap	*header = (t_heap *)((char *)ptr - sizeof(t_heap));
	t_heap	*prev = header->prev;
	t_heap	*next = header->next;

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

void	free(void *ptr) {
	t_block	*block_header;

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
	defragment(block_header);
	pthread_mutex_unlock(&malloc_mutex);
}
