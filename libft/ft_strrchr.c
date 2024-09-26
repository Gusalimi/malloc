/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:58:48 by gsaile            #+#    #+#             */
/*   Updated: 2022/11/04 15:58:49 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	char	*last_occ;

	tmp = (char *)s;
	last_occ = NULL;
	if ((char)c == 0)
		return (tmp + ft_strlen(s));
	while (*tmp)
	{
		if (*tmp == (char)c)
			last_occ = tmp;
		tmp++;
	}
	return (last_occ);
}
