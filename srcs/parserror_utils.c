/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserror_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:39:25 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/26 13:18:51 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	metachar_type(char c)
{
	if (c == '>')
		return (1);
	if (c == '<')
		return (2);
	if (c == '|')
		return (3);
	if (c == '&')
		return (4);
	if (c >= 40 && c <= 44)
		return (5);
	return (0);
}

int	count_metac(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_metachar(str[i]) > 0)
			count++;
		i++;
	}
	return (count);
}

int	str_contains_mc(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (metachar_type(str[i]) > 0)
			return (metachar_type(str[i]));
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
