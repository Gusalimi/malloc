/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:58:13 by gsaile            #+#    #+#             */
/*   Updated: 2022/11/28 11:19:42 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		min;

	if (haystack == NULL && len == 0)
		return (NULL);
	i = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)(haystack));
	while (haystack[i] && i <= len)
	{
		if (haystack[i] == needle[0])
		{
			if (len - i < ft_strlen(needle))
				return (NULL);
			if (len - i < ft_strlen(needle))
				min = len - i;
			else
				min = ft_strlen(needle);
			if (ft_strncmp(haystack + i, needle, min) == 0)
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
