/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:46:24 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/24 15:37:28 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arg(t_data *data)
{
	int	i;

	i = 0;
	while (data->arg[i])
	{
		free(data->arg[i]);
		i++;
	}
	free(data->arg);
	free(data->clean_prompt);
}

void	freefrom_quotes_err(t_data *data)
{
	free(data->clean_prompt);
	freetab(data->new_env);
	freetab(data->prev_env);
}

void	freefrom_syntax_err(t_data *data)
{
	freetab(data->f_arg);
	freetab(data->new_env);
	freetab(data->prev_env);
}

int	mini_exit(t_data *data)
{
	int	i;

	i = 0;
	while (data->f_arg[i])
	{
		free(data->f_arg[i]);
		i++;
	}
	i = 0;
	while (data->new_env[i])
	{
		free(data->new_env[i]);
		free(data->prev_env[i]);
		i++;
	}
	free(data->new_env);
	free(data->prev_env);
	free(data->f_arg);
	free(data->ast);
	exit(0);
}

void	free_dobby(t_data *data)
{
	int	i;

	i = 0;
	while (data->f_arg[i])
	{
		free(data->f_arg[i]);
		i++;
	}
	i = 0;
	while (data->p_arg[i])
	{
		free(data->p_arg[i]);
		i++;
	}
	free(data->p_arg);
	free(data->f_arg);
	free(data->ast);
}

int	freetab(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return (0);
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (i);
}
