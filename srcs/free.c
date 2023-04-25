/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:46:24 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/25 16:34:41 by sdanel           ###   ########.fr       */
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
		i++;
	}
	free(data->new_env);
	free(data->f_arg);
	free(data->ast);
	exit(0);
}
