/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:20:10 by sdanel            #+#    #+#             */
/*   Updated: 2023/06/13 10:54:09 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	if (count_sub_cmd(data))
		freetab(data->cmd_tab);
	freetab(data->tmp_arg);
	freetab(data->p_arg);
	freetab(data->path);
	ft_free(data->ast);
	if (data->nbredir)
	{
		freetab(data->redir);
		ft_free(data->type);
	}
	if (data->nb_here)
	{
		while (++i < data->nb_here)
			ft_free(data->here[i].limiter);
		free(data->here);
	}
}

void	free_data_fork(t_data *data)
{
	int	i;

	i = -1;
	freetab(data->tmp_arg);
	freetab(data->path);
	ft_free(data->ast);
	if (data->nbredir)
	{
		freetab(data->redir);
		ft_free(data->type);
	}
	if (data->nb_here)
	{
		i = -1;
		while (++i < data->nb_here)
			ft_free(data->here[i].limiter);
		free(data->here);
	}
}

void	free_in_fork(t_data *data, char *str)
{
	int	i;

	i = -1;
	if (count_sub_cmd(data))
		freetab(data->cmd_tab);
	freetab(data->path);
	freetab(data->new_env);
	freetab(data->prev_env);
	freetab(data->tmp_arg);
	freetab(data->redir);
	freetab(data->p_arg);
	ft_free(data->ast);
	ft_free(data->type);
	if (str)
		free(str);
	if (data->nb_here)
	{
		while (++i < data->nb_here)
			ft_free(data->here[i].limiter);
		free(data->here);
	}
	exit(1);
}

void	free_isdir(t_data *data, char *cmd)
{
	freetab(data->new_env);
	freetab(data->prev_env);
	freetab(data->cmd_tab);
	freetab(data->p_arg);
	ft_free(cmd);
	exit(0);
}
