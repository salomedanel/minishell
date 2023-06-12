/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:46:24 by sdanel            #+#    #+#             */
/*   Updated: 2023/06/08 12:40:59 by tmichel-         ###   ########.fr       */
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
	ft_free(tab);
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
	exit(0);
}

int	exit_fork(t_data *data, char *cmd)
{
	int	i;

	ft_free(cmd);
	freetab(data->tmp_arg);
	freetab(data->cmd_tab);
	freetab(data->p_arg);
	freetab(data->path);
	freetab(data->new_env);
	freetab(data->prev_env);
	ft_free(data->ast);
	if (data->nbredir)
	{
		freetab(data->redir);
		ft_free(data->type);
	}
	if (data->nb_here > 0)
	{
		i = -1;
		while (++i < data->nb_here)
			ft_free(data->here[i].limiter);
		free(data->here);
	}
	exit(127);
}
