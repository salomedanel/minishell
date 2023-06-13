/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:42:43 by tmichel-          #+#    #+#             */
/*   Updated: 2023/06/13 10:03:58 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strnstr(const char *big, const char *little, size_t len)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	k;

// 	if (!big)
// 		return (NULL);
// 	if (*(little) == 0)
// 		return ((char *)big);
// 	i = ft_strlen((char *)little);
// 	if (i > len)
// 		return (NULL);
// 	j = 0;
// 	k = 0;
// 	while (*(big + j) && j < len)
// 	{
// 		while ((j + k) < len && *(big + j + k) == *(little + k))
// 		{
// 			k++;
// 			if (!*(little + k))
// 				return (&*(char *)(big + j));
// 		}
// 		j++;
// 	}
// 	return (NULL);	
// }

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	c;
	size_t	n_len;
	char	*hay;

	i = 0;
	hay = (char *)haystack;
	n_len = ft_strlen(needle);
	if (n_len == 0 || haystack == needle)
		return (hay);
	while (hay[i] != '\0' && i < len)
	{
		c = 0;
		while (hay[i + c] != '\0' && needle[c] != '\0'
				&& hay[i + c] == needle[c] && i + c < len)
			c++;
		if (c == n_len)
			return (hay + i);
		i++;
	}
	return (0);
}