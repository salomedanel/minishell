/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:13:00 by tmichel-          #+#    #+#             */
/*   Updated: 2023/06/12 12:28:22 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	exec_builtin_in_fork(t_data *data, char *cmd)
{
	exec_builtin(data, data->cmd_tab[0]);
	exit_fork(data, cmd);
}

void	exec_cmd(t_data *data, char *cmd)
{
	free_data_fork(data);
	execve(cmd, data->cmd_tab, data->new_env);
	cmd_not_found(data->cmd_tab[0]);
	free_isdir(data, cmd);
}

void	parent_process(t_data *data)
{
	close(data->fd[1]);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	data->prev_pipe = data->fd[0];
	signal(SIGQUIT, SIG_IGN);
}

void	child_loop(t_data *data, char *cmd)
{
	if (cmd && !is_builtin(data->cmd_tab[0]))
		exec_cmd(data, cmd);
	else if (is_builtin(data->cmd_tab[0]))
		exec_builtin_in_fork(data, cmd);
	else if (!cmd)
	{
		cmd_not_found(data->cmd_tab[0]);
		exit_fork(data, cmd);
	}
}

void	child_process(t_data *data, int i, char *cmd)
{
	pipe(data->fd);
	data->pid[i] = fork();
	if (data->pid[i] < 0)
		return ;
	if (data->pid[i] == 0)
	{
		signal(SIGINT, &ctrlc);
		signal(SIGQUIT, &antislash);
		g_exit_code = 0;
		if (init_exec(data, i))
			exit(127);
		if (ft_strncmp(data->cmd_tab[0], "./", 2))
			ft_ignore_signal();
		select_pipe(data, i);
		if (open_files(data) == 1)
			free_in_fork(data, cmd);
		if (!data->cmd_tab || !data->cmd_tab[0])
			exit_fork(data, cmd);
		cmd = get_cmd_path(data->cmd_tab[0], data->path);
		child_loop(data, cmd);
	}
	else if (data->pid[i] > 0)
		parent_process(data);
	close_fd(data);
}
