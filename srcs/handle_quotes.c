/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:35:37 by danelsalome       #+#    #+#             */
/*   Updated: 2023/05/03 16:46:48 by sdanel           ###   ########.fr       */
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

int	count_newlen(char *arg, int i, int count)
{
	int	dq_open;
	int	sq_open;

	dq_open = 0;
	sq_open = 0;
	while (arg[++i])
	{
		if (arg[i] == '"' && sq_open == 0 && dq_open == 0)
		{
			count = open_quotes(arg[i], &dq_open, &sq_open, &count);
			i++;
		}
		if (arg[i] == '\'' && sq_open == 0 && dq_open == 0)
		{
			count = open_quotes(arg[i], &dq_open, &sq_open, &count);
			i++;
		}
		if (arg[i] == '"' && dq_open == 1)
			count = close_quotes(arg[i], &dq_open, &sq_open, &count);
		if (arg[i] == '\'' && sq_open == 1)
			count = close_quotes(arg[i], &dq_open, &sq_open, &count);
	}
	return (count);
}

void	trimquotes(char *arg, t_data *data, int index, int i)
{
	int	dq_open;
	int	sq_open;
	int	j;

	dq_open = 0;
	sq_open = 0;
	j = 0;
	while (arg[++i])
	{
		trimquotes_utils(arg[i], &dq_open, &sq_open, &i);
		if (arg[i] == '"' && dq_open == 1)
			dq_open = 0;
		if (arg[i] == '\'' && sq_open == 1)
			sq_open = 0;
		if ((arg[i] != '"' && dq_open == 1) || (arg[i] != '\'' && sq_open == 1))
		{
			data->f_arg[index][j] = arg[i];
			j++;
		}
	}
	data->f_arg[index][j] = '\0';

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
		if (data->clean_prompt[i] == '"' && sq_open == 0 && dq_open == 0)
		{
			dq_open = 1;
			i++;
		}
		if (data->clean_prompt[i] == '\'' && sq_open == 0 && dq_open == 0)
		{
			sq_open = 1;
			i++;
		}
		replace_space(data, &dq_open, &sq_open, i);
	}
	if (check_quotes_open(data, dq_open, sq_open) == 1)
		return (NULL);
	return (data->clean_prompt);
}
