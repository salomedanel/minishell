/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_newbis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:28:49 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/24 16:51:32 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_code;	

void	select_pipe(t_data *data)
{
	if (data->cmd_id > data->count_cmd - 1)
		return ;
	if (data->cmd_id == 0)
	{
		dupnclose(data->in, STDIN_FILENO);
		dupnclose(data->fd[1], STDOUT_FILENO);
		// printf("cmd_id = %d\n", data->cmd_id);
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

void	exec(t_data *data)
{
	int		i;
	char 	*cmd;

	i = -1;
	data->path = ft_get_path(data);
	// if (path == NULL) ?
	while (++i < data->count_cmd)
	{
		data->tmp_arg = ft_split(data->p_arg[i], ' ');
		token(data);
		get_cmd_tab(data);
		pipe(data->fd);
		select_pipe(data);
		open_files(data);
		if (is_builtin(data->cmd_tab[0]))
			exec_builtin(data, data->cmd_tab[0]);
		else
		{
			cmd = get_cmd_path(data->cmd_tab[0], data->path);
			if (!cmd)
				return (cmd_not_found(data->cmd_tab[0]));
			data->pid[i] = fork();
			if (data->pid[i] == 0)
				execve(cmd, data->cmd_tab, data->new_env);
		}
		waitpid(-1, NULL, 0);
		freetab(data->cmd_tab);
	}
}