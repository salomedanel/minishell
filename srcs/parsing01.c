/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:18:14 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/12 17:44:37 by sdanel           ###   ########.fr       */
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
	while (data->new_prompt[i])
	{
		if (data->new_prompt[i] == '"')
		{
			i++;
			if (check_otherquote(data->new_prompt, i, '"') == 0)
				return (1);
			while (data->new_prompt[i] != '"')
			{
				if (data->new_prompt[i] == 32)
					data->new_prompt[i] = 90;
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
	while (data->new_prompt[i])
	{
		if (data->new_prompt[i] == '\'')
		{
			i++;
			if (check_otherquote(data->new_prompt, i, '\'') == 0)
				return (1);
			while (data->new_prompt[i] != '\'')
			{
				if (data->new_prompt[i] == 32)
					data->new_prompt[i] = 90;
				i++;
			}
		}
		i++;
	}
	return (0);
}
