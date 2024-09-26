/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:52:21 by gsaile            #+#    #+#             */
/*   Updated: 2022/11/05 11:24:01 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	if (count == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	ret = malloc(count * size);
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, count * size);
	return (ret);
}
