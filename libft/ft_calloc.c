/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:10:48 by tmichel-          #+#    #+#             */
/*   Updated: 2022/11/23 11:36:51 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;	

	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	else
	{
		p = (void *) malloc(nmemb * size);
		if (!p)
			return (NULL);
		ft_bzero((unsigned char *)p, nmemb * size);
		return (p);
	}
}
/*
int	main()
{
	size_t	nmemb;
	char	*str;
	size_t	i;

	nmemb = 10;
	i = 0;
	str = ft_calloc(nmemb, sizeof(char));
	while (i < nmemb)
	{
		printf("str[%ld] = %d\n", i, str[i]);
		i++;
	}
}*/
