/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:18:14 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/24 17:30:25 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_otherquote(char *prompt, int i, int quote)
{
	while (prompt[i])
	{
		if (prompt[i] == quote)
			return (1);
		i++;
	}
	return (0);
}

int	space_dquotes(t_data *data)
{
	int	i;

	i = 0;
	while (i < ft_strlen(data->clean_prompt) && data->clean_prompt[i])
	{
		if (data->clean_prompt[i] == '"')
		{
			i++;
			if (check_otherquote(data->clean_prompt, i, '"') == 0)
				return (1);
			if (data->clean_prompt[i] == '"')
				i++;
			while (data->clean_prompt[i] && data->clean_prompt[i] != '"')
			{
				if (data->clean_prompt[i] == 32)
					data->clean_prompt[i] = 31;
				i++;
			}
			if (data->clean_prompt[i] == '"' && data->clean_prompt[i + 1] == '"'
				&& count_dquotes(data->clean_prompt) % 2 == 0)
				return (0);
		}
		i++;
	}
	return (0);
}

int	space_squotes(t_data *data)
{
	int	i;

	i = 0;
	while (i < ft_strlen(data->clean_prompt) && data->clean_prompt[i])
	{
		if (data->clean_prompt[i] == '\'')
		{
			i++;
			if (check_otherquote(data->clean_prompt, i, '\'') == 0)
				return (1);
			if (data->clean_prompt[i] == '\'')
				i++;
			while (data->clean_prompt[i] && data->clean_prompt[i] != '\'')
			{
				if (data->clean_prompt[i] == 32)
					data->clean_prompt[i] = 31;
				i++;
			}
			if (data->clean_prompt[i] == '\'' && data->clean_prompt[i
					+ 1] == '\'' && count_squotes(data->clean_prompt) % 2 == 0)
				return (0);
		}
		i++;
	}
	return (0);
}

char	*handle_quotes(t_data *data, int i)
{
	int	qtype;

	qtype = 0;
	while (data->clean_prompt[++i])
	{
		if (data->clean_prompt[i] == '"' && (qtype == 0 || qtype == 2))
		{
			qtype = 2;
			if (space_dquotes(data) == 1)
			{
				quote_err(data, QUOTE_ERR, '"');
				return (NULL);
			}
		}
		else if (data->clean_prompt[i] == '\'' && (qtype == 0 || qtype == 1))
		{
			qtype = 1;
			if (space_squotes(data) == 1)
			{
				quote_err(data, QUOTE_ERR, '\'');
				return (NULL);
			}
		}
	}
	return (data->clean_prompt);
}

void	split_space(t_data *data, int i)
{
	int	j;

	j = 0;
	data->arg = ft_split(data->clean_prompt, 32);
	if (quote_finalcheck(data) == 1)
		return ;
	while (data->arg[++i])
	{
		while (data->arg[i][j])
		{
			if (data->arg[i][j] == '"' || data->arg[i][j] == '\'')
			{
				while (data->arg[i][j])
				{
					if (data->arg[i][j] == 31)
						data->arg[i][j] = 32;
					j++;
				}
			}
			if (j < ft_strlen(data->arg[i]))
				j++;
		}
		j = 0;
	}
}
