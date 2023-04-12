/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:41:46 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/12 16:25:53 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (*(dest + i))
		i++;
	j = 0;
	while (*(src + j))
		j++;
	if (!size)
		return (j);
	k = 0;
	while (*(src + k) && i + k < size - 1)
	{
		*(dest + i + k) = *(src + k);
		k++;
	}
	*(dest + i + k) = '\0';
	if (i > size)
		return (j + size);
	return (i + j);
}
