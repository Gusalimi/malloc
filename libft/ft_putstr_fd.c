/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:56:41 by gsaile            #+#    #+#             */
/*   Updated: 2022/11/26 16:15:49 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0 || s == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	write(fd, s, ft_strlen(s));
	return ((int)ft_strlen(s));
}
