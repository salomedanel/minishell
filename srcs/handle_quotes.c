/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:35:37 by danelsalome       #+#    #+#             */
/*   Updated: 2023/05/31 12:32:54 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes_open(t_quotes *quotes, t_data *data)
{
	if (quotes->dq_open == 1)
	{
		err_msg_char(ERR_MSG, 34, data);
		return (1);
	}
	if (quotes->sq_open == 1)
	{
		err_msg_char(ERR_MSG, 39, data);
		return (1);
	}
	return (0);
}

void	replace_space(t_data *data, t_quotes *quotes, int i)
{
	if (data->clean_prompt[i] == '"' && quotes->dq_open == 1)
		quotes->dq_open = 0;
	if (data->clean_prompt[i] == '\'' && quotes->sq_open == 1)
		quotes->sq_open = 0;
	if ((quotes->dq_open == 1 || quotes->sq_open == 1)
		&& data->clean_prompt[i] == 32)
		data->clean_prompt[i] = 31;
}

int	count_newlen(t_data *data, t_quotes *quotes)
{
	int	i;

	i = -1;
	while (quotes->arg && i <= ft_strlen(quotes->arg) - 1 && quotes->arg[++i])
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
	while (quotes->arg && i < ft_strlen(quotes->arg) && quotes->arg[i]
		&& stop < ft_strlen(quotes->arg) - count)
	{
		trquotes_util1(quotes->arg[i], quotes, &i);
		trquotes_util2(quotes->arg[i], quotes, &i);
		if ((quotes->arg[i] == '"' && quotes->sq_open == 0)
			|| (quotes->arg[i] == '\'' && quotes->dq_open == 0))
		{
			i = norm_trimquotes(quotes, &i);
			continue ;
		}
		j = cpy_varenv(data, quotes, &i, &j);
		i++;
		stop++;
	}
	data->f_arg[quotes->index][j] = '\0';
	return ;
}

char	*handle_quotes(t_data *data, int i, t_quotes *quotes)
{
	while (data->clean_prompt && data->clean_prompt[++i])
	{
		trquotes_util1(data->clean_prompt[i], quotes, &i);
		if (i >= ft_strlen(data->clean_prompt))
			break ;
		if (is_spechar(data->clean_prompt[i]) > 0 && quotes->dq_open == 0
			&& quotes->sq_open == 0)
		{
			err_msg_char(ERR_MSG, data->clean_prompt[i], data);
			free(data->clean_prompt);
			return (NULL);
		}
		replace_space(data, quotes, i);
	}
	if (check_quotes_open(quotes, data) == 1)
		return (NULL);
	return (data->clean_prompt);
}
