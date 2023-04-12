/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:34:50 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/12 16:24:41 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hexlen(unsigned int hex)
{
	int	i;

	i = 0;
	while (hex != 0)
	{
		i++;
		hex /= 16;
	}
	return (i);
}

void	ft_puthex(unsigned int hex)
{
	if (hex >= 16)
	{
		ft_puthex(hex / 16);
		ft_puthex(hex % 16);
	}
	else
	{
		if (hex <= 9)
			ft_putchar_fd((hex + '0'), 1);
		else
			ft_putchar_fd((hex - 10 + 'a'), 1);
	}
}

int	ft_printhex(unsigned int hex)
{
	int	i;

	i = 0;
	if (hex == 0)
		i += write(1, "0", 1);
	else
	{
		ft_puthex(hex);
		i += ft_hexlen(hex);
	}
	return (i);
}

void	ft_puthexmaj(unsigned int hexmaj)
{
	if (hexmaj >= 16)
	{
		ft_puthexmaj(hexmaj / 16);
		ft_puthexmaj(hexmaj % 16);
	}
	else
	{
		if (hexmaj <= 9)
			ft_putchar_fd((hexmaj + '0'), 1);
		else
			ft_putchar_fd((hexmaj - 10 + 'A'), 1);
	}
}

int	ft_printhexmaj(unsigned int hexmaj)
{
	int	i;

	i = 0;
	if (hexmaj == 0)
		i += write(1, "0", 1);
	else
	{
		ft_puthexmaj(hexmaj);
		i += ft_hexlen(hexmaj);
	}
	return (i);
}
