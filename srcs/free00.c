/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:46:24 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/31 16:27:14 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	freetab(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return (0);
	while (tab[++i])
		ft_free(tab[i]);
	free(tab);
	tab = NULL;
	return (i);
}

void	free_arg(t_data *data)
{
	freetab(data->arg);
	ft_free(data->clean_prompt);
}

int	mini_exit_bis(t_data *data)
{
	freetab(data->new_env);
	freetab(data->prev_env);
	freetab(data->path);
	if (data->redir != NULL && data->redir[0])
		freetab(data->redir);
	if (data->type != NULL)
		ft_free(data->type);
	exit(0);
}

int	exit_fork(t_data *data, char *cmd)
{
	int	i;

	ft_free(cmd);
	freetab(data->f_arg);
	freetab(data->tmp_arg);
	freetab(data->cmd_tab);
	freetab(data->p_arg);
	freetab(data->redir);
	freetab(data->path);
	freetab(data->new_env);
	freetab(data->prev_env);
	ft_free(data->ast);
	ft_free(data->type);
	if (data->nb_here > 0)
	{
		i = -1;
		while (++i < data->nb_here)
			ft_free(data->here[i].limiter);
		free(data->here);
	}
	exit(127);
}
