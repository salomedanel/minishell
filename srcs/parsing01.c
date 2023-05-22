/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:14:50 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/22 11:21:46 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_len(char *arg, t_data *data, t_quotes *quotes)
{
	quotes->arg = arg;
	data->count = ft_strlen(arg);
	return (count_newlen(data, quotes));
}

void	new_words(char *arg, t_data *data, int index, t_quotes *quotes)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	quotes->dq_open = 0;
	quotes->sq_open = 0;
	quotes->arg = arg;
	quotes->index = index;
	quotes->counter = 0;
	trimquotes(data, quotes, i, j);
	return ;
}

void	final_arg(t_data *data)
{
	int			i;
	t_quotes	quotes;

	i = 0;
	quotes.dq_open = 0;
	quotes.sq_open = 0;
	while (data->arg[i])
		i++;
	data->f_arg = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (data->arg[i])
	{
		data->f_arg[i] = malloc(sizeof(char) * (new_len(data->arg[i], data,
						&quotes) + 1));
		new_words(data->arg[i], data, i, &quotes);
		i++;
	}
	data->f_arg[i] = NULL;
	free_arg(data);
	return ;
}
