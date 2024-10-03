/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:03:58 by gsaile            #+#    #+#             */
/*   Updated: 2024/10/03 15:13:30 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_heap {
	struct s_heap	*prev;
	struct s_heap	*next;
}	t_heap;

typedef struct s_block {
	struct s_block	*prev;
	struct s_block	*next;
	size_t			size;
	bool			freed;
}	t_block;

#endif /* end of include guard: STRUCTS_H */
