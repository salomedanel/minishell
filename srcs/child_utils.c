/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:13:00 by tmichel-          #+#    #+#             */
/*   Updated: 2023/06/13 11:20:16 by sdanel           ###   ########.fr       */
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
	int	j;

	j = -1;
	pipe(data->fd);
	data->pid[i] = fork();
	signal(SIGINT, handle_sig_cmd);
	signal(SIGQUIT, handle_sig_cmd);
	while (data->p_arg[++j])
	{
		if (ft_strncmp(data->p_arg[j], "./", 2) == 0)
			ft_ignore_signal();
	}
	if (data->pid[i] < 0)
		return ;
	if (data->pid[i] == 0)
	{
		g_exit_code = 0;
		if (init_exec(data, i))
			exit(127);
		select_pipe(data, i);
		if (open_files(data) == 1)
			free_in_fork(data, cmd);
		if (!count_sub_cmd(data))
			exit_fork(data, cmd);
		cmd = get_cmd_path(data->cmd_tab[0], data->path);
		child_loop(data, cmd);
	}
	else if (data->pid[i] > 0)
		parent_process(data);
	close_fd(data);
}
