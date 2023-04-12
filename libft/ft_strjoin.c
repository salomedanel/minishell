/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:27:24 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/12 16:25:43 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = ft_strlen(s1);
	if (!s1)
		return (NULL);
	new = malloc(sizeof(char) * (j + ft_strlen(s2) + 1));
	j = 0;
	if (!new)
		return (NULL);
	while (*(char *)(s1 + i))
	{
		*(new + i) = *(s1 + i);
		i++;
	}
	while (*(char *)(s2 + j))
	{
		*(new + i + j) = *(s2 + j);
		j++;
	}
	*(new + i + j) = '\0';
	return (new);
}
