/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:49:26 by danelsalome       #+#    #+#             */
/*   Updated: 2023/05/04 14:56:33 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trimquotes_utils(char c, int *dq_open, int *sq_open, int *i)
{
	if (c == '"' && *dq_open == 0 && *sq_open == 0)
	{
		*dq_open = 1;
		*i = *i + 1;
	}
	if (c == '\'' && *dq_open == 0 && *sq_open == 0)
	{
		*sq_open = 1;
		*i = *i + 1;
	}
	return ;
}

void	ft_strcpy(char *dest, char *src, int start)
{
	int	i;

	i = 0;
	if (src == NULL)
		return ;
	while (src[start])
	{
		dest[i] = src[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return ;
}

int	contains_quotes(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '"' || arg[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
