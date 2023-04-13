/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:18:14 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/13 14:32:04 by sdanel           ###   ########.fr       */
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

void split_space(char *final_prompt)
{
	t_mini mini;

	ft_printf("%s\n", final_prompt);
	mini.full_cmd = ft_split(final_prompt, ' ');
	mini.ast = malloc (sizeof(char *) * 5);
	int i = 0;
	while (mini.ast[i])
	{
		mini.ast[i] = "test";
		if (ft_strncmp(mini.full_cmd[i], "-n", 2) && ft_countchar(mini.full_cmd[1], 'n') == ft_strlen(mini.full_cmd[1] - 1))
			mini.ast[i] = "T_OPTION";
		i++;
		ft_printf("%s\n", mini.ast[i]);
	}
	mini_echo(&mini);
}