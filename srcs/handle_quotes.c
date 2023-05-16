/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:35:37 by danelsalome       #+#    #+#             */
/*   Updated: 2023/05/16 18:08:23 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes_open(t_data *data, int dquotes, int squotes)
{
	if (dquotes == 1)
	{
		quote_err(data, QUOTE_ERR, 34);
		return (1);
	}
	if (squotes == 1)
	{
		quote_err(data, QUOTE_ERR, 39);
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
	printf("%d\n", data->count);
	return (data->count);
}

void	trimquotes(t_data *data, t_quotes *quotes, int i, int j)
{
	int	dq;
	int	sq;
	int	count;
	int	stop;

	dq = -1;
	sq = -1;
	stop = 0;
	while (quotes->arg[++dq])
		if (quotes->arg[dq] == '"')
			break ;
	while (quotes->arg[++sq])
		if (quotes->arg[sq] == '\'')
			break ;
	if (dq < sq)
		count = count_char(quotes->arg, '"');
	else
		count = count_char(quotes->arg, '\'');
	while (quotes->arg[i] && stop < ft_strlen(quotes->arg) - count)
	{
		trimquotes_utils1(quotes->arg[i], &quotes->dq_open, &quotes->sq_open,
			&i);
		trimquotes_utils2(quotes->arg[i], &quotes->dq_open, &quotes->sq_open,
			&i);
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
		trimquotes_utils1(data->clean_prompt[i], &dq_open, &sq_open, &i);
		replace_space(data, &dq_open, &sq_open, i);
	}
	if (check_quotes_open(data, dq_open, sq_open) == 1)
		return (NULL);
	return (data->clean_prompt);
}
