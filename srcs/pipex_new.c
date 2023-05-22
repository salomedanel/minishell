/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:37:39 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/17 16:12:37 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	open_files(t_data *data)
{
	int i;
	int fd;

	i = -1;
	fd = 0;
	while (data->f_arg[++i] && data->ast[i] != T_PIPE)
	{
		if (data->ast[i] == T_REDOUT)
			fd = open(data->f_arg[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (data->ast[i] == T_REDIN)
			fd = open(data->f_arg[i + 1], O_RDONLY);
		else if (data->ast[i] == T_RED_OUT_APPEND)
			fd = open(data->f_arg[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: An error has occurred while opening ", 2);
			ft_putendl_fd(data->f_arg[i + 1], 2);
			return (1);
		}
		if (data->ast[i] == T_REDOUT || data->ast[i] == T_RED_OUT_APPEND)
			dupnclose(fd, STDOUT_FILENO);
		else if (data->ast[i] == T_REDIN)
			dupnclose(fd, STDIN_FILENO);
	}
	return (0);
}