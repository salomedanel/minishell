/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:55:49 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/27 16:47:21 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_code;

void	outfile_error(t_data *data, char *str)
{
	ft_putstr_fd("minishell: An error has occurred while opening: ", 2);
	ft_putendl_fd(str, 2);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	close(data->fd[0]);
	close(data->fd[1]);
}

void	infile_error(t_data *data, char *str)
{
	ft_putstr_fd("minishell: no such file or directory: ", 2);
	ft_putendl_fd(str, 2);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	close(data->fd[0]);
	close(data->fd[1]);
}

int	last_redir(t_data *data)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (data->type[++i])
		if (data->type[i] == 1 || data->type[i] == 4)
			count++;
	return (count);
}

void	echo_redir(t_data *data, int i, int index)
{
	if (!ft_strcmp(data->cmd_tab[0], "echo") && (data->type[i] == 1 
		|| data->type[i] == 4) && index < last_redir(data))
		exec_builtin(data, data->cmd_tab[0]);
}

int	open_files(t_data *data)
{
	int	i;
	int	j;
	int	fd;

	i = -1;
	j = 0;
	while (data->redir[++i])
	{
		if (data->type[i] == T_REDOUT)
			fd = open(data->redir[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (data->type[i] == T_RED_APPEND)
			fd = open(data->redir[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return(outfile_error(data, data->redir[i]), g_exit_code = 1);	
		if (data->type[i] == T_REDIN)
			fd = open(data->redir[i], O_RDONLY);
		if (fd == -1)
			return(infile_error(data, data->redir[i]), g_exit_code = 1);	
		if ((data->type[i] == T_REDOUT || data->type[i] == T_RED_APPEND) && ++j)
			dupnclose(fd, STDOUT_FILENO);
		else if (data->type[i] == T_REDIN)
			dupnclose(fd, STDIN_FILENO);
		echo_redir(data, i, j);
	}
	return (0);
}
