/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:02:21 by gsaile            #+#    #+#             */
/*   Updated: 2024/10/16 14:19:12 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

void *realloc(void *ptr, size_t size) {
	pthread_mutex_lock(&malloc_mutex);
	(void)size;
	pthread_mutex_unlock(&malloc_mutex);
	return ptr;
}
