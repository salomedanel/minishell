/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:46:24 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/27 07:58:28 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

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

// void	freefrom_quotes_err(t_data *data)
// {
// 	//free(data->clean_prompt);
// 	freetab(data->new_env);
// 	freetab(data->prev_env);
// }

// void	freefrom_syntax_err(t_data *data)
// {
// 	freetab(data->f_arg);
// 	freetab(data->new_env);
// 	freetab(data->prev_env);
// }

int	mini_exit(t_data *data)
{
	freetab(data->f_arg);
	freetab(data->p_arg);
	freetab(data->new_env);
	freetab(data->prev_env);
	freetab(data->cmd_tab);
	freetab(data->path);
	freetab(data->tmp_arg);
	freetab(data->redir);
	free(data->type);
	free(data->ast);
	exit(0);
}

int	mini_exit_bis(t_data *data)
{
	// int	i;

	// i = 0;
	//freetab(data->f_arg);
	//freetab(data->p_arg);
	freetab(data->new_env);
	freetab(data->prev_env);
	freetab(data->path);
	free(data->ast);
	exit(0);
}

void	free_dobby(t_data *data)
{
	free(data->clean_prompt);
	freetab(data->f_arg);
	freetab(data->p_arg);
	freetab(data->new_env);
	freetab(data->prev_env);
	freetab(data->cmd_tab);
	freetab(data->tmp_arg);
	freetab(data->path);
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
