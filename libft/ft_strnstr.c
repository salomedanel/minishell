/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danelsalome <danelsalome@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:26:38 by sdanel            #+#    #+#             */
/*   Updated: 2023/03/30 10:45:12 by danelsalome      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
//#include <bsd/string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (big == 0)
		return (0);
	if (little[0] == '\0')
		return ((char *) big);
	while (big[i] != '\0' && i < len)
	{
		while ((i + j) < len && big[i + j] == little[j])
		{
			j++;
			if (!little[j])
				return ((char *) &big[i]);
		}
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	*big;
	char	*little;
	size_t	len;

	big = "hello salome";
	little = "fake";
	len = 0;
	printf("%s\n", ft_strnstr(((void*)0), little, len));
	printf("%s\n", strnstr(((void*)0), little, len));
	return (0);
}
*/
