/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danelsalome <danelsalome@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:35:37 by danelsalome       #+#    #+#             */
/*   Updated: 2023/05/13 15:49:24 by danelsalome      ###   ########.fr       */
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

int	count_newlen(char *arg, int i, t_data *data)
{
	int	dq_open;
	int	sq_open;

	dq_open = 0;
	sq_open = 0;
	while (arg[++i])
	{
		if (arg[i] == '"' && sq_open == 0 && dq_open == 0)
		{
			data->count = open_quotes(arg[i], &dq_open, &sq_open, &data->count);
			i++;
		}
		data->count = varenv_len(arg, data, &i, &sq_open);
		if (arg[i] == '\'' && sq_open == 0 && dq_open == 0)
		{
			data->count = open_quotes(arg[i], &dq_open, &sq_open, &data->count);
			i++;
		}
		if (arg[i] == '"' && dq_open == 1)
			data->count = close_quotes(arg[i], &dq_open, &sq_open, &data->count);
		if (arg[i] == '\'' && sq_open == 1)
			data->count = close_quotes(arg[i], &dq_open, &sq_open, &data->count);
	}
	return (data->count);
}

void	trimquotes(char *arg, t_data *data, int index, int i)
{
	int	dq_open;
	int	sq_open;
	int	j;
	int k;
	char *var;

	dq_open = 0;
	sq_open = 0;
	j = 0;
	k = 0;
	while (arg[++i])
	{
		trimquotes_utils1(arg[i], &dq_open, &sq_open, &i);
		trimquotes_utils2(arg[i], &dq_open, &sq_open, &i);
		if ((arg[i] == '"' && sq_open == 0) || (arg[i] == '\'' && dq_open == 0))
		{
			if (arg[i] == '"' && dq_open == 0)
				dq_open = 1;
			else if (arg[i] == '\'' && sq_open == 0)
				sq_open = 1;
			continue ;
		}
		var = replace_dollar(arg, &i, &sq_open);
		if (var == NULL && arg[i] != '$')
		{
			data->f_arg[index][j] = arg[i];
			j++;
		}
		else if (var != NULL)
		{
			while (var[k])
			{
				data->f_arg[index][j] = var[k];
				j++;
				k++;
			}
			k = 0;
		}
		if (arg[i] == '$')
			i--;
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
		trimquotes_utils1(data->clean_prompt[i], &dq_open, &sq_open, &i);
		replace_space(data, &dq_open, &sq_open, i);
	}
	if (check_quotes_open(data, dq_open, sq_open) == 1)
		return (NULL);
	return (data->clean_prompt);
}
