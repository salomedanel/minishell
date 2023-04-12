/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:13:51 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/12 16:24:52 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_uintlen(unsigned int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_uitoa(unsigned int n)
{
	int		i;
	char	*numb;

	i = ft_uintlen(n);
	numb = malloc(sizeof(char) * (i + 1));
	if (!numb)
		return (NULL);
	*(numb + i) = '\0';
	while (i > 0)
	{
		*(numb + i - 1) = n % 10 + '0';
		n /= 10;
		i--;
	}
	return (numb);
}

int	ft_printuint(unsigned int n)
{
	int		i;
	char	*numb;

	i = 0;
	if (n == 0)
		i += write (1, "0", 1);
	else
	{
		numb = ft_uitoa(n);
		i += ft_printstr(numb);
		free (numb);
	}
	return (i);
}
