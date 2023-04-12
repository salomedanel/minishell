/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:48:44 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/12 16:26:57 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
	{
		new = malloc(sizeof(char));
		*(new + 0) = '\0';
		return (new);
	}
	if (len >= (unsigned int)ft_strlen(s))
		len = ft_strlen(s) - start;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (*(s + i) && i < len)
	{
		*(new + i) = *(char *)(s + start + i);
		i++;
	}
	*(new + i) = '\0';
	return (new);
}
