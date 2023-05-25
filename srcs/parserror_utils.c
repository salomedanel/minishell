/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserror_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:39:25 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/24 18:10:10 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	metachar_type(char c, int *count)
{
	if (c == '>')
	{
		*count = *count + 1;
		return (1);
	}
	if (c == '<')
	{
		*count = *count + 1;
		return (2);
	}
	if (c == '|')
	{
		*count = *count + 1;
		return (3);
	}
	return (0);
}

int	str_contains_mc(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (metachar_type(str[i], &count) > 0)
			return (metachar_type(str[i], &count));
		i++;
	}
	return (0);
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
