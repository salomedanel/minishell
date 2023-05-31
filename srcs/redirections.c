/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:55:49 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/31 00:46:23 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	outfile_error(t_data *data, char *str)
{
	ft_putstr_fd("minishell: An error has occurred while opening: ", 2);
	ft_putendl_fd(str, 2);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
}

void	infile_error(t_data *data, char *str)
{
	ft_putstr_fd("minishell: no such file or directory: ", 2);
	ft_putendl_fd(str, 2);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
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

int get_pipe(char *str, t_data *data)
{
	int i = -1;

	while (++i < data->nb_here)
	{
		if (!ft_strcmp(str, data->here[i].limiter))
			return (data->here[i].fd[0]);
	}
	return (-1);
}

int	open_files(t_data *data)
{
	int	i;
	int	fd;

	i = -1;
	fd = 0;

	while (++i < count_redir(*data))
	{
		if (data->type[i] == T_REDOUT)
			fd = open(data->redir[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (data->type[i] == T_RED_APPEND)
			fd = open(data->redir[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (outfile_error(data, data->redir[i]), g_exit_code = 1);
		if (data->type[i] == T_REDIN)
			fd = open(data->redir[i], O_RDONLY);
		else if (data->type[i] == T_HERE_DOC)
			fd = get_pipe(data->redir[i], data);
		if (fd == -1)
			return (infile_error(data, data->redir[i]), g_exit_code = 1);
		if ((data->type[i] == T_REDOUT || data->type[i] == T_RED_APPEND))
			dupnclose(fd, STDOUT_FILENO);
		if (data->type[i] == T_REDIN)
			dupnclose(fd, STDIN_FILENO);
		if (data->type[i] == T_HERE_DOC)
			dup2(fd, STDIN_FILENO);
	}
	i = -1;
	while (++i < data->nb_here)
		close(data->here[i].fd[0]);
	return (0);
}

int	blank_open(t_data *data)
{
	int	i;
	int	fd;

	i = -1;
	fd = 0;
	while (++i < count_redir(*data))
	{
		if (data->type[i] == T_REDOUT)
			fd = open(data->redir[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (data->type[i] == T_RED_APPEND)
			fd = open(data->redir[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (outfile_error(data, data->redir[i]), g_exit_code = 1);
		if (data->type[i] == T_REDIN)
			fd = open(data->redir[i], O_RDONLY);
		if (data->type[i] == T_HERE_DOC)
			continue ;
		if (fd == -1)
			return (infile_error(data, data->redir[i]), g_exit_code = 1);
		close(fd);
	}
	return (0);
}
