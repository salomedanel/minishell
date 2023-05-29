/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils02.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:51:47 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/29 20:29:17 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	is_specialchar(char c)
{
	if (c == '$' || c == '\'' || c == '"' || c == '\0' || c == '[' || c == ']'
		|| c == '{' || c == '}' || c == '%')
		return (1);
	return (0);
}

int	is_spechar(char c)
{
	if (c == '&')
		return (1);
	if (c >= 40 && c <= 42)
		return (1);
	return (0);
}

void	fill_farg(t_quotes *quotes, t_data *data, int *i, int *j)
{
	data->f_arg[quotes->index][*j] = quotes->arg[*i];
	*j = *j + 1;
	return ;
}

int	varenv_len_utils(t_quotes *quotes, int *i, int *count)
{
	if (quotes->arg[*i] != '$' || quotes->sq_open != 0)
		return (*count);
	if (quotes->arg[*i] == '$' && quotes->arg[*i - 1] == '?' && !quotes->arg[*i
			+ 1])
		return (2);
	if (quotes->arg[*i] == '$' && quotes->arg[*i + 1] == '?')
		return (*count + ft_strlen(ft_itoa(g_exit_code)) - 1);
	return (*count);
}

int	contains_dollar(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
