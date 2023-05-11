/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:14:50 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/11 13:53:51 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_len(char *arg, t_data *data)
{
	int	i;
	//int	count;

	// if (str_contains_dollar(arg) == 1)
	// 	return (len_env(arg, data));
	i = -1;
	data->count = ft_strlen(arg);
	return (count_newlen(arg, i, data));
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
		data->f_arg[i] = malloc(sizeof(char) * (new_len(data->arg[i], data) + 1));
		new_words(data->arg[i], data, i);
		//printf("new_len = %d\n", new_len(data->arg[i], data));
		i++;
	}
	data->f_arg[i] = NULL;
	free_arg(data);
	return ;
}
