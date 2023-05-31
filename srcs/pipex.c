/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:28:49 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/31 17:50:08 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	parent_process(t_data *data)
{
	close(data->fd[1]);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	data->prev_pipe = data->fd[0];
	freetab(data->tmp_arg);
	if (data->ast)
		ft_free(data->ast);
	if (data->redir)
		freetab(data->redir);
	if (data->type)
		ft_free(data->type);
	return ;
}

void	child_process(t_data *data, int i, char *cmd)
{
	if (ft_strncmp(data->cmd_tab[0], "./", 2))
		ft_ignore_signal();
	select_pipe(data, i);
	if (open_files(data) == 1)
	{
		free_in_fork(data, cmd);
		exit(1);
	}
	if (unforkable_builtins(data->cmd_tab[0]) == 1)
		exit(0);
	if (cmd && !is_builtin(data->cmd_tab[0]))
	{
		free_data_fork(data);
		execve(cmd, data->cmd_tab, data->new_env);
		cmd_not_found(data->cmd_tab[0]);
		free_isdir(data, cmd);
	}
	else if (is_builtin(data->cmd_tab[0]))
	{
		exec_builtin(data, data->cmd_tab[0]);
		exit_fork(data, cmd);
	}
	return ;
}

void	end_exec(t_data *data)
{
	int	i;

	i = -1;
	exec_waitpid(data);
	if (data->nb_here > 0)
	{
		i = -1;
		while (++i < data->nb_here)
			ft_free(data->here[i].limiter);
		free(data->here);
	}
	freetab(data->f_arg);
	freetab(data->p_arg);
	close(data->fd[0]);
	close(data->fd[1]);
}

void	init_cmd()
{
	
}

void	exec(t_data *data)
{
	int		i;
	int		j;
	char	*cmd;

	i = -1;
	data->prev_pipe = -1;
	j = 0;
	while (++i < data->count_cmd)
	{
		data->tmp_arg = ft_split(data->p_arg[i], ' ');
		token(data);
		get_cmd_tab(data);
		get_redir_tab(data);
		if (!data->cmd_tab || data->cmd_tab[0] == NULL)
		{
			blank_open(data);
			free_data(data, NULL);
			return ;
		}
		cmd = get_cmd_path(data->cmd_tab[0], data->path);
		if (data->count_cmd == 1 && is_builtin(data->cmd_tab[0]))
		{
			data->in = dup(STDIN_FILENO);
			data->out = dup(STDOUT_FILENO);
			if (open_files(data) == 1)
				return ((void)free_data(data, cmd), (void)close(data->in),
					(void)close(data->out));
			exec_builtin(data, data->cmd_tab[0]);
			dupnclose(data->in, STDIN_FILENO);
			dupnclose(data->out, STDOUT_FILENO);
			free_data(data, cmd);
			return ;
		}
		else
		{
			pipe(data->fd);
			data->pid[i] = fork();
			if (data->pid[i] < 0)
				return ;
			if (data->pid[i] == 0)
				child_process(data, i, cmd);
			else if (data->pid[i] > 0)
				parent_process(data);
		}
		ft_free(cmd);
		freetab(data->cmd_tab);
		j = -1;
	}
	end_exec(data);
}
