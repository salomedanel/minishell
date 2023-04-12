/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:54:25 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/12 16:24:18 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format(va_list args, const char p)
{
	int	i;

	i = 0;
	if (p == 'c')
		i += ft_printchar(va_arg(args, int));
	else if (p == 's')
		i += ft_printstr(va_arg(args, char *));
	else if (p == 'p')
		i += ft_printptr(va_arg(args, unsigned long long));
	else if (p == 'd')
		i += ft_printnbr(va_arg(args, int));
	else if (p == 'i')
		i += ft_printnbr(va_arg(args, int));
	else if (p == 'u')
		i += ft_printuint(va_arg(args, unsigned int));
	else if (p == 'x')
		i += ft_printhex(va_arg(args, unsigned int));
	else if (p == 'X')
		i += ft_printhexmaj(va_arg(args, unsigned int));
	else if (p == '%')
		i += ft_percent();
	return (i);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		j;
	va_list	args;

	i = 0;
	j = 0;
	va_start(args, s);
	while (*(s + j))
	{
		if (*(s + j) == '%')
		{
			i += ft_format(args, *(s + j + 1));
			j++;
		}
		else
			i += ft_printchar(*(s + j));
		j++;
	}
	va_end(args);
	return (i);
}
