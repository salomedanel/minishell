/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:14:50 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/04 14:56:16 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_len(char *arg, t_data *data)
{
	int	i;
	int	count;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
			return (check_varenv(data, &arg[i]));
		i++;
	}
	i = -1;
	count = ft_strlen(arg);
	return (count_newlen(arg, i, count));
}

void	new_words(char *arg, t_data *data, int index)
{
	int	i;

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
	i = -1;
	if (contains_quotes(arg) == 0)
		ft_strcpy(data->f_arg[index], arg, 0);
	else
		trimquotes(arg, data, index, i);
	return ;
}

void	final_arg(t_data *data)
{
	int	i;

	i = 0;
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
