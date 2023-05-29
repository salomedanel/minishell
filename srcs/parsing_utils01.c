/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:49:26 by danelsalome       #+#    #+#             */
/*   Updated: 2023/05/29 17:47:50 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	trquotes_util1(char c, t_quotes *quotes, int *i)
{
	if (c == '"' && quotes->dq_open == 0 && quotes->sq_open == 0)
	{
		quotes->dq_open = 1;
		*i = *i + 1;
	}
	if (c == '\'' && quotes->dq_open == 0 && quotes->sq_open == 0)
	{
		quotes->sq_open = 1;
		*i = *i + 1;
	}
	return ;
}

void	trquotes_util2(char c, t_quotes *quotes, int *i)
{
	if (c == '"' && quotes->dq_open == 1)
	{
		quotes->dq_open = 0;
		if (*i == ft_strlen(quotes->arg) - 1)
			return ;
		*i = *i + 1;
	}
	if (c == '\'' && quotes->sq_open == 1)
	{
		quotes->sq_open = 0;
		if (*i == ft_strlen(quotes->arg) - 1)
			return ;
		*i = *i + 1;
	}
	return ;
}

int	cpy_varenv(t_data *data, t_quotes *quotes, int *i, int *j)
{
	char	*var;
	int		k;

	k = -1;
	if (special_cases_doll00(quotes, data, i, j) == 0)
		return (*j);
	var = replace_dollar(quotes, i, data);
	if ((var == NULL && quotes->arg[*i] != '$' && quotes->arg[*i] != '"')
		|| (quotes->arg[*i] == '"' && quotes->sq_open == 1))
		fill_farg(quotes, data, i, j);
	else if (var != NULL)
	{
		while (var[++k] != '\0')
		{
			data->f_arg[quotes->index][*j] = var[k];
			*j = *j + 1;
		}
		k = -1;
	}
	if (special_cases_doll01(quotes, data, i, j) == 0)
		return (*j);
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
