/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:38:07 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/12 16:54:58 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) - 1;
	if (!c)
		return ((char *)(s + i + 1));
	while (i >= 0)
	{
		if (*(char *)(s + i) == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
