/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:11:22 by gsaile            #+#    #+#             */
/*   Updated: 2022/11/26 16:17:38 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(unsigned int nbr, char *base)
{
	unsigned int	value;
	int				i;

	i = 0;
	value = ft_strlen(base);
	if (!base)
		return (0);
	if (nbr >= value)
	{
		i += ft_putnbr_base(nbr / value, base);
		ft_putnbr_base(nbr % value, base);
	}
	else
		ft_putchar_fd(base[nbr], 1);
	i++;
	return (i);
}

int	ft_putlnbr_base(unsigned long long int nbr, char *base)
{
	unsigned int	value;
	int				i;

	i = 0;
	value = ft_strlen(base);
	if (!base)
		return (0);
	if (nbr >= value)
	{
		i += ft_putlnbr_base(nbr / value, base);
		ft_putlnbr_base(nbr % value, base);
	}
	else
		ft_putchar_fd(base[nbr], 1);
	i++;
	return (i);
}
