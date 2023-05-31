/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:20:10 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/31 17:39:25 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data, char *str)
{
	int	i;

	freetab(data->tmp_arg);
	if (data->cmd_tab)
		freetab(data->cmd_tab);
	ft_free(data->ast);
	freetab(data->p_arg);
	freetab(data->f_arg);
	if (data->nb_here > 0)
	{
		i = -1;
		while (++i < data->nb_here)
			ft_free(data->here[i].limiter);
		free(data->here);
	}
	if (str)
		free(str);
}

void	free_data_fork(t_data *data)
{
	freetab(data->tmp_arg);
	freetab(data->redir);
	ft_free(data->ast);
	ft_free(data->type);
}

void	free_in_fork(t_data *data, char *str)
{
	freetab(data->path);
	freetab(data->new_env);
	freetab(data->prev_env);
	freetab(data->tmp_arg);
	freetab(data->cmd_tab);
	freetab(data->redir);
	freetab(data->p_arg);
	freetab(data->f_arg);
	ft_free(data->ast);
	ft_free(data->type);
	if (str)
		free(str);
}

void	free_isdir(t_data *data, char *cmd)
{
	freetab(data->path);
	freetab(data->new_env);
	freetab(data->prev_env);
	freetab(data->cmd_tab);
	freetab(data->p_arg);
	freetab(data->f_arg);
	ft_free(cmd);
	exit(0);
}