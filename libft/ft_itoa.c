/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:53:20 by gsaile            #+#    #+#             */
/*   Updated: 2022/11/04 16:08:52 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	unsigned int	nb;

	i = get_len(n);
	str = malloc((i + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		nb = -n;
		str[0] = '-';
	}
	else
		nb = n;
	str[i--] = 0;
	if (nb == 0)
		str[i] = '0';
	while (nb)
	{
		str[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}
