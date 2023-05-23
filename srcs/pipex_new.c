/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:37:39 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/23 16:10:16 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	ft_op_error(char *str)
{
	ft_putstr_fd("minishell: An error has occurred while opening ", 2);
	ft_putendl_fd(str, 2);
}

int	count_redir_out(t_data *data)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (data->ast[++i])
	{
		if (data->ast[i] == T_REDOUT || data->ast[i] == T_RED_OUT_APPEND)
			count++;
	}
	return (count);
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
			dupnclose(fd, STDOUT_FILENO);
		else if (data->ast[i] == T_REDIN)
			dupnclose(fd, STDIN_FILENO);
	}
	// if (data->cmd_id == data->count_cmd - 1 && count_redir_out(data) == 0)
	// 	dupnclose(data->save_out, STDOUT_FILENO);
	return (0);
}
