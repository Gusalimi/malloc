/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:51:59 by gsaile            #+#    #+#             */
/*   Updated: 2022/11/05 10:41:21 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return ((c == '\t')
		|| (c == '\n')
		|| (c == '\v')
		|| (c == '\f')
		|| (c == '\r')
		|| (c == ' '));
}

int	ft_atoi(const char *str)
{
	unsigned int		result;
	int					sign;
	char				*tmp;

	result = 0;
	sign = 1;
	tmp = (char *)str;
	while (ft_isspace(*tmp))
		tmp++;
	if (*tmp == '+')
		tmp++;
	else if (*tmp == '-')
	{
		sign = -1;
		tmp++;
	}
	while (ft_isdigit(*tmp))
	{
		result *= 10;
		result += *tmp - '0';
		tmp++;
	}
	return (result * sign);
}
