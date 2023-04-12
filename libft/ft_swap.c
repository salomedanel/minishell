/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:08:07 by tmichel-          #+#    #+#             */
/*   Updated: 2022/12/26 19:59:36 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *a, void *b, int size)
{
	int		i;
	char	atemp;
	char	btemp;

	i = -1;
	while (++i < size)
	{
		atemp = ((char *)a)[i];
		btemp = ((char *)b)[i];
		((char *)a)[i] = btemp;
		((char *)b)[i] = atemp;
	}
}
