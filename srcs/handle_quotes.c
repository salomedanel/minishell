/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:35:37 by danelsalome       #+#    #+#             */
/*   Updated: 2023/05/25 15:22:19 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes_open(int dquotes, int squotes)
{
	if (dquotes == 1)
	{
		err_msg(ERR_MSG, 34);
		return (1);
	}
	if (squotes == 1)
	{
		err_msg(ERR_MSG, 39);
		return (1);
	}
	return (0);
}

void	replace_space(t_data *data, int *dq_open, int *sq_open, int i)
{
	if (data->clean_prompt[i] == '"' && *dq_open == 1)
		*dq_open = 0;
	if (data->clean_prompt[i] == '\'' && *sq_open == 1)
		*sq_open = 0;
	if ((*dq_open == 1 || *sq_open == 1) && data->clean_prompt[i] == 32)
		data->clean_prompt[i] = 31;
}

int	count_newlen(t_data *data, t_quotes *quotes)
{
	int	i;

	i = -1;
	while (quotes->arg[++i])
	{
		if (quotes->arg[i] == '"' && quotes->sq_open == 0
			&& quotes->dq_open == 0)
			data->count = open_quotes(quotes->arg[i], quotes, &i, &data->count);
		data->count = varenv_len(quotes, data, &i);
		if (quotes->arg[i] == '\'' && quotes->sq_open == 0
			&& quotes->dq_open == 0)
			data->count = open_quotes(quotes->arg[i], quotes, &i, &data->count);
		if (quotes->arg[i] == '"' && quotes->dq_open == 1)
			data->count = close_quotes(quotes->arg[i], quotes, &data->count);
		if (quotes->arg[i] == '\'' && quotes->sq_open == 1)
			data->count = close_quotes(quotes->arg[i], quotes, &data->count);
	}
	return (data->count);
}

void	trimquotes(t_data *data, t_quotes *quotes, int i, int j)
{
	int	count;
	int	stop;

	stop = 0;
	count = trimquotes_utils(quotes, &count);
	while (quotes->arg[i] && stop < ft_strlen(quotes->arg) - count)
	{
		trquotes_util1(quotes->arg[i], &quotes->dq_open, &quotes->sq_open, &i);
		trquotes_util2(quotes->arg[i], &quotes->dq_open, &quotes->sq_open, &i);
		if ((quotes->arg[i] == '"' && quotes->sq_open == 0)
			|| (quotes->arg[i] == '\'' && quotes->dq_open == 0))
		{
			if (quotes->arg[i] == '"' && quotes->dq_open == 0)
				quotes->dq_open = 1;
			else if (quotes->arg[i] == '\'' && quotes->sq_open == 0)
				quotes->sq_open = 1;
			continue ;
		}
		j = cpy_varenv(data, quotes, &i, &j);
		i++;
		stop++;
	}
	data->f_arg[quotes->index][j] = '\0';
	return ;
}

char	*handle_quotes(t_data *data, int i)
{
	int	dq_open;
	int	sq_open;

	dq_open = 0;
	sq_open = 0;
	while (data->clean_prompt[++i])
	{
		trquotes_util1(data->clean_prompt[i], &dq_open, &sq_open, &i);
		if (i >= ft_strlen(data->clean_prompt))
			break ;
		replace_space(data, &dq_open, &sq_open, i);
	}
	if (check_quotes_open(dq_open, sq_open) == 1)
		return (NULL);
	return (data->clean_prompt);
}
