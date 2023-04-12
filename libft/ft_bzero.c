/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:42:26 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/12 15:38:38 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*t;

	i = 0;
	t = (char *) s;
	while (i < n)
	{
		t[i] = '\0';
		i++;
	}
}
/*
int	main()
{
	char s[15];
	size_t n = 10;
	size_t i;

	i = 0;
	ft_bzero(s, n);
	while (i < n)
	{
		printf("%c\n", s[i]);
		i++;
	}
	return (0);
}*/
