/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_newbis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:28:49 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/31 11:33:53 by tmichel-         ###   ########.fr       */
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
			|| data.ast[i] == T_REDIN || data.ast[i] == T_HERE_DOC)
			count++;
	}
	return (count);
}

void	get_redir_tab(t_data *data)
{
	int i = -1;
	int j = 0;
	if (count_redir(*data) == 0)
		return ;
	data->redir = ft_calloc(count_redir(*data) + 1, sizeof(char*));
	data->type = ft_calloc(count_redir(*data), sizeof(int));
	while (data->tmp_arg && data->tmp_arg[++i])
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

void	exec_waitpid(t_data *data)
{
	int	i;
	int	var;

	i = -1;
	var = 0;
	while (++i < data->count_cmd)
	{
		waitpid(data->pid[i], &g_exit_code, 0);
		if (WIFEXITED(g_exit_code))
			g_exit_code = WEXITSTATUS(g_exit_code);
		if (g_exit_code == 131 && !var++)
			ft_printf("Quit (core dumped)\n");
	}
}

void	free_data(t_data *data, char *str)
{
	freetab(data->tmp_arg);
	if (data->cmd_tab)
		freetab(data->cmd_tab);
	ft_free(data->ast);
	freetab(data->p_arg);
	freetab(data->f_arg);
	if (str)
		free(str);
}

void	free_data_fork(t_data *data, char *str)
{
	freetab(data->tmp_arg);
	freetab(data->cmd_tab);
	// freetab(data->redir);
	ft_free(data->ast);
	// ft_free(data->type);
	if (str)
		free(str);
}

void	free_in_fork(t_data *data, char *str)
{
	freetab(data->path);
	freetab(data->new_env);
	freetab(data->prev_env);
	freetab(data->tmp_arg);
	freetab(data->cmd_tab);
	freetab(data->redir);
	freetab(data->p_arg);
	freetab(data->f_arg);
	ft_free(data->ast);
	ft_free(data->type);
	if (str)
		free(str);
}

void	exec(t_data *data)
{
	int		i;
	char 	*cmd;
	
	i = -1;
	data->prev_pipe = -1;
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
			return	;
		}
		cmd = get_cmd_path(data->cmd_tab[0], data->path);
		if (data->count_cmd == 1 && is_builtin(data->cmd_tab[0]))
		{
			
			data->in = dup(STDIN_FILENO);
			data->out = dup(STDOUT_FILENO);
			if (open_files(data) == 1)
				return ((void)free_data(data, cmd), (void)close(data->in), (void)close(data->out));
			exec_builtin(data, data->cmd_tab[0]);
			dupnclose(data->in, STDIN_FILENO);
			dupnclose(data->out, STDOUT_FILENO);
			free_data(data, cmd);
			return ;
		}
		else
		{
			printf("%s\n", cmd);
			pipe(data->fd);
			data->pid[i] = fork();
			if (data->pid[i] == 0)
			{
				select_pipe(data, i);
				if (open_files(data) == 1)
				{
					free_in_fork(data,cmd);
					exit (1) ;
				}
				if (unforkable_builtins(data->cmd_tab[0]) == 1)
					exit(0);
				if (cmd && !is_builtin(data->cmd_tab[0]))
					execve(cmd, data->cmd_tab, data->new_env);
				else if (is_builtin(data->cmd_tab[0]))
				{
					// g_exit_code = 0;
					exec_builtin(data, data->cmd_tab[0]);
					exit_fork(data, cmd);
				}
				cmd_not_found(data->cmd_tab[0]);
				exit_fork(data, cmd);
			}
			else if (data->pid[i] > 0)
			{
				close(data->fd[1]);
				if (data->prev_pipe != -1)
					close(data->prev_pipe);
				data->prev_pipe = data->fd[0];
			}
		}
		free_data_fork(data, cmd);
	}
	exec_waitpid(data);
	freetab(data->f_arg);
	freetab(data->p_arg);
	close(data->fd[0]);
	close(data->fd[1]);
}