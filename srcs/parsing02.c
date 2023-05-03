/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danelsalome <danelsalome@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:14:50 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/02 15:10:47 by danelsalome      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_finalcheck(t_data *data)
{
	int	i;

	i = 0;
	while (data->arg[i])
	{
		if (data->arg[i][0] == '"' && (data->arg[i][ft_strlen(data->arg[i])
			- 1] == '\'' || (data->arg[i][1] == '"'
			&& count_dquotes(data->arg[i]) % 2 == 1)))
		{
			quote_err2(data, QUOTE_ERR, '"');
			return (1);
		}
		if (data->arg[i][0] == '\'' && (data->arg[i][ft_strlen(data->arg[i])
			- 1] == '"' || (data->arg[i][1] == '\''
			&& count_squotes(data->arg[i]) % 2 == 1)))
		{
			quote_err2(data, QUOTE_ERR, '\'');
			return (1);
		}
		i++;
	}
	return (0);
}

int	new_len(char *arg, t_data *data)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[0] == '\'')
			return (ft_strlen(arg) - count_squotes(arg));
		i++;
	}
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
			return (check_varenv(data, &arg[i]));
		i++;
	}
	// if (str_contains_dollar(arg) == 1)
	// 	return (var_len(arg, data));
	i = 0;
	while (arg[i])
	{
		if (arg[0] == '"')
			return (ft_strlen(arg) - count_dquotes(arg));
		i++;
	}
	return (ft_strlen(arg));
}

void	new_words(char *arg, t_data *data, int index)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			trim_squotes(arg, data, index);
			return ;
		}
		i++;
	}
	i = 0;
	while (arg[i])
	{
		while (arg[i] == '$')
		{
			replace_dollar(arg, data, index);
			return ;
		}
		i++;
	}
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '"')
		{
			trim_dquotes(arg, data, index);
			return ;
		}
		i++;
	}
	ft_strcpy(data->f_arg[index], arg, 0);
	return ;
}

void	final_arg(t_data *data)
{
	int	i;

	i = 0;
	print_arg(data->arg);
	while (data->arg[i])
		i++;
	data->f_arg = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (data->arg[i])
	{
		data->f_arg[i] = malloc(sizeof(char) * (new_len(data->arg[i], data)
					+ 1));
		new_words(data->arg[i], data, i);
		i++;
	}
	data->f_arg[i] = NULL;
	free_arg(data);
	return ;
}
