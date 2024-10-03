/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:24:19 by gsaile            #+#    #+#             */
/*   Updated: 2024/10/03 09:43:01 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include "../libft/libft.h"
#include "struct.h"

#define TINY_HEAP_ALLOC_SIZE (4 * getpagesize())
#define TINY_BLOCK_ALLOC_SIZE (TINY_HEAP_ALLOC_SIZE / 128)
#define SMALL_HEAP_ALLOC_SIZE (16 * getpagesize())
#define SMALL_BLOCK_ALLOC_SIZE (SMALL_HEAP_ALLOC_SIZE / 128)

typedef enum e_zone_types {
	TINY,
	SMALL,
	LARGE
} t_zone_types;

extern t_heap *g_zones[3];

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void show_alloc_mem();

#endif /* end of include guard: MALLOC_H */
