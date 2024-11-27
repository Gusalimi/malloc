/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:02:21 by gsaile            #+#    #+#             */
/*   Updated: 2024/11/27 10:27:10 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

void *realloc(void *ptr, size_t size) {
	pthread_mutex_lock(&malloc_mutex);

	void	*new_ptr;

	if (!ptr) {
		pthread_mutex_unlock(&malloc_mutex);
		return (malloc(size));
	} else if (size == 0) {
		pthread_mutex_unlock(&malloc_mutex);
		free(ptr);
		return (NULL);
	}

	t_block	*block = ptr - sizeof(t_block);
	if (size <= block->size) {
		shrink_block(block, size);
	} else if (block->next->size >= size - block->size) {
		enlarge_block(block, size);
	} else {
		pthread_mutex_unlock(&malloc_mutex);
		new_ptr = malloc(size);
		if (new_ptr) {
			ft_memcpy(new_ptr, ptr, block->size);
		}
		free(ptr);
		return (new_ptr);
	}

	pthread_mutex_unlock(&malloc_mutex);
	return ptr;
}
