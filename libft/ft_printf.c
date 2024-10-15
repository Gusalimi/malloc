/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:52:28 by gsaile            #+#    #+#             */
/*   Updated: 2024/10/15 18:27:01 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	parse_arg(const char *format, va_list args, int *counter)
{
	char	c;

	c = *format;
	if (c == '%' || c == 0)
		*counter += ft_putchar_fd(c, 1);
	else if (c == 'c')
		*counter += ft_putchar_fd(va_arg(args, int), 1);
	else if (c == 's')
		*counter += ft_putstr_fd(va_arg(args, char *), 1);
	else if (c == 'd')
		*counter += ft_putnbr_fd(va_arg(args, int), 1);
	else if (c == 'i')
		*counter += ft_putnbr_fd(va_arg(args, int), 1);
	else if (c == 'u')
		*counter += ft_putunbr_fd(va_arg(args, unsigned int), 1);
	else if (c == 'z' && *(format + 1) && *(format + 1) == 'u')
		*counter += ft_putulnbr_fd(va_arg(args, unsigned long), 1);
	else if (c == 'x')
		*counter += ft_putnbr_base(va_arg(args, int), "0123456789abcdef");
	else if (c == 'X')
		*counter += ft_putnbr_base(va_arg(args, int), "0123456789ABCDEF");
	else if (c == 'p')
	{
		*counter += ft_putstr_fd("0x", 1);
		*counter += ft_putlnbr_base(va_arg(args, unsigned long long int),
				"0123456789abcdef");
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		counter;

	va_start(args, format);
	i = 0;
	counter = 0;
	while (format[i])
	{
		if (format[i] != '%')
			counter += ft_putchar_fd(format[i], 1);
		else
		{
			parse_arg(&format[++i], args, &counter);
			if (format[i] && format[i] == 'z' && format[i + 1]
					&& format[i + 1] == 'u')
				i++;
		}
		i++;
	}
	va_end(args);
	return (counter);
}
