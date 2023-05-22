/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:37:39 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/22 16:18:32 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	ft_op_error(char *str)
{
	ft_putstr_fd("minishell: An error has occurred while opening ", 2);
	ft_putendl_fd(str, 2);
}

int	open_files(t_data *data)
{
	int	i;
	int	fd;

	i = -1;
	while (data->f_arg[++i])
	{
		if (data->ast[i] == T_REDOUT)
			fd = open(data->f_arg[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (data->ast[i] == T_REDIN)
			fd = open(data->f_arg[i + 1], O_RDONLY);
		else if (data->ast[i] == T_RED_OUT_APPEND)
			fd = open(data->f_arg[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			ft_op_error(data->f_arg[i + 1]);
		if (data->ast[i] == T_REDOUT || data->ast[i] == T_RED_OUT_APPEND)
			dupnclose(data, fd, STDOUT_FILENO);
		else if (data->ast[i] == T_REDIN)
			dupnclose(data, fd, STDIN_FILENO);
	}
	return (0);
}
