/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_newbis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:28:49 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/29 19:43:17 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_code;	

void	select_pipe(t_data *data, int i)
{
	if (i != data->count_cmd -1)
		dup2(data->fd[1], STDOUT_FILENO);
	if (i != 0)
		dupnclose(data->prev_pipe, STDIN_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
}

int	count_redir(t_data data)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (data.ast[++i])
	{
		if (data.ast[i] == T_REDOUT || data.ast[i] == T_RED_APPEND
			|| data.ast[i] == T_REDIN)
			count++;
	}
	return (count);
}

void	get_redir_tab(t_data *data)
{
	int i = -1;
	int j = 0;
	data->redir = malloc(sizeof(char *) * (count_redir(*data) + 1));
	if (!data->redir)
		return ;
	data->type = malloc(sizeof(int) * (count_redir(*data)));
	if (!data->type)
		return ;
	while (data->tmp_arg[++i])
	{
		if (data->ast[i] == T_REDIN || data->ast[i] == T_REDOUT
			|| data->ast[i] == T_RED_APPEND || data->ast[i] == T_HERE_DOC)
		{
			data->redir[j] = ft_strdup(data->tmp_arg[i + 1]);
			data->type[j++] = data->ast[i];
		}
	}
	data->redir[j] = NULL;
}

void	exec(t_data *data)
{
	int		i;
	char 	*cmd;
	int		exipipe[2];

	i = -1;
	data->in = dup(STDIN_FILENO);
	data->out = dup(STDOUT_FILENO);
	data->prev_pipe = -1;
	if (data->p_arg[0] == NULL)
		return ;
	pipe(exipipe);
	while (++i < data->count_cmd)
	{
		pipe(data->fd);
		data->tmp_arg = ft_split(data->p_arg[i], ' ');
		token(data);
		get_cmd_tab(data);
		get_redir_tab(data);
		if (!data->cmd_tab || data->cmd_tab[0] == NULL)
		{
			blank_open(data);
			return ;
		}
		cmd = get_cmd_path(data->cmd_tab[0], data->path);
		if (is_builtin(data->cmd_tab[0]) && data->count_cmd == 1)
		{
			if (open_files(data) == 1)
				continue ;
			open_here_doc(data);
			exec_builtin(data, data->cmd_tab[0]);
			dupnclose(data->in, STDIN_FILENO);
			dupnclose(data->out, STDOUT_FILENO);
			g_exit_code = 0;
		}
		else
		{
			data->pid[i] = fork();
			if (data->pid[i] == 0)
			{
				close(exipipe[0]);
				open_here_doc(data);
				select_pipe(data, i);
				if (open_files(data) == 1)
					exit (1) ;
				if (unforkable_builtins(data->cmd_tab[0]) == 1)
					exit(0);
				if (cmd && !is_builtin(data->cmd_tab[0]))
				{
					write(exipipe[1], &g_exit_code, sizeof(int));
					execve(cmd, data->cmd_tab, data->new_env);
				}
				else if (is_builtin(data->cmd_tab[0]))
				{
					exec_builtin(data, data->cmd_tab[0]);
					write(exipipe[1], &g_exit_code, sizeof(int));
					exit_fork(data, cmd);
				}
				cmd_not_found(data->cmd_tab[0]);
				write(exipipe[1], &g_exit_code, sizeof(int));
				exit_fork(data, cmd);
			}
			else if (data->pid[i] > 0)
			{
				close(exipipe[1]);
				close(data->fd[1]);
				if (data->prev_pipe != -1)
					close(data->prev_pipe);
				data->prev_pipe = data->fd[0];
				waitpid(data->pid[i], 0, 0);
				read(exipipe[0], &g_exit_code, sizeof(int));
			}
		}
		freetab(data->tmp_arg);
		freetab(data->cmd_tab);
		freetab(data->redir);
		free(data->type);
		free(cmd);
	}
	close(exipipe[0]);
	close(exipipe[1]);
	close(data->fd[0]);
	close(data->fd[1]);
	close(data->in);
	close (data->out);
}