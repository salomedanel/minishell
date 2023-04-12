/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:24:26 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/12 15:40:02 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_malloc_size(int n)
{
	size_t	j;

	j = 0;
	if (n == -2147483648)
	{
		j = 11;
		return (j);
	}
	if (n == 0)
		j = 1;
	if (n < 0)
	{
		n *= -1;
		j++;
	}
	while (n >= 1)
	{
		n /= 10;
		j++;
	}
	return (j);
}

char	*ft_itoa(int n)
{
	unsigned int	numb;
	char			*res;
	size_t			i;

	i = ft_malloc_size(n);
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	if (n < 0)
	{
		*(res + 0) = '-';
		numb = n * -1;
	}
	else
		numb = n;
	*(res + i--) = '\0';
	if (numb == 0)
		*(res + 0) = '0';
	while (numb > 0)
	{
		*(res + i--) = '0' + (numb % 10);
		numb /= 10;
	}
	return (res);
}
