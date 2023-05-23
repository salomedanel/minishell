/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:18:43 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/23 16:11:36 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	select_pipe(t_data *data)
{
	if (data->cmd_id == 0)
	{
		dupnclose(data->in, STDIN_FILENO);
		dupnclose(data->fd[1], STDOUT_FILENO);
		data->prev_pipe = data->fd[0];
	}
	else if (data->cmd_id < data->count_cmd - 1)
	{
		dupnclose(data->prev_pipe, STDIN_FILENO);
		dupnclose(data->fd[1], STDOUT_FILENO);
	}
	else if (data->cmd_id == data->count_cmd - 1)
	{
		dupnclose(data->prev_pipe, STDIN_FILENO);
		dupnclose(data->out, STDOUT_FILENO);
	}
	data->cmd_id++;
}

void	child(t_data *data, int i)
{
	pid_t	pid;

	pipe(data->fd);
	pid = fork();
	if (!pid)
	{
		select_pipe(data);
		open_files(data);
		exec_builtin(data, data->p_arg[i], i);
		execve(data->p_arg[0], &data->p_arg[i], data->new_env);
	}
}