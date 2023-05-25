/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:49:26 by danelsalome       #+#    #+#             */
/*   Updated: 2023/05/25 10:29:34 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	trimquotes_utils1(char c, int *dq_open, int *sq_open, int *i)
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

void	trimquotes_utils2(char c, int *dq_open, int *sq_open, int *i)
{
	if (c == '"' && *dq_open == 1)
	{
		*dq_open = 0;
		*i = *i + 1;
	}
	if (c == '\'' && *sq_open == 1)
	{
		*sq_open = 0;
		*i = *i + 1;
	}
	return ;
}

int	cpy_varenv(t_data *data, t_quotes *quotes, int *i, int *j)
{
	char	*var;
	int		k;

	k = 0;
	var = replace_dollar(quotes, i, data);
	if (var == NULL && quotes->arg[*i] != '$' && quotes->arg[*i] != '"')
	{
		data->f_arg[quotes->index][*j] = quotes->arg[*i];
		*j = *j + 1;
	}
	else if (var != NULL)
	{
		while (var[k] != '\0')
		{
			data->f_arg[quotes->index][*j] = var[k];
			*j = *j + 1;
			k++;
		}
		k = 0;
	}
	if (quotes->arg[*i] == '$')
		*i = *i - 1;
	return (*j);
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

void	norm_count_mc(int *count, int *i)
{
	*count = *count + 1;
	*i = *i + 1;
	return ;
}