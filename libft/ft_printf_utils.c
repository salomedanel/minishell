/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:01:21 by tmichel-          #+#    #+#             */
/*   Updated: 2022/12/14 15:49:34 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(int c)
{
	write(1, &c, 1);
	return (1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (*(s + i))
	{
		write(1, &*(s + i), 1);
		i++;
	}
}

int	ft_printstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (*(s + i))
	{
		write(1, &*(s + i), 1);
		i++;
	}
	return (i);
}

int	ft_printnbr(int n)
{
	char	*numb;
	int		i;

	numb = ft_itoa(n);
	i = ft_printstr(numb);
	free (numb);
	return (i);
}

int	ft_percent(void)
{
	write(1, "%", 1);
	return (1);
}
