/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:17:46 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/12 16:24:48 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ptrlen(unsigned long long ptr)
{
	int	i;

	i = 0;
	while (ptr != 0)
	{
		i++;
		ptr /= 16;
	}
	return (i);
}

void	ft_putptr(unsigned long long ptr)
{
	if (ptr >= 16)
	{
		ft_putptr(ptr / 16);
		ft_putptr(ptr % 16);
	}
	else
	{
		if (ptr <= 9)
			ft_putchar_fd((ptr + '0'), 1);
		else
			ft_putchar_fd((ptr - 10 + 'a'), 1);
	}
}

int	ft_printptr(unsigned long long ptr)
{
	int	i;

	i = 0;
	if (ptr == 0)
	{
		i += write(1, "(nil)", 5);
		return (5);
	}
	else
	{
		i += ft_printstr("0x");
		ft_putptr(ptr);
		i += ft_ptrlen(ptr);
	}
	return (i);
}
