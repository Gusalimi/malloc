/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:56:34 by gsaile            #+#    #+#             */
/*   Updated: 2024/10/15 18:23:12 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (fd < 0)
		return (0);
	if (n < 0)
	{
		nb = -n;
		ft_putchar_fd('-', fd);
	}
	else
		nb = n;
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	ft_putchar_fd((nb % 10) + '0', fd);
	return (ft_get_len(n));
}

int	ft_putunbr_fd(unsigned int n, int fd)
{
	if (fd < 0)
		return (0);
	if (n > 9)
		ft_putunbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
	return (ft_get_ulen(n));
}

int	ft_putulnbr_fd(unsigned long n, int fd)
{
	if (fd < 0)
		return (0);
	if (n > 9)
		ft_putulnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
	return (ft_get_ullen(n));
}
