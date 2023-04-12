/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:02:34 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/12 16:25:34 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int			i;
	const char	*dest;

	i = 0;
	dest = malloc((ft_strlen(src) + 1) * sizeof(*src));
	if (!dest)
		return (NULL);
	while (*(unsigned char *)(src + i))
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
	*(unsigned char *)(dest + i) = '\0';
	return ((char *)(dest));
}
