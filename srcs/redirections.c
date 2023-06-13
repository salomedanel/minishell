/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:55:49 by tmichel-          #+#    #+#             */
/*   Updated: 2023/06/12 22:28:06 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	open_files_utils(t_data *data, int i, int fd)
{
	if ((data->type[i] == T_REDOUT || data->type[i] == T_RED_APPEND))
		dupnclose(fd, STDOUT_FILENO);
	if (data->type[i] == T_REDIN)
		dupnclose(fd, STDIN_FILENO);
	if (data->type[i] == T_HERE_DOC)
		dup2(fd, STDIN_FILENO);
}

int	open_files(t_data *data)
{
	int	i;
	int	fd;

	i = -1;
	fd = 0;
	while (++i < count_redir(data))
	{
		if (data->type[i] == T_REDOUT)
			fd = open(data->redir[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (data->type[i] == T_RED_APPEND)
			fd = open(data->redir[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (outfile_error(data, data->redir[i]));
		if (data->type[i] == T_REDIN)
			fd = open(data->redir[i], O_RDONLY);
		else if (data->type[i] == T_HERE_DOC)
			fd = get_pipe(data->redir[i], data);
		if (fd == -1)
			return (infile_error(data, data->redir[i]));
		open_files_utils(data, i, fd);
	}
	i = -1;
	while (++i < data->nb_here)
		close(data->here[i].fd[0]);
	return (0);
}


