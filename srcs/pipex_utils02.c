/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:12:28 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/31 17:18:26 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	select_pipe(t_data *data, int i)
{
	if (i != data->count_cmd - 1)
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
	if (data.ast == NULL)
		return (0);
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
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (count_redir(*data) == 0)
		return ;
	data->redir = ft_calloc(count_redir(*data) + 1, sizeof(char *));
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
