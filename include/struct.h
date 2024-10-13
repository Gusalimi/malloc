/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:03:58 by gsaile            #+#    #+#             */
/*   Updated: 2024/10/13 14:30:43 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum e_zone_types {
	TINY,
	SMALL,
	LARGE
} t_zone_types;

typedef struct s_heap {
	struct s_heap	*prev;
	struct s_heap	*next;
    size_t          size;
	t_zone_types	zone_type;
}	t_heap;

typedef struct s_block {
	struct s_block	*prev;
	struct s_block	*next;
	size_t			size;
	bool			freed;
}	t_block;

#endif /* end of include guard: STRUCTS_H */
