/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:28:49 by tmichel-          #+#    #+#             */
/*   Updated: 2023/06/08 16:43:23 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	init_exec(t_data *data, int i)
{
	data->tmp_arg = ft_split(data->p_arg[i], ' ');
	if (!data->tmp_arg)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		if (data->prev_pipe != -1)
			close(data->prev_pipe);
		ft_putstr_fd("minishell: : command not found\n", 2);
		return (1);
	}
	token(data);
	get_cmd_tab(data);
	get_redir_tab(data);
	return (0);
}

void	exec_one_builtin(t_data *data, char *cmd)
{
	data->in = dup(STDIN_FILENO);
	data->out = dup(STDOUT_FILENO);
	if (open_files(data) == 1)
	{
		free_data(data, cmd);
		close(data->in);
		close(data->out);
		return ;
	}
	exec_builtin(data, cmd);
	dupnclose(data->in, STDIN_FILENO);
	dupnclose(data->out, STDOUT_FILENO);
	return ;
}

void	free_close_exec(t_data *data)
{
	int	i;

	i = -1;
	if (data->nb_here > 0)
	{
		while (++i < data->nb_here)
			ft_free(data->here[i].limiter);
		free(data->here);
	}
	freetab(data->p_arg);
	freetab(data->path);
	close(data->fd[0]);
	close(data->fd[1]);
}

void	exec(t_data *data)
{
	int		i;

	i = -1;
	data->path = ft_get_path(data);
	data->prev_pipe = -1;
	while (++i < data->count_cmd)
	{
		if (data->count_cmd == 1)
		{
			data->tmp_arg = ft_split(data->p_arg[i], ' ');
			if (!data->tmp_arg)
			{
				free(data->p_arg);
				freetab(data->path);
				return ;
			}
			token(data);
			get_cmd_tab(data);
			get_redir_tab(data);
			if (data->cmd_tab && is_builtin(data->cmd_tab[0]))
			{
				exec_one_builtin(data, data->cmd_tab[0]);
				freetab(data->cmd_tab);
				free(data->ast);
				if (data->nbredir)
				{
					freetab(data->redir);
					free(data->type);
				}
				freetab(data->p_arg);
				freetab(data->tmp_arg);
				freetab(data->path);
				return ;
			}
			free(data->ast);
			freetab(data->tmp_arg);
			freetab(data->cmd_tab);
			if (data->nbredir)
			{
				freetab(data->redir);
				free(data->type);
			}
			signal(SIGINT, SIG_IGN);
		}
		child_process(data, i, NULL);
	}
	exec_waitpid(data);
	signal(SIGINT, &ctrlc);
	free_close_exec(data);
}
