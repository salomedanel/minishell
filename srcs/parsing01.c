/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:18:14 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/17 12:45:41 by sdanel           ###   ########.fr       */
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
	while (data->clean_prompt[i])
	{
		if (data->clean_prompt[i] == '"')
		{
			i++;
			if (check_otherquote(data->clean_prompt, i, '"') == 0)
				return (1);
			while (data->clean_prompt[i] != '"')
			{
				if (data->clean_prompt[i] == 32)
					data->clean_prompt[i] = '_';
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	space_squotes(t_data *data)
{
	int	i;

	i = 0;
	while (data->clean_prompt[i])
	{
		if (data->clean_prompt[i] == '\'')
		{
			i++;
			if (check_otherquote(data->clean_prompt, i, '\'') == 0)
				return (1);
			while (data->clean_prompt[i] != '\'')
			{
				if (data->clean_prompt[i] == 32)
					data->clean_prompt[i] = '_';
				i++;
			}
		}
		i++;
	}
	return (0);
}

char	*handle_quotes(t_data *data)
{
	int		i;
	int		qtype;

	i = 0;
	qtype = 0;
	while (data->clean_prompt[i])
	{
		if (data->clean_prompt[i] == '"' && (qtype == 0 || qtype == 2))
		{
			qtype = 2;
			if (space_dquotes(data) == 1)
			{	
				ft_printf("%s '\"'\n", QUOTE_ERR);
				return (NULL);
			}
		}
		else if (data->clean_prompt[i] == '\'' && (qtype == 0 || qtype == 1))
		{
			qtype = 1;
			if (space_squotes(data) == 1)
			{
				ft_printf("%s '\''\n", QUOTE_ERR);
				return (NULL);
			}
		}
		i++;
	}
	return (data->clean_prompt);
}

void	split_space(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	ft_printf("final_prompt = %s\n", data->final_prompt);
	data->arg = ft_split(data->final_prompt, 32);
	while (data->arg[i])
	{
		if (data->arg[i][j] == '"' || data->arg[i][j] == '\'')
		{
			while (data->arg[i][j])
			{
				if (data->arg[i][j] == '_')
					data->arg[i][j] = 32;
				j++;
			}
		}
		ft_printf("arg[%d] = %s\n", i, data->arg[i]);
		i++;
	}
}